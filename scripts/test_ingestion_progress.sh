#!/usr/bin/env bash
set -euo pipefail
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TEST_DIR="$(mktemp -d "${TMPDIR:-/tmp}/speckle-ingestion-progress-test.XXXXXX")"
trap 'rm -rf "$TEST_DIR"' EXIT
clang++ -std=c++20 \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Artifacts" \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Converter" \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Network" \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Connector" \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Utils" \
  -I "$ROOT_DIR/Libs/json/include" \
  "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Artifacts/ArtifactUploader.cpp" \
  "$ROOT_DIR/tests/IngestionProgressTests.cpp" -o "$TEST_DIR/ingestion_progress_tests"
"$TEST_DIR/ingestion_progress_tests"
