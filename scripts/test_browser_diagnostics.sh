#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TEST_DIR="$(mktemp -d "${TMPDIR:-/tmp}/speckle-browser-diagnostics-test.XXXXXX")"
trap 'rm -rf "$TEST_DIR"' EXIT

clang++ -std=c++20 -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Utils" \
  "$ROOT_DIR/tests/BrowserDiagnosticsTests.cpp" -o "$TEST_DIR/browser_diagnostics_tests"
"$TEST_DIR/browser_diagnostics_tests"
