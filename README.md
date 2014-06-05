emscripten-zinnia
=================

Porting of zinnia to javascript library with emscripten.

Zinnia is a simple, open source online hand recognition system:
<http://zinnia.sourceforge.net/>

The emscripten-zinnia has two built-in recognition models:

 * zh_Hans.model - Simplified Chinese model
 * zh_Hant.model - Traditional Chinese model

These models are extracted from the zinnia Japanese model. Therefore they
only contains part of the most frequently used Chinese characters.

Assume the root diectory of the source code is `$SRC_DIR`. See
`$SRC_DIR\emscripten\emscripten_zinnia.cpp` about the usage.

Build
-------

For Linux (such as Ubuntu 12.04), run the following commands:

`cd  $SRC_DIR/emscripten && ./bld.sh`

If succeeded, you will see the following message:

 * ...
 * node emscripten_zinnia_test.js
 * 前草帝荒奏洞考尊施葱
 * Test succeeded!
 * build done! Open demo/index.html to run the demo.

And get a library file - `emscripten_zinnia.js` alongside a data file - `emscripten_zinnia.data`.

Demo
-------

The demo is under `$SRC_DIR/emscripten/demo` (<http://yxl.github.io/emscripten-zinnia/>). It is a Firefox OS app.

Update its library and data files generated after the above build process.

Open `index.html` with Firefox (or Chrome) browser to view the demo on your computer,
or install the app into your Firefox OS device.

License
-------

emscripten-zinnia as well as the original zinnia is available under BSD 2-Clause
license.
