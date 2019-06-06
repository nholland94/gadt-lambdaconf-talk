(* $hide *)
#use "peano.ml"
#use "vect.ml"
(* $show *)
(* $region Balanced Binary Tree *)
type ('depth, 'el) bbtree =
  | Leaf : 'el -> (zero, 'el) bbtree
  | Branch :
         'el * ('depth, 'el) bbtree * ('depth, 'el) bbtree
      -> ('depth succ, 'el) bbtree

let split :
     type depth.
     (depth succ, 'a) bbtree
  -> (depth, 'a) bbtree * (depth, 'a) bbtree =
  function
  | Branch (_, l, r) -> (l, r)
  | _ -> .

(* $hide *)
(*
type ('a, 'b, 'r) sum =
	| Sum_ident : (zero_, 'r, 'r) sum
	| Sum_step : ('a, 'b, 'r) sum -> ('a succ_, 'b, 'r succ_) sum

type ('a_peano, 'b_peano, 'r, 'sum) sum_peano = 'r peano
	constraint 'a_peano = 'a peano
  constraint 'b_peano = 'b peano
  constraint 'sum = ('a, 'b, 'r) sum

(*... err no actually gt *)
type ('length, 'rem) peano_gt = 'result
	constraint 'rem -> 'length = 'result -> unit

type ('old, 'tail, 'updated) append =
  | Append_base : (unit, 'tail, 'tail) append
  | Append_step : ('t, 'tail, 'updated) append -> ('h -> 't, 'tail, 'updated) append
(* currently just the leftmost to test *)
let rec defract : type length rem. length peano -> ((length, rem) peano_gt, 'el) bbtree -> (rem, 'el) bbtree =
	fun len tree ->
		match (len, tree) with
		| (Zero, Branch (el, l, r)) -> Branch (el, Branch (el, l, r), Branch (el, l, r))
		| (Succ n, Branch (_, l, _)) -> defract l n
*)
