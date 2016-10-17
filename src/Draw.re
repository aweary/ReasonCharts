/*
 * vim: set ft=rust:
 * vim: set ft=reason:
 */

open Types;

let pos = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0];


/**
 * Draw is resoonsible for rendering
 * the grid system and all data that needs to be plotted.
 * Currently it only handles line charts. The OpenGL cooridante
 * system ranges from -1.0 to 1.0 on both the x and y axis,
 * with 0.0, 0.0 being the center of the grid.
 *
 *
 *               topLeft           topRight
 *             ------------------------------
 *             - -1.0, 1.0   -   1.0, 1.0   -
 *   leftTop   -             -              -  rightTop
 *             -             -              -
 *             -             -              -
 *             ------------------------------
 *             -             -              -
 *  leftBottom -             -              -  rightBottom
 *             -             -              -
 *             - -1.0, -1.0  -   1.0, -1.0  -
 *             ------------------------------
 *               bottomLeft      bottomRight
 */

let topLeft = List.map (fun x => (-.x, 1.0)) @@ List.rev pos;
let bottomLeft = List.map (fun x => (-.x, -1.0)) @@ List.rev pos;


let topRight = List.map (fun x => (x, 1.0)) pos;
let bottomRight = List.map (fun x => (x, -1.0)) pos;

let leftBottom = List.map (fun x => (-1.0, -.x)) pos;
let rightBottom = List.map (fun x => (1.0, -.x)) pos;

let leftTop = List.map (fun x => (1.0, x)) pos;
let rightTop = List.map (fun x => (-1.0, x)) pos;


let drawCoordinateText = fun (x, y) (a, b) => {
  let xChars = ref [];
  let yChars = ref [];
  String.iter (fun c => xChars := List.append !xChars [c]) @@ string_of_float a;
  String.iter (fun c => yChars := List.append !yChars [c]) @@ string_of_float b;
  let xOffset = x >= 0.0 ? -0.02 : 0.02;
  let yOffset = y >= 0.0 ? -0.02 : 0.02;
  let xchars = List.map (fun x => x) !xChars;
  let ychars = List.map (fun y => y) !yChars;
  let chars = ['('];
  let chars = List.append chars xchars;
  let chars = List.append chars [' ', ',', ' '];
  let chars = List.append chars ychars;
  let chars = List.append chars [')'];
  let chars = List.filter (fun c => c != '.') chars;
  let charCodes = List.map int_of_char chars;
  GlPix.raster_pos (x +. xOffset) (y +. yOffset) ();
  List.iter (fun c => Glut.bitmapCharacter font::Glut.BITMAP_TIMES_ROMAN_10 c::c) charCodes;
};

/**
 * Draw a line segment from point a to point b
 */
let drawLineSegment = fun a b => {
  GlDraw.vertex2 a;
  GlDraw.vertex2 b;
};

/**
 * Draw a faint grid both vertically and horizontally
 */
let drawGrid = fun () => {
  GlDraw.color (0.1, 0.1, 0.1);
  ignore @@ List.map2 drawLineSegment topLeft bottomLeft;
  ignore @@ List.map2 drawLineSegment topRight bottomRight;
  ignore @@ List.map2 drawLineSegment leftBottom rightBottom;
  ignore @@ List.map2 drawLineSegment leftTop rightTop;
};

/**
 * Draw the x and y axis and optionally draw a grid
 */
let drawAxis = fun useGrid::useGrid => {
  if (useGrid == true) {
    drawGrid ();
  };
};

/**
 * Draw a line, which is composed of numerous line segments.
 * Used to plot data in a line chart.
 */
let drawLine = fun
  (data: list Gl.point2)
  (index: int)
  (datum: Gl.point2)
  => {
  Gl.enable `line_smooth;
  let length = List.length data;
  if (index < length - 1) {
    let target = List.nth data (index + 1);
    drawLineSegment datum target;
  }
};