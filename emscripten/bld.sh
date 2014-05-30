#!/bin/sh

# build native zinnia tools
mkdir -p build
cd build
../../zinnia/configure --prefix=`pwd`
make && make install

# generate dictionaries
cd ..
make
