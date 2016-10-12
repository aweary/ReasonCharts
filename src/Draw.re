/*
 * vim: set ft=rust:
 * vim: set ft=reason:
 */

open Types;

let drawAxis = fun () => {
  /* Draw primary x and y axis */
  GlDraw.vertex2 (-1.0, 0.0);
  GlDraw.vertex2 (1.0, 0.0);
  GlDraw.vertex2 (0.0, -1.0);
  GlDraw.vertex2 (0.0, 1.0);
  /* Draw grid system */
  for i in 1 to 10 {
    GlDraw.color (0.1, 0.1, 0.1);
    let x = (float_of_int i);
    GlDraw.vertex2 (x /. 10.0, 1.0);
    GlDraw.vertex2 (x /. 10.0, -1.0);
    GlDraw.vertex2 (-.x /. 10.0, 1.0);
    GlDraw.vertex2 (-.x /. 10.0, -1.0);
    GlDraw.vertex2 (1.0, x /. 10.0);
    GlDraw.vertex2 ( -1.0, x /. 10.0);
    GlDraw.vertex2 (1.0, -.x /. 10.0);
    GlDraw.vertex2 (-1.0, -.x /. 10.0);
  };
};

let drawLineSegment = fun
  (data: list point)
  (index: int)
  (datum: point)
  => {
  let length = List.length data;
  if (index < length - 1) {
    let target = List.nth data (index + 1);
    GlDraw.vertex2 datum;
    GlDraw.vertex2 target;
  }
};