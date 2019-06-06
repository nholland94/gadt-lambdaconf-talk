type true_
type false_
type 'a tbool =
  | True : true_ tbool
  | False : false_ tbool
type true_tbool = true_ tbool
type flase_tbool = false_ tbool

type ('a, 'b, 'r) xor =
  | TF : (true_, false_, true_) xor
  | FT : (false_, true_, true_) xor
  | TT : (true_, true_, false_) xor
  | FF : (false_, false_, false_) xor
type ('a, 'b) xor_ex =
  | Xor_ex : ('a, 'b, 'r) xor -> ('a, 'b) xor_ex

let calculate_xor :
     type a b.
     a tbool * b tbool
  -> (a, b) xor_ex =
  function
  | (True, True)   -> Xor_ex TT
  | (True, False)  -> Xor_ex TF
  | (False, True)  -> Xor_ex FT
  | (False, False) -> Xor_ex FF

type ('a, 'b) work_status =
  | Work_status : 'a tbool * 'b tbool -> ('a, 'b) work_status

type ('a, 'b, 'r) xor_result = 'r
  constraint _ = ('a, 'b, 'r) xor

let decons_work_status :
     type first second.
     (first, second) work_status
  -> first tbool * second tbool =
  fun (Work_status (a, b)) -> (a, b)

let do_first :
     type second.
     (false_, second) work_status
  -> (true_, second) work_status =
  function
  | Work_status (False, b) -> Work_status (True, b)
  | _ -> .

let do_second :
     type first.
     (first, false_) work_status
  -> (first, true_) work_status =
  function
  | Work_status (b, False) -> Work_status (b, True)
  | _ -> .

type ('a, 'b, 'r) work_status_xor = ('a, 'b) work_status *  ('a, 'b, 'r) xor

let do_other :
     type first second.
     (first, second, true_) work_status_xor
  -> (true_, true_) work_status =
  fun work_status ->
    match work_status with
    | (Work_status (False, True), _) ->
        do_first (fst work_status)
    | (Work_status (True, False), _) ->
        do_second (fst work_status)
    | _ -> .

let _ =
  let work_status = Work_status (True, False) in
  let Xor_ex xor = calculate_xor (decons_work_status work_status) in
  do_other (work_status, xor)
