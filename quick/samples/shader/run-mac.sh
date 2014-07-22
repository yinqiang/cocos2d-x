#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

BIN="$DIR/proj.mac/bin/shader.app/Contents/MacOS/shader"
if [ ! -f $BIN ]; then
    echo "PLEASE BUILD proj.mac/shader.xcodeproj FIRST"
    exit
fi

echo $QUICK_V3_ROOT

ARG="-relaunch-off -quick $QUICK_V3_ROOT/quick -workdir $DIR"
SIZE="-portrait"
CMD="$BIN $ARG $SIZE"

until $CMD; do
    echo ""
    echo "------------------------------------------------------"
    echo ""
    echo ""
    echo ""
done
