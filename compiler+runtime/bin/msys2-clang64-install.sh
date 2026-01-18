#!/usr/bin/env bash
#
# Download and Install a fixed MSYS2 CLANG64 toolchain for Jank with
# additional patches applied.
#
# set -x

VERSION="21.1.8-2.jank"
FLAVOR="CLANG64"
BASE_URL="https://github.com/ikappaki/MINGW-packages/releases/download/mingw-w64-llvm-${VERSION}"
ZIP="mingw-w64-llvm-${VERSION}-${FLAVOR}.zip"
DEST="build/msys2-clang-jank"

(
  echo "==> Installing required tools"
  pacman -S --needed --noconfirm curl unzip

  echo "==> Creating destination directory: $DEST"
  mkdir -p "$DEST"
  cd "$DEST"

  echo "==> Downloading zip archive: $ZIP"
  curl -LO "${BASE_URL}/${ZIP}"

  echo "==> Extracting archive"
  unzip -o "$ZIP"

  echo "==> Installing packages matching version: $VERSION"
  pacman -U --noconfirm ./*-${VERSION}-*.pkg.tar.zst

  echo "==> Done!"

)
