/*
 * vim: set ft=rust:
 * vim: set ft=reason:
 */

open Types;

let linear = fun bounds::(domain: point) => {
  let (min, max) = domain;
  let linearScale = fun value => {
    1. -. (value -. min) /. (max -. min);
  };
  linearScale;
 };

let parseDomain = fun (data: list (float, float)) => {
  let domain = List.map (fun (x, _) => x) data;
  let upper = List.fold_left max 0.0 domain;
  let lower = List.fold_left min max_float domain;
  (upper, lower);
};

let parseRange = fun (data: list (float, float)) => {
  let range = List.map (fun (_, y) => y) data;
  let upper = List.fold_left max 0.0 range;
  let lower = List.fold_left min max_float range;
  (upper, lower);
};