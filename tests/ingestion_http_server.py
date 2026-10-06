import argparse
import json
import threading
import time
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path


class IngestionServer(ThreadingHTTPServer):
    daemon_threads = True

    def __init__(self, address):
        super().__init__(address, Handler)
        self.states = {}
        self.lock = threading.Lock()


class Handler(BaseHTTPRequestHandler):
    protocol_version = "HTTP/1.1"

    def log_message(self, template, *args):
        print(template % args, flush=True)

    def respond(self, body, code=200, headers=None):
        payload = body if isinstance(body, bytes) else json.dumps(body).encode()
        self.send_response(code)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(payload)))
        for key, value in (headers or {}).items():
            self.send_header(key, value)
        self.end_headers()
        try:
            self.wfile.write(payload)
        except (BrokenPipeError, ConnectionResetError):
            pass

    def refresh(self, state):
        if not state["complete"] and time.monotonic() - state["lastUpdate"] > 0.65:
            state["type"] = "ModelIngestionFailedStatus"
            state["cancellationRequested"] = True

    def ingestion(self, state):
        self.refresh(state)
        return {
            "id": state["id"],
            "versionId": state["versionId"],
            "cancellationRequested": state["cancellationRequested"],
            "statusData": {
                "__typename": state["type"],
                "versionId": state["publishedId"],
                "errorReason": "controlled idle timeout or server failure",
                "validationMessage": None,
                "cancellationMessage": None,
            },
        }

    def do_GET(self):
        with self.server.lock:
            state = self.server.states[self.path.removeprefix("/control/")]
            self.refresh(state)
            self.respond(state)

    def do_PUT(self):
        payload = self.rfile.read(int(self.headers.get("Content-Length", 0)))
        with self.server.lock:
            ingestion_id = self.path.split("/")[2]
            self.server.states[ingestion_id]["uploadedBytes"] += len(payload)
        self.respond({}, headers={"ETag": '"runtime-etag"'})

    def do_POST(self):
        body = json.loads(self.rfile.read(int(self.headers.get("Content-Length", 0))))
        with self.server.lock:
            if self.path.startswith("/control/"):
                state = self.server.states[self.path.removeprefix("/control/")]
                state.update(body)
                self.respond(state)
                return
            if self.path == "/graphql":
                self.graphql(body)
                return
            ingestion_id = self.path.split("/")[6]
            state = self.server.states[ingestion_id]
            self.refresh(state)
            if self.path.endswith("/sign"):
                uploads = {
                    name: {"url": f"http://127.0.0.1:{self.server.server_port}/put/{ingestion_id}/{name}"}
                    for name in body["files"]
                }
                self.respond({"uploads": uploads})
            elif self.path.endswith("/complete"):
                state["complete"] = True
                state["completeAt"] = time.monotonic()
                state["updatesAtComplete"] = state["updates"]
                if state["type"] != "ModelIngestionFailedStatus":
                    state["type"] = "ModelIngestionProcessingStatus"
                if state["scenario"] == "complete-malformed":
                    self.respond(b"not-json")
                elif state["scenario"] == "complete-mismatch":
                    self.respond({"versionId": "wrong-complete-echo"})
                else:
                    self.respond({"versionId": state["versionId"]})
            else:
                self.respond({}, 404)

    def graphql(self, body):
        query = body["query"]
        variables = body["variables"]
        if "mutation IngestionCreate" in query:
            ingestion_id = f"ingestion-{len(self.server.states) + 1}"
            version_id = f"reserved-{len(self.server.states) + 1}"
            state = {
                "id": ingestion_id, "versionId": version_id, "publishedId": version_id,
                "scenario": variables["input"]["modelId"], "type": "ModelIngestionProcessingStatus",
                "lastUpdate": time.monotonic(), "updates": 0, "polls": 0, "completionPolls": 0,
                "progressAttempts": 0,
                "complete": False, "versionExists": False, "cancellationRequested": False,
                "failMutations": 0, "cancelMutations": 0, "uploadedBytes": 0,
            }
            self.server.states[ingestion_id] = state
            self.respond({"data": {"data": {"data": {"data": self.ingestion(state)}}}})
            return
        ingestion_id = variables.get("ingestionId", variables.get("input", {}).get("ingestionId"))
        state = self.server.states[ingestion_id]
        self.refresh(state)
        scenario = state["scenario"]
        if "query IngestionStatus" in query:
            state["polls"] += 1
            if scenario == "stalled" and not state["complete"]:
                state["stalledReceived"] = True
                self.server.lock.release()
                try:
                    time.sleep(4)
                finally:
                    self.server.lock.acquire()
            if state["complete"]:
                state["completionPolls"] += 1
                poll = state["completionPolls"]
                if scenario == "retry" and poll in (1, 2, 4, 5):
                    self.respond({"errors": [{"message": "controlled transient failure"}]})
                    return
                if scenario == "failure-budget":
                    self.respond({}, 503)
                    return
                if (scenario in ("publish", "complete-malformed", "complete-mismatch") and poll >= 3) or (scenario == "retry" and poll >= 6):
                    state["type"] = "ModelIngestionSuccessStatus"
                    state["versionExists"] = True
                elif scenario == "mismatch":
                    state["type"] = "ModelIngestionSuccessStatus"
                    state["publishedId"] = "wrong-version"
                elif scenario in ("failed", "cancelled", "invalid", "unknown"):
                    state["type"] = {
                        "failed": "ModelIngestionFailedStatus", "cancelled": "ModelIngestionCancelledStatus",
                        "invalid": "ModelIngestionInvalidStatus", "unknown": "UnexpectedSuccessStatus",
                    }[scenario]
            self.respond({"data": {"project": {"ingestion": self.ingestion(state)}}})
        elif "mutation IngestionProgress" in query:
            state["progressAttempts"] += 1
            if scenario == "heartbeat-retry" and state["progressAttempts"] <= 2:
                self.respond({}, 503)
                return
            state["updates"] += 1
            if state["complete"]:
                state["updatesAfterComplete"] = state.get("updatesAfterComplete", 0) + 1
            state["lastUpdate"] = time.monotonic()
            self.respond({"data": {"data": {"data": {"data": self.ingestion(state)}}}})
        elif "mutation IngestionFail" in query or "mutation IngestionCancel" in query:
            state["failMutations" if "IngestionFail" in query else "cancelMutations"] += 1
            self.respond({"data": {"data": {"data": {"data": self.ingestion(state)}}}})
        else:
            self.respond({"errors": [{"message": "unexpected operation"}]})


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--ready-file", required=True)
    args = parser.parse_args()
    server = IngestionServer(("127.0.0.1", 0))
    Path(args.ready_file).write_text(str(server.server_port))
    print(f"Loopback ingestion fixture on port {server.server_port}; idle window 650ms", flush=True)
    server.serve_forever()


if __name__ == "__main__":
    main()
