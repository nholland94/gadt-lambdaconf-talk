open Base

type 't type_ =
  | Int : int type_
  | Float : float type_

type ('src, 'dst) cast =
  | Unfix : (int, float) cast
  | Floor : (float, int) cast
  | Ceil : (float, int) cast

type 't ast =
  | Constant : 'a type_ * 'a -> 'a ast
  | Cast : 'a ast * ('a, 'b) cast -> 'b ast
  | Add : 'a ast * 'a ast -> 'a ast
  | Div : 'a ast * 'a ast -> float ast

let cast : type src dst. (src, dst) cast -> src -> dst =
  function
  | Unfix -> Int.to_float
  | Floor -> Float.(Fn.compose to_int round_down)
  | Ceil  -> Float.(Fn.compose to_int round_up)

let cast_result : type src dst. (src, dst) cast -> dst type_ =
  function
  | Unfix -> Float
  | Floor -> Int
  | Ceil  -> Int

let to_float : type t. t type_ * t -> float =
  fun (t, v) ->
    match t with
    | Int -> Int.to_float v
    | Float -> v

let arithmetic_op : type t. int:(int -> int -> int) -> float:(float -> float -> float) -> t type_ -> t -> t -> t =
  fun ~int ~float t x y ->
    match t with
    | Int   -> int x y
    | Float -> float x y

let rec eval : type t. t ast -> t type_ * t =
  fun ast ->
    match ast with
    | Constant (t, x) -> (t, x)
    | Cast (exp, c)   ->
        let (_, v) = eval exp in
        (cast_result c, cast c v)
    | Add (x, y)      -> 
        let (t, x') = eval x in
        let (_, y') = eval y in
        (t, arithmetic_op ~int:(+) ~float:(+.) t x' y')
    | Div (x, y)      ->
        let (t, x') = eval x in
        let (_, y') = eval y in
        (Float, (to_float (t, x')) /. (to_float (t, y')))

(* (int)(((float)9)/((float)2) + 3.5)
(* floor(9/2 + 3.5) *)
let example1 : int ast =
  Cast (
    Add (
      Div (Constant (Int, 9), Constant (Int, 2)),
      Constant (Float, 3.5) ),
    Floor)

(* examples of what you cannot do: *)
(* 3.5 + 1 = Add (Constant (Float, 3.5), Constant (Int, 1)) *)
