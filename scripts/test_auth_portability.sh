#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$(mktemp -d "${TMPDIR:-/tmp}/speckle-auth-portability-test.XXXXXX")"
trap 'rm -rf "$BUILD_DIR"' EXIT

clang++ -std=c++20 \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Auth" \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Connector" \
  -I "$ROOT_DIR/Libs/sha/include" \
  "$ROOT_DIR/tests/AuthPortabilityTests.cpp" \
  "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Auth/CryptoUtils.cpp" \
  "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Auth/LoopbackListener.cpp" \
  -o "$BUILD_DIR/auth_portability_tests"

"$BUILD_DIR/auth_portability_tests"
