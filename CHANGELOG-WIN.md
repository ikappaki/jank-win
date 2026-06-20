# Changelog

This fork carries Windows-specific changes pending upstream acceptance.
See [README.md](README.md) for context.

Binaries: [jank-win-release](https://github.com/ikappaki/jank-win-release)

## Untagged

- Add `-DGC_NO_THREAD_REDIRECTS` to fix `future` deref segfault on macOS ([#813](https://github.com/jank-lang/jank/discussions/813))
- Extend nREPL server with test-support hooks (header + implementation changes)
- Add nREPL test suite: bencode, parsec, connection harness, and core server tests (`test/bash/nrepl-server/`)

## 2026-05-26 (80c2d4f06)

**Synced with:** jank-lang/jank @ [`80c2d4f06`](https://github.com/jank-lang/jank/commit/80c2d4f0672d55d57102d34f5ad328b4ef551329)
**Changeset:** [main-jank.26-05-26-80c2d4f06...main-win.26-05-26-80c2d4f06](https://github.com/ikappaki/jank-win/compare/main-jank.26-05-26-80c2d4f06...main-win.26-05-26-80c2d4f06)
**Highlight:** SEH exception support via custom LLVM build, all Windows exception tests re-enabled

- Switch LLVM to ikappaki/llvm-project (branch `support/jitlink-coff-seh-llvm-22`) for SEH exception support
- Re-enable all Windows exception tests (JIT skip list, bash E2E suites)
- Fix `unsigned long` → `unsigned long long` pointer cast for 64-bit Windows
- Fix negative code point range check in `character.cpp`
- Fix module-path separator in error-reporting tests for Windows
- Add README banner identifying fork purpose
- Add CHANGELOG-WIN.md

