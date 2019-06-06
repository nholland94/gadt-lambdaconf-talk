(* $hide *)
#use "peano.ml"
#use "vect.ml"
(* $show *)
(* $region Uninitialized Reduction *)
let reduce : type n. ('a -> 'a -> 'a) -> (n succ, 'a) vect -> 'a =
  fun f list ->
    let rec loop : type n. (n succ, 'a) vect -> 'a -> 'a =
      fun list acc ->
        match list with
        | []     -> acc
        | h :: t -> loop t (f acc h)
    in
    match list with
    | h :: t -> loop t h
    | _      -> .
