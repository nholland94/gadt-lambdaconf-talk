(* $region Type Level List *)
type nil = unit
type ('h, 't) cons = 'h -> 't

(* $region Heterogeneous List *)
type 'ls hlist =
  | [] : nil hlist
  | (::) : 'h * 't hlist -> (('h, 't) cons) hlist

let x : (int -> string -> (int -> int) -> unit) hlist =
  [1; "str"; ((+) 1)]
