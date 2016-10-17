
/*
 * vim: set ft=rust:
 * vim: set ft=reason:
 */

open Types;

let windowSize = 500;

let state: chartState = {
  windowSize: 600,
  useGrid: true
};

/* Hardcoded list of points representing x/y values */
let (data: list Gl.point2) = [
  (0.0, 0.0),
  (1.0, 20.0),
  (2.0, 10.0),
  (3.0, 40.0),
  (4.0, 30.0),
  (5.0, 0.0),
];

/* Padding is parsed just like padding in CSS, top, right, bottom left */
let padding = (10.0, 10.0, 0.0, 0.0);
/* Find the bounds for the domain/range */

let domain = Scale.parseDomain data::data padding::padding;
let range = Scale.parseRange data:: data padding::padding;

let scaleX = Scale.wideLinear bounds::domain;
let scaleY = Scale.wideLinear bounds::range;

let scaledData = List.map (fun (x, y) => (scaleX(x), scaleY(y))) data;

let render = fun () => {
  GlClear.clear [`color];
  GlMat.load_identity ();
  GlDraw.begins `lines;
  GlDraw.color (1.0, 1.0, 1.0);
  Draw.drawAxis useGrid::true;
  GlDraw.color (0.5, 0.3, 0.75);
  List.iteri (Draw.drawLine scaledData) scaledData;
  GlDraw.ends ();
  Glut.swapBuffers ();
  GlClear.clear [`color];
  GlDraw.color (1.0, 1.0, 1.0);
  GlPix.raster_pos x::0.5 y::0.0 ();
  List.iter2 Draw.drawCoordinateText scaledData data;
  Glut.swapBuffers ();
};

let resize = fun w::w h::h => {
  print_endline (string_of_int w ^ "x" ^ string_of_int h);
  GlDraw.viewport x::0 y::0 w::w h::h;
  render ();
};

let () = {
  ignore @@ Glut.init Sys.argv;
  Glut.initWindowSize windowSize windowSize;
  Glut.initDisplayMode double_buffer::true ();
  ignore @@ Glut.createWindow title::"Reason Charts";
  GlMat.mode `modelview;
  Glut.displayFunc (render);
  Glut.idleFunc cb::(Some Glut.postRedisplay);
  Glut.reshapeFunc (resize);
  Glut.mainLoop ();
}