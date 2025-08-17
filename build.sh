#!/bin/bash

set -e

autoreconf -fi
autoreconf -i

rm -rf build

mkdir build
cd build

INSTALLROOT=$PWD/../install-root

rm -rf $INSTALLROOT

../configure --prefix=$INSTALLROOT
make
make install

