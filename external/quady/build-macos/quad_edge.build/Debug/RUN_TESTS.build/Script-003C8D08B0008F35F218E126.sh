#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/edselmalasig/dev/engine-X/external/quady/build-macos
  /usr/local/Cellar/cmake/3.20.2/bin/ctest --force-new-ctest-process -C $CONFIGURATION$EFFECTIVE_PLATFORM_NAME
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/edselmalasig/dev/engine-X/external/quady/build-macos
  /usr/local/Cellar/cmake/3.20.2/bin/ctest --force-new-ctest-process -C $CONFIGURATION$EFFECTIVE_PLATFORM_NAME
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/edselmalasig/dev/engine-X/external/quady/build-macos
  /usr/local/Cellar/cmake/3.20.2/bin/ctest --force-new-ctest-process -C $CONFIGURATION$EFFECTIVE_PLATFORM_NAME
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/edselmalasig/dev/engine-X/external/quady/build-macos
  /usr/local/Cellar/cmake/3.20.2/bin/ctest --force-new-ctest-process -C $CONFIGURATION$EFFECTIVE_PLATFORM_NAME
fi

