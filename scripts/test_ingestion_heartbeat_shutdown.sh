#!/usr/bin/env bash
set -euo pipefail
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TEST_DIR="$(mktemp -d "${TMPDIR:-/tmp}/speckle-ingestion-shutdown-test.XXXXXX")"
trap 'rm -rf "$TEST_DIR"' EXIT
clang++ -std=c++20 -fobjc-arc -framework Foundation \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Artifacts" \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Network" \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Connector" \
  "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Network/MacHttpClient.mm" \
  "$ROOT_DIR/tests/IngestionHeartbeatShutdownTests.cpp" -o "$TEST_DIR/shutdown_test"
python3 - "$TEST_DIR/shutdown_test" <<'PY'
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from threading import Thread
import subprocess
import sys
import time

class StalledHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        time.sleep(3)
    def log_message(self, *args):
        pass

server = ThreadingHTTPServer(('127.0.0.1', 0), StalledHandler)
Thread(target=server.serve_forever, daemon=True).start()
try:
    subprocess.run([sys.argv[1], f'http://127.0.0.1:{server.server_port}/graphql'], check=True, timeout=5)
finally:
    server.shutdown()
    server.server_close()
PY
