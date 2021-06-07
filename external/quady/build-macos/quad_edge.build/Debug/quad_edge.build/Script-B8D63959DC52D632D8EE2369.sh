#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/edselmalasig/dev/engine-X/external/quady/build-macos
  /usr/local/Cellar/cmake/3.20.2/bin/cmake -E cmake_symlink_library /Users/edselmalasig/dev/engine-X/external/quady/build-macos/Debug/libquad_edge.0.1.0.dylib /Users/edselmalasig/dev/engine-X/external/quady/build-macos/Debug/libquad_edge.1.dylib /Users/edselmalasig/dev/engine-X/external/quady/build-macos/Debug/libquad_edge.dylib
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/edselmalasig/dev/engine-X/external/quady/build-macos
  /usr/local/Cellar/cmake/3.20.2/bin/cmake -E cmake_symlink_library /Users/edselmalasig/dev/engine-X/external/quady/build-macos/Release/libquad_edge.0.1.0.dylib /Users/edselmalasig/dev/engine-X/external/quady/build-macos/Release/libquad_edge.1.dylib /Users/edselmalasig/dev/engine-X/external/quady/build-macos/Release/libquad_edge.dylib
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/edselmalasig/dev/engine-X/external/quady/build-macos
  /usr/local/Cellar/cmake/3.20.2/bin/cmake -E cmake_symlink_library /Users/edselmalasig/dev/engine-X/external/quady/build-macos/MinSizeRel/libquad_edge.0.1.0.dylib /Users/edselmalasig/dev/engine-X/external/quady/build-macos/MinSizeRel/libquad_edge.1.dylib /Users/edselmalasig/dev/engine-X/external/quady/build-macos/MinSizeRel/libquad_edge.dylib
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/edselmalasig/dev/engine-X/external/quady/build-macos
  /usr/local/Cellar/cmake/3.20.2/bin/cmake -E cmake_symlink_library /Users/edselmalasig/dev/engine-X/external/quady/build-macos/RelWithDebInfo/libquad_edge.0.1.0.dylib /Users/edselmalasig/dev/engine-X/external/quady/build-macos/RelWithDebInfo/libquad_edge.1.dylib /Users/edselmalasig/dev/engine-X/external/quady/build-macos/RelWithDebInfo/libquad_edge.dylib
fi

