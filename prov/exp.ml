(* $hide *)
open Base
(* $show *)
(* $region Defining a Witness Type *)
type 'a type_ =
  | Int : int type_
  | Bool : bool type_

(* $region Defining Limited Polymorphic Equality *)
let rec equal : type t. t type_ -> t -> t -> bool =
  fun t x y ->
    match t with
    | Int -> Int.equal x y
    | Bool -> Bool.equal x y

(* $region Defining the Expression Tree *)
type 'a exp =
  | Value : 'a type_ * 'a -> 'a exp
  | Not : bool exp -> bool exp
  | And : bool exp * bool exp -> bool exp
  | Equal : 'a exp * 'a exp -> bool exp
  | Add : int exp * int exp -> int exp

(* $region Evaluating the Expression Tree *)
let rec eval : type t. t exp -> t type_ * t =
  fun exp ->
    let value (_, v) = v in
    match exp with
    | Value (t, v) -> (t, v)
    | Not x -> (Bool, not (value (eval x)))
    | And (x, y) -> (Bool, value (eval x) && value (eval y))
    | Equal (x, y) ->
        let (t, x') = eval x in
        let y' = value (eval y) in
        (Bool, equal t x' y')
    | Add (x, y) -> (Int, value (eval x) + value (eval y))

