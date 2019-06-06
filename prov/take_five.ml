(* $hide *)
#use "peano.ml"
#use "vect.ml"
(* $show *)
(* $region Encoding Restrictions on Types *)
type 'n plus_five = 'n succ succ succ succ succ

let take_five : ('n plus_five, 'a) vect -> (five, 'a) vect =
  function
  | v0 :: v1 :: v2 :: v3 :: v4 :: _  -> [v0; v1; v2; v3; v4]
  | _ -> .

(* $hide *)

type ('n, 'm, 'z) add =
  | Identity : (zero, 'm, 'm) add
  | Recursive : ('n, 'm, 'z) add -> ('n succ, 'm, unit -> 'z) add

(*
let rec take_n : type n z. (z, 'a) vect -> (n succ) peano -> (n succ, 'm, z) add * (n succ, 'a) vect =
  fun ls n ->
    match (ls, n) with
    | (h :: t, Succ n') ->
        let (add_z, t') = take_n t n' in
        (Recursive add_z, h :: t')
    | (_, Zero) -> (Identity, [])
    | _ -> .

let rec take_n : type n z. (z, 'a) vect -> (n succ) peano -> (n succ, 'm, z) add * (n succ, 'a) vect =
  fun ls n ->
    match (ls, n) with
    | (h :: t, Succ (Succ n')) ->
        let (add_z, t') = take_n t (Succ n') in
        (Recursive add_z, h :: t')
    | (h :: t, Succ n') ->
        (Recursive Identity, [h])
    | _ -> .
*)
