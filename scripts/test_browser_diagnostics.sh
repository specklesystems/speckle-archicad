#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TEST_DIR="$(mktemp -d "${TMPDIR:-/tmp}/speckle-browser-diagnostics-test.XXXXXX")"
trap 'rm -rf "$TEST_DIR"' EXIT

clang++ -std=c++20 -I "$ROOT_DIR/AddOns/Speckle/Sources/AddOn/Utils" \
  "$ROOT_DIR/tests/BrowserDiagnosticsTests.cpp" -o "$TEST_DIR/browser_diagnostics_tests"
"$TEST_DIR/browser_diagnostics_tests" "$TEST_DIR/probe.js"

node - "$TEST_DIR/probe.js" <<'JS'
const assert = require('node:assert/strict')
const fs = require('node:fs')
const vm = require('node:vm')
const messages = []
vm.runInNewContext(fs.readFileSync(process.argv[2], 'utf8'), {
  URL,
  location: { href: 'https://user:password@dui.speckle.systems/?token=secret#private' },
  document: {
    readyState: 'complete',
    scripts: [{ src: 'https://dui.speckle.systems/_nuxt/entry.js?token=secret#private' }],
    body: { children: [] },
    getElementById: () => ({ children: [] })
  },
  window: {},
  performance: { getEntriesByType: () => [{ initiatorType: 'script', name: 'https://dui.speckle.systems/_nuxt/entry.js?token=secret', decodedBodySize: 12, transferSize: 14 }] },
  console: { log: value => messages.push(value) }
})
assert.equal(messages.length, 1)
assert(!/password|secret|private|token=/.test(messages[0]))
const context = JSON.parse(messages[0].slice('[DEBUG-ENG10393] context '.length))
assert.equal(context.baseBinding, 'undefined')
assert.equal(context.readyState, 'complete')
assert.equal(context.nuxtChildren, 0)
assert.equal(context.resources[0].decodedBytes, 12)
console.log('Browser diagnostics context probe tests passed')
JS
