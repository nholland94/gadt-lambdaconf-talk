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

let component = ReasonReact.statelessComponent("BigCode");

let make = (~title, ~code, _children) => {
  ...component,
  render: (_self) => {
    let ranges = [|CodeSlide.range(~loc=[|0, count_lines(code)|], ~title, ())|];
    <CodeSlide lang="ocaml" className="big-code" showLineNumbers=true ranges code />
  }
}
