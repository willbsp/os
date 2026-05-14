#!/bin/sh
# dev.sh - regenerate compile_commands.json
set -e
. ./config.sh
./clean.sh
. ./headers.sh
(cd libc && DESTDIR="$SYSROOT" bear --output ../compile_commands.json -- $MAKE install)
(cd kernel && DESTDIR="$SYSROOT" bear --append --output ../compile_commands.json -- $MAKE install)
