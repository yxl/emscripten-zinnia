/*
 * @param {Array.<string>} urls An array of the file URLs to load.
 *
 * Usage:
 * require(['foo.js','bar.js'], function () {
 *       // Use foo.js and bar.js here
 * });
 */
function importScripts(urls, callback) {
  if (urls.length > 1) {
    // Load the nth file as soon as everything up to the
    // n-1th one is done.
    importScripts(urls.slice(0,urls.length-1), function () {
      importScripts([urls[urls.length-1]], callback);
    });
    return;
  }
  var script = document.createElement('script');
  script.src = urls[0];
  script.onload = callback;
  document.body.appendChild(script);
}

$(function () {
  importScripts(['js/zinnia-engine.js', 'js/emscripten_zinnia.js'], function() {
    console.log('loaded\n');
  });

	// The timer is used to send handwriting strokes to the recognizer engine if
	// user stops writing for a specified time interval.
  var timeOutId = null;
  var writing = false;

  render.init(280, 280);

	function mousedown(event) {
		clearTimeout(timeOutId);
		var point = board.getMousePoint(event);
		board.addStrokePoint(point[0], point[1]);
		writing = true;
		render.draw(point[0], point[1], true);
	}

	function mousemove(event) {
		if (!writing) {
		  return;
		}

		var point = board.getMousePoint(event);
		board.addStrokePoint(point[0], point[1]);
		render.draw(point[0], point[1], false);
	}

	function mouseup(e) {
		timeOutId = setTimeout(board.sendStrokePoints.bind(board), 50);
		writing = false;
		board.addStrokePoint(-1, 0);
	}

  $("#c").mousedown(mousedown);

  $("#c").mousemove(mousemove);

  $("#c").mouseup(mouseup);

  $('#c').mouseleave(mouseup);

  $("#c").on("touchstart", function(evt) {
    evt.preventDefault();
    evt.stopPropagation();
    mousedown(evt.originalEvent.touches[0]);
  });

  $("#c").on("touchmove", function(evt) {
    evt.preventDefault();
    evt.stopPropagation();
    mousemove(evt.originalEvent.touches[0]);
  });

  $("#c").on("touchend", function(evt) {
    evt.preventDefault();
    evt.stopPropagation();
    mouseup(evt.originalEvent.touches[0]);
  });

  $("#c").on("touchleave", function(evt) {
    evt.preventDefault();
    evt.stopPropagation();
    mouseleave(evt.originalEvent.touches[0]);
  });
  
  $("#clearBtn").click(board.clear.bind(board));
  
	// Select candiate.
	$(document).on('click', '.candidate-item', function () {
		$('#output').val($('#output').val() + $(this).text()[2]);
		board.clear()
	});
});

var board = {
  _strokePoints: [],

  addStrokePoint: function(x, y) {
    if (x < -1 || y < -1) {
      alert('dd');
    }
    this._strokePoints.push(x, y);
  },

  getMousePoint: function(event) {
    var c = $("#c"); 
		var posX = c.offset().left;
		var posY = c.offset().top;

		return [event.pageX - posX, event.pageY - posY];
  },

	sendStrokePoints: function() {
		if (this._strokePoints.length == 0) {
		  return;
		}
		this.showCandidates(HWREngine.recognize(this._strokePoints));
	},

  clear: function() {
  	this._strokePoints = [];
  	render.clear();
  	$("#candidates").html("");
  	arr = [];
  },

	showCandidates: function(str) {
		var strRes = '';
		// Only show the first 5 candidates.
		var len = Math.min(5, str.length);
		for (var i = 0; i < len; i++) {
		  strRes += '<span class="candidate-item">' + (i+1) + '.' + str[i] + '</span>';
		}
		$('#candidates').html(strRes);
	}
};

// Canvas rendering.
var render = {
  _lastX: -1,
  _lastY: -1,
  _ctx: null,
  _width: 280,
  _height: 280,

  init: function(width, height) {
		this._ctx = document.getElementById('c').getContext('2d');
		this._ctx.strokeStyle = "#df4b26";
		this._ctx.lineJoin = "round";
		this._ctx.lineWidth = 5;
		this._width = width;
		this._height = height;
  },

  clear: function() {
  	this._ctx.clearRect(0, 0, 280, 280);
  	this._lastX = this._lastY = -1;
  },

  draw: function(x, y, start) {
		this._ctx.beginPath();

    // Check if we start to write a new stroke.
		if (start) {
		  // Set the last point 2 pixel from the stroke start position, so that we
		  // can draw a start point.
		  this._lastX = x - 1;
		  this._lastY = y;
		}

    this._ctx.moveTo(this._lastX, this._lastY);
    this._ctx.lineTo(x, y);
    this._ctx.closePath();
    this._ctx.stroke();

    this._lastX = x;
    this._lastY = y;
  }
};


