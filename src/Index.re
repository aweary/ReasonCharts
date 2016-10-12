
/*
 * vim: set ft=rust:
 * vim: set ft=reason:
 */

open Types;

let windowSize = 800;

/* Hardcoded list of points representing x/y values */
let (data: list point) = [
  (1.0, 10.0),
  (2.0, 30.0),
  (3.0, 20.0),
  (6.0, 40.0),
  (8.0, 60.0),
  (9.0, 1.0),
  (12.0, 20.0),
  (30.0, 100.0)
];
/* Find the bounds for the domain/range */

let domain = Scale.parseDomain data;
let range = Scale.parseRange data;

let scaleX = Scale.linear bounds::domain;
let scaleY = Scale.linear bounds::range;

let scaledData = List.map (fun (x, y) => (scaleX(x), scaleY(y))) data;

let render = fun () => {
  GlClear.clear [`color];
  GlMat.load_identity ();
  GlDraw.begins `lines;
  GlDraw.color (1.0, 1.0, 1.0);
  ignore @@ Draw.drawAxis ();
  GlDraw.color (1.0, 0.5, 0.5);
  List.iteri (Draw.drawLineSegment scaledData) scaledData;
  GlDraw.ends ();
  Glut.swapBuffers ();
};


let () = {
  ignore @@ Glut.init Sys.argv;
  Glut.initWindowSize windowSize windowSize;
  Glut.initDisplayMode double_buffer::true ();
  ignore @@ Glut.createWindow title::"Reason Charts";
  GlMat.mode `modelview;
  Glut.displayFunc (render);
  Glut.idleFunc cb::(Some Glut.postRedisplay);
  Glut.mainLoop ();
}