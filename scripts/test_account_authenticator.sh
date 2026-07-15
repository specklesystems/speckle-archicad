#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$(mktemp -d "${TMPDIR:-/tmp}/speckle-account-auth-test.XXXXXX")"
trap 'rm -rf "$BUILD_DIR"' EXIT

clang++ -std=c++20 \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Connector" \
  -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Network" \
  -I "$ROOT_DIR/Libs/json/include" \
  -I "$ROOT_DIR/Libs/sha/include" \
  "$ROOT_DIR/tests/AccountAuthenticatorTests.cpp" \
  "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Connector/AccountAuthentication.cpp" \
  -o "$BUILD_DIR/account_authenticator_tests"

"$BUILD_DIR/account_authenticator_tests"
