open BsSpectacle;
let s = ReasonReact.string;

module Image = {
  type t = CodeSlide.image;

  [@bs.module] external btree_adt_example: t = "../prov/btree_adt_example.dot.png";
}

module Code = {
  [@bs.deriving abstract]
  type t = {
    [@bs.as "source"] source: string,
    [@bs.as "ranges"] ranges: array(CodeSlide.range)
  };

  [@bs.module] external bbtree: t = "../prov/bbtree.ml";
  [@bs.module] external exp: t = "../prov/exp.ml";
  [@bs.module] external hlist: t = "../prov/hlist.ml";
  [@bs.module] external peano: t = "../prov/peano.ml";
  [@bs.module] external take_five: t = "../prov/take_five.ml";
  [@bs.module] external vect: t = "../prov/vect.ml";
  [@bs.module] external validation_multi: t = "../prov/validation_multi.ml";
  [@bs.module] external validation_single: t = "../prov/validation_single.ml";
  [@bs.module] external vect_reduce: t = "../prov/vect_reduce.ml";

  let cons = (code) =>
    <CodeSlide
      lang="ocaml"
      showLineNumbers=true
      code=sourceGet(code)
      ranges=rangesGet(code) />
}

module InlineCode = {
  let string_fold = (f: 'a => char => 'a, init: 'a, str: string) => {
    let length = String.length(str);
    let rec loop = (acc, i) => {
      if(i >= length) {
        acc
      } else {
        loop(f(acc, String.get(str, i)), i + 1)
      }
    };
    loop(init, 0)
  }

  let count_lines = {
    let f = (acc, c) => { if(c == '\n') { acc + 1 } else { acc }};
    string_fold(f, 1)
  };

  let cons = (~title, ~image=?, source) => {
    let ranges = [|CodeSlide.range(~loc=[|0, count_lines(source)|], ~title, ~image=?image, ())|];
    <CodeSlide
      lang="ocaml"
      showLineNumbers=true
      code={source ++ "\n"}
      ranges />
  }
}

