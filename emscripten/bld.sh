#!/bin/sh

# build native zinnia tools
mkdir -p build
cd build
../../zinnia/configure --prefix=`pwd`
make && make install

# generate dictionaries
cd ..
make

# update demo
cp emscripten_zinnia.data demo/
cp emscripten_zinnia.js demo/js/

echo build done! Open demo/index.html to run the demo.
