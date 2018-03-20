const MAX_CANDIDATE_NUM = 10;
const MAX_STROKE_NUM = 1000;

var HWREngine = {
  recognize: function(points) {
    var strokes = points.slice(0, 2 * MAX_STROKE_NUM);
    // Append [-1, -1] to strokes.
    strokes.push.apply(strokes, [-1, -1]);
    this._strokeBuffer.set(strokes);
    return this._CharacterRecognize(this._strokeBuffer.byteOffset);
  },

  init: function() {
    if (!Module.ccall('InitRecog',
                      'number',
                      ['string', 'number', 'number'],
                      ['zh_Hans.model', 140, 140])) {
      return false;
    }

    this._CharacterRecognize =
      Module.cwrap('CharacterRecognize', 'string', ['number']);

    var buf = Module._malloc((MAX_STROKE_NUM + 1) * 4);
    this._strokeBuffer = 
      new Int16Array(Module.HEAPU8.buffer, buf, (MAX_STROKE_NUM + 1) * 2);

    return true;
  },

  uinit: function() {
    Module._free(this._strokeBuffer.byteOffset);
    Module.ccall('ExitRecog', '', [], []);
  },

  _strokeBuffer: null,
  _CharacterRecognize: null,
};

Module = {
  canvas: {},
  stdout: null,
  onRuntimeInitialized: function() {
    if (!HWREngine.init()) {
      alert('InitHzRecog failed\n');
      return;
    }
  }
};
