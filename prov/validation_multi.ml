(* $region Handling Multiple Validation States *)
type block = ...
type ('time, 'transactions) block_with_validation =
  block * 'time * 'transactions
  constraint 'time = [`Time] * _ tbool
  constraint 'transactions = [`Transactions] * _ tbool

(* $region Example Validation Function *)
let validate_time :
     type transactions.
     ( [`Time] * false_ tbool
     , [`Transactions] * transactions tbool )
     block_with_validation
  -> ( [`Time] * true_ tbool
     , [`Transactions] * transactions tbool )
     block_with_validation =
  ...

(* $region Ignoring Validation *)
let get_block_parent_hash :
     type time transactions.
     ( [`Time] * time tbool
     , [`Transactions] * transactions tbool )
     block_with_validation
  -> block_hash =
  ...

(* $region Encapsulating Details *)
type time_validated_block =
  | At_least_time_validated :
         ( [`Time] * true_ tbool
         , [`Transactions] * 'a tbool )
         block_with_validation
      -> time_validated_block =
  ...
