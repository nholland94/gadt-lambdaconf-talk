(* $region Type Level Boolean *)
type true_
type false_
type 'a tbool =
  | True : true_ tbool
  | False : false_ tbool
type true_tbool = true_ tbool
type flase_tbool = false_ tbool

(* $region Type Level Validation *) 
type block = ...
type 'a block_with_validation =
  | Block_with_validation : block * 'a tbool -> 'a block_with_validation

(* $region Interface Examples *)
let validate_block :
     false_ block_with_validation
  -> true_ block_with_validation =
  ...

(* $region Interface Examples *)
let accept_block :
     true_ block_with_validation
  -> unit =
  ...

(* $region Interface Examples *)
let get_block_parent_hash :
     type valid.
     valid block_with_validation
  -> block_hash =
  ...

