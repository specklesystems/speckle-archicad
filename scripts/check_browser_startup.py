import argparse
from pathlib import Path
import sys


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "log",
        nargs="?",
        type=Path,
        default=Path.home()
        / "Library/Application Support/Speckle/Archicad/bridge-debug.log",
    )
    args = parser.parse_args()
    lines = args.log.read_text().splitlines()
    requests = sum(
        "request-url https://dui.speckle.systems/" in line for line in lines
    )
    failures = [
        line
        for line in lines
        if "load-error" in line and "url=https://dui.speckle.systems/" in line
    ]
    document_calls = sum(
        "run-method binding=baseBinding method=GetDocumentInfo" in line
        for line in lines
    )
    print(
        f"DUI requests={requests}, load errors={len(failures)}, "
        f"document info calls={document_calls}"
    )
    if requests != 1 or failures or document_calls == 0:
        print("FAIL: browser startup did not reach a single healthy native context.")
        return 1
    print("PASS: one DUI navigation reached the native document binding.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
