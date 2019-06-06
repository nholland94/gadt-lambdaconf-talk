(* $region Type Level Peano Numbers *)
type zero = unit
type 'n succ = unit -> 'n
type one = zero succ
type two = one succ
(* $put ... *)
(* $hide *)
type three = two succ
type four = three succ
type five = four succ
(* $show *)

(* $region GADT Peano Numbers *)
type 'n peano =
  | Zero : zero peano
  | Succ : 'n peano -> ('n succ) peano

let succ : 'n peano -> ('n succ) peano = fun n -> Succ n
let zero : zero peano = Zero
let one : one peano = succ zero
let two : two peano = succ one
(* $put ... *)
