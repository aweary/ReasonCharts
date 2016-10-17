/*
 * vim: set ft=rust:
 * vim: set ft=reason:
 */

let linear = fun bounds::(domain: Gl.point2) => {
  let (min, max) = domain;
  let linearScale = fun value => {
    1. -. (value -. min) /. (max -. min);
  };
  linearScale;
 };

 let wideLinear = fun bounds::(domain: Gl.point2) => {
   let (min, max) = domain;
   let mid = (max -. min) /. 2. +. min;
   let step = (max -. min) /. 2.;
   fun value => {
     let offset = value -. mid;
     -1.0 *. offset /. step;
   };
 };

let parseDomain = fun data::data padding::padding => {
  let (_, right, _, left) = padding;
  let domain = List.map (fun (x, _) => x) data;
  let upper = List.fold_left max 0.0 domain;
  let lower = List.fold_left min max_float domain;
  (upper, lower);
};

let parseRange = fun data::data padding::padding => {
  let (top, _, bottom, _) = padding;
  print_endline (string_of_float bottom);
  let range = List.map (fun (_, y) => y) data;
  let upper = List.fold_left max 0.0 range;
  let lower = List.fold_left min max_float range;
  (upper, lower);
};