let make = (_children) => {
  ...ReasonReact.statelessComponent("Presentation"),
  render: (_self) => {
    // <Deck transition=[|Slide|] progress=`pacman controls=false showFullscreenControl=false theme>
    <Deck transition=[|Slide|] progress=`pacman controls=false theme=SpectacleTheme.t>
      <Slide>
        <Heading size=1 textColor="black">(s("GADTs and You"))</Heading>
        <Heading size=2>(s("Writing Safer Code Using GADTs"))</Heading>
        <Text> <S type_=`italic>(s("Nathan Holland"))</S> </Text>
        <Notes>
          <ul>
            <li>(s("self introduction"))</li>
          </ul>
        </Notes>
      </Slide>

      <Slide>
        <Heading size=1 textColor="black">(s("GADT"))</Heading>
        <Heading size=2>(s("Generalized Algebraic Data Type"))</Heading>
        <Notes>
          <ul>
            <li>(s("GADT = Generalized Algebraic Data Type"))</li>
            <li>(s("GADTs provide a way to reason about types on a per constructor basis (if you don't know what this means, don't worry; we'll build it up)"))</li>
            <li>(s("GADTs are available for use in Haskell and OCaml"))</li>
            <li>(s("This presentation will be in OCaml, but everything here should work in other languages with GADTs"))</li>
          </ul>
        </Notes>
      </Slide>

      <Slide>
        <Text>(s("What can we do with GADTs?"))</Text>
        <List>
          <ListItem>(s("add invariants to data structures at a type level"))</ListItem>
          <ListItem>(s("restrict what values of a type can be passed into our functions"))</ListItem>
          <ListItem>(s("encode simple logic into the type system"))</ListItem>
          <ListItem>(s("enables certain run time representation optimizations"))</ListItem>
        </List>
        <Notes>(s("for the purposes of this talk, we will be focusing on #1 and #2"))</Notes>
      </Slide>

      <Slide> <Heading>(s("An introduction to types in OCaml"))</Heading> </Slide>

      <CodeSlide
        lang="ocaml"
        code={"\
(* basic types include: int, float, string *)
type string_and_int = string * int

type int_operation = int -> int -> int

let add : int -> int -> int = fun x y -> x + y
let add (x : int) (y : int) : int = x + y
let add x y = x + y
let add = (+)

type 'a list
type 'a pair = 'a * 'a

let reduce_pair : ('a -> 'a -> 'a) -> 'a pair -> 'a =
  fun f (x, y) -> f x y
    
let f : type a. a list -> int = ..."}
        ranges=[|
          CodeSlide.range(~loc=[|0, 2|], ~title="Basic Types", ()),
          CodeSlide.range(~loc=[|3, 4|], ~title="Function Types", ()),
          CodeSlide.range(~loc=[|5, 9|], ~title="Function Definitions", ()),
          CodeSlide.range(~loc=[|10, 15|], ~title="Parametric Polymorphism", ()),
          CodeSlide.range(~loc=[|16, 17|], ~title="Universal Quantification", ())
        |] />

      <Slide> <Heading>(s("A Review of ADTs"))</Heading> </Slide>

      {InlineCode.cons(~title="Basic ADT", "\
type example =
  | A
  | B of int
  | C of string * float

let something : example = C (\"hello\", 3.14)")}

      {InlineCode.cons(~title="List ADT", "\
type 'a list =
  | []
  | (::) of 'a * 'a list

let empty : 'a list = []
let fibs : int list = [0; 1; 1; 2; 3; 5; 8; 13]")}

      {InlineCode.cons(~title="Binary Tree ADT", ~image=Image.btree_adt_example, "\
type 'a btree =
  | Leaf of 'a
  | Branch of 'a * 'a btree * 'a btree

let sorted_tree : int btree =
  Branch (25,
    Branch (15, Leaf 5, Leaf 17),
    Leaf 64)")}

      <Slide>
        <Heading>(s("Limitations of ADTs"))</Heading>
        <Notes>(s("ADTs are great, but since every constructor for an ADT has the exact same type, we can't reason about types encapsulated by ADT constructors"))</Notes>
      </Slide>

      {InlineCode.cons(~title="ADT Expression Tree", "\
type value =
  | Int of int
  | Bool of bool

type exp =
  | Value of value
  | Not of exp
  | And of exp * exp
  | Add of exp * exp
  | Equal of exp * exp")}

      {InlineCode.cons(~title="Safety Issues", "\
(* 2 + 3 *)
let test1 : exp =
  Add (Value (Int 2), Value (Int 3))

(* 5 && true *)
let test2 : exp =
  And (Value (Int 5), Value (Bool true))

(* 2 + (5 = 3) *)
let test3 : exp =
  Add (Value (Int 2), Equal (Value (Int 5), Value (Int 3)))")}

      <CodeSlide
        lang="ocaml"
        code={"\
(* 5 *)
let test1 : int exp = Value (Int, 5)

(* 5 = 3 *)
let test2 : bool exp = Equal (Value (Int, 5), Value (Int, 3))

(* 2 + (5 = 3) *)
let test3 : _ exp =
  Add (Value (Int, 2), Equal (Value (Int, 5), Value (Int, 3)))
(* type error! *)"}
        ranges=[|
          CodeSlide.range(~loc=[|0, 5|], ~title="If We Had Used a GADT...", ()),
          CodeSlide.range(~loc=[|6, 10|], ~title="If We Had Used a GADT...", ())
        |] />

      // -- sum up: hopefully this gives you a concept of the power of gadts, but before we get to how these examples are implemented, let's go over some more fundamental gadt constructions first

      <Slide>
        <Heading>(s("Basic GADT Constructions"))</Heading>
        <Notes>
          <ul>
            <li>(s("now that we have a basic understanding of what GADTs give us, let's start looking at some basic constructions"))</li>
            <li>(s("we are going to start very simple -- this means that our first couple of constructions may not seem immediately useful, but worry not; they will be later"))</li>
          </ul>
        </Notes>
      </Slide>

      // A type witness is a GADT that defines a direct mapping between its constructors and the type parameter of the GADT
      // In a sense, this allows us to "reflect" information about our constructor into the type system
      // The language understands here that the only possible inhabitants of the type parameter are int and float
      {InlineCode.cons(~title="Type Witness", "\
type 'a witness =
  | Int : int witness
  | Float : float witness")}

      {InlineCode.cons(~title="Recursive Type Witness", "\
type 'a witness =
  | Int : int witness
  | Float : float witness
  | List : 'a witness -> ('a list) witness")}

      {InlineCode.cons(~title="ADT Peano Numbers", "\
type peano =
  | Zero
  | Succ of peano

let zero = Zero
let one = Succ Zero
...
let four = Succ (Succ (Succ (Succ Zero)))")}

      {Code.cons(Code.peano)}
      {Code.cons(Code.vect)}
      {Code.cons(Code.hlist)}

      <Slide>
        <Heading>(s("\"Value Safe\" Functions Using GADTs"))</Heading>
        <Notes>
          <ul>
            <li>(s("now that we have exposed some type parameters from our ADT definitions using GADTs, we can express type level restrictions"))</li>
            <li>(s("value safe function = function with compile time limitations what values can be passed into it"))</li>
          </ul>
        </Notes>
      </Slide>

      {Code.cons(Code.take_five)}
      {Code.cons(Code.vect_reduce)}

      <Slide> <Heading>(s("Adding Invariants to Data Structures"))</Heading> </Slide>

      {Code.cons(Code.bbtree)}

      <Slide>
        <Heading>(s("Encoding Restrictions on Application Logic"))</Heading>
        <Notes>
          <ul>
            <li>(s("let's move on to a more practical example that's a little easier to see how it can be useful"))</li>
            <li>(s("the problem and solution we will review is related to my work on Coda, and is an existing solution we use today to make our code safer"))</li>
          </ul>
        </Notes>
      </Slide>

      <Slide>
        <Heading size=3>(s("Problem: Block Validation"))</Heading>
        <List>
          <ListItem>(s("blocks can be received in a variety of ways (in multiple code paths)"))</ListItem>
          <List>
            <ListItem>(s("new blocks are gossiped over p2p network"))</ListItem>
            <ListItem>(s("missing blocks are requested from neighbors"))</ListItem>
            <ListItem>(s("..."))</ListItem>
          </List>
          <ListItem>(s("need to validate certain properties of blocks before we can safely do things with them"))</ListItem>
          <ListItem>(s("different actions require different validations"))</ListItem>
          <ListItem>(s("ordering of validation may be different in some code paths"))</ListItem>
        </List>
        <Notes>(s("INTRO: if you don't know what a blockchain is -- it's basically just a decentralized reverse link list data structure"))</Notes>
      </Slide>

      <Slide>
        <Heading size=2>(s("Naive Solution"))</Heading>
        <List>
          <ListItem>(s("analyze all possible traversals through validation states (model validation as an FSM)"))</ListItem>
          <ListItem>(s("create an abstract, concretely equivalent type representations for each level validation in reachable validation states"))</ListItem>
          <ListItem>(s("redefine boilerplate functions for each type representation"))</ListItem>
          <ListItem>(s("populate our restricted functions with the correct type representation associated with the required level of validation"))</ListItem>
        </List>
        <Notes>
          <p>(s("issues:"))</p>
          <ul>
            <li>(s("functions can't express optional validation at type level, meaning we need to provide a bunch of identity functions that define mappings between our abstract types for lowering validation"))</li>
            <li>(s("none of this scales well every arc in our FSM requires mapping functions and every state requires abstract types and boilerplate definitions"))</li>
          </ul>
        </Notes>
      </Slide>

      <Slide>
        <Heading size=2>(s("A Better Solution"))</Heading>
        <List>
          <ListItem>(s("expose each validation state as individual type parameters"))</ListItem>
          <ListItem>(s("implement a single function for each validation computation"))</ListItem>
          <ListItem>(s("use universal quantification in our restricted functions to express optional validation states"))</ListItem>
        </List>
        <Notes>(s("much better -- though let's start simple and just begin with implementing a single validation state"))</Notes>
      </Slide>

      {Code.cons(Code.validation_single)}
      {Code.cons(Code.validation_multi)}

      <Slide>
        <Heading>(s("Full Circle"))</Heading>
        <Text>(s("Implementing an Expression Tree as a GADT"))</Text>
        <Notes>(s("let's revisit the original example of expression trees"))</Notes>
      </Slide>

      {Code.cons(Code.exp)}

      <Slide>
        <Heading>(s("Limitations of GADTs"))</Heading>
        <Notes>
          <ul>
            <li>(s("often limits ability to do tail recursion"))</li>
            <li>(s("some techniques can require extra allocations for unused runtime values in order to express a proof"))</li>
            <li>(s("limited scope of applications compared to proper dependent types (but you can get it in your programming language todayi"))</li>
          </ul>
        </Notes>
      </Slide>

      // <Slide>
      //   <Heading>(s("GADTs: Friend or Foe?"))</Heading>
      //   <Notes>
      //     <ul>
      //       <li>(s("one argument against GADTs is that they are complex and can cause confusing type errors"))</li>
      //       <li>(s("yet the strengths are just too good to be ignored"))</li>
      //       <li>(s("best use case"))</li>
      //     </ul>
      //   </Notes>
      // </Slide>

      <Slide>
        <Heading>(s("Conclusions"))</Heading>
        <Notes>
          <ul>
            <li>(s("GADTs are extremely useful for certain things, but knowing how and when to use them effectively can be tricky"))</li>
            <li>(s("My recommendation: just start trying to use them for personal projects, and learn the techniques and limitations yourself"))</li>
            <li>(s("The End"))</li>
          </ul>
        </Notes>
      </Slide>
    </Deck>
  }
};
