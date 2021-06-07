#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/edselmalasig/dev/engine-X/external/quady/build-macos
  make -f /Users/edselmalasig/dev/engine-X/external/quady/build-macos/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/edselmalasig/dev/engine-X/external/quady/build-macos
  make -f /Users/edselmalasig/dev/engine-X/external/quady/build-macos/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/edselmalasig/dev/engine-X/external/quady/build-macos
  make -f /Users/edselmalasig/dev/engine-X/external/quady/build-macos/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/edselmalasig/dev/engine-X/external/quady/build-macos
  make -f /Users/edselmalasig/dev/engine-X/external/quady/build-macos/CMakeScripts/ReRunCMake.make
fi

