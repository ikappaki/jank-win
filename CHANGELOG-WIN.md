# Changelog

This fork carries Windows-specific changes pending upstream acceptance.
See [README.md](README.md) for context.

Binaries: [jank-win-release](https://github.com/ikappaki/jank-win-release)

## Untagged

- Switch LLVM to ikappaki/llvm-project (branch `support/jitlink-coff-seh-llvm-22`) for SEH exception support
- Re-enable all Windows exception tests (JIT skip list, bash E2E suites)
- Fix `unsigned long` → `unsigned long long` pointer cast for 64-bit Windows
- Fix negative code point range check in `character.cpp`
- Fix module-path separator in error-reporting tests for Windows
- Add README banner identifying fork purpose
- Add CHANGELOG-WIN.md

