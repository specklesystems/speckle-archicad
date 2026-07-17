#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$(mktemp -d "${TMPDIR:-/tmp}/speckle-session-log-test.XXXXXX")"
TEST_TMPDIR="$(mktemp -d "${TMPDIR:-/tmp}/speckle-session-log-data.XXXXXX")"
trap 'rm -rf "$BUILD_DIR" "$TEST_TMPDIR"' EXIT

clang++ -std=c++20 \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Diagnostics" \
  -I "$ROOT_DIR/Libs/json/include" \
  "$ROOT_DIR/tests/ArtefactSessionLogTests.cpp" \
  "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Diagnostics/ArtefactSessionLog.cpp" \
  -o "$BUILD_DIR/artefact_session_log_tests"

TMPDIR="$TEST_TMPDIR" "$BUILD_DIR/artefact_session_log_tests"
