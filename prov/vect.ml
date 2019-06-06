(* $hide *)
#use "peano.ml"
(* $show *)
(* $region Vectors *)
type ('n, 'a) vect =
  | [] : (zero, 'a) vect
  | (::) : 'a * ('n, 'a) vect -> ('n succ, 'a) vect
