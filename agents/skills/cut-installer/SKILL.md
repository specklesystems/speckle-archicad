---
name: cut-installer
description: Cut an Archicad connector installer — a test installer from any branch via an installer-test/ push, or a public release via an unprefixed CalVer tag — and understand how the version reaches the .apx and the server.
---

# Cutting an installer

Versioning is **tag-driven** (GitVersion was removed in `fe9f5e4`; there is no `GitVersion.yml`).
`main` is the production branch. `.github/workflows/release.yml` builds on Windows, then dispatches
the `Build Installers` workflow in `specklesystems/connector-installers`.

## Test installer (any branch)

```
git push origin <branch>:installer-test/<name>
```

A push to `installer-test/**` builds with a synthesized version `0.0.0.<run_number>` and
`is_public_release: false`.

## Public release

Push a tag matching `202[0-9].*.*` — **unprefixed** CalVer, e.g. `2026.9.0` (the `v` prefix was
dropped at 2026.9, ENG-9392; old `v3.x` / `v2026.x` tags do not trigger). `is_public_release` is
`true` for tag refs.

## How the version flows

- `release.yml` derives `semver` (= tag, or `0.0.0.<run>`) and `fileVersion`
  (`<major.minor.patch>.<run>`) in its `set-version` step and passes them to `./build.ps1` as the
  **environment variables** `SEMVER` / `FILE_VERSION`. They must be env, not step outputs —
  `ci-build/Program.cs` reads `Environment.GetEnvironmentVariable`; when that link was missing,
  every build silently shipped the `0.0.0-localBuild` fallback.
- The `build` target substitutes `SEMVER` for `connector_build_num` in
  `AddOnResources/RINT/AddOn.grc` (`STR# 5010`) and passes `/p:Version` + `/p:FileVersion` to
  msbuild.
- `STR# 5010` is the connector version the UI shows (`BaseBridge.cpp`) **and** the
  `envelope.meta.producer_version` stamped into every artifact bundle
  (`ArchicadArtifactRootObjectBuilder.cpp`) — a wrong value there is visible server-side, not just
  cosmetic.
- Running `./build.ps1` locally rewrites the tracked `AddOn.grc`; `git checkout` it afterwards.
