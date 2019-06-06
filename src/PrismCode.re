let s = ReasonReact.string;

type language;
[@bs.deriving abstract]
// type prismjs = {
//   languages: Js.Dict.t(language),
//   highlight: string => language => array(string)
// };
// [@bs.val] [@bs.scope "window"] external prism: prismjs = "Prism";
[@bs.val] [@bs.scope ("window", "Prism")] external languages: Js.Dict.t(language) = "";
[@bs.val] [@bs.scope ("window", "Prism")] external highlight: string => language => string = "";

let component = ReasonReact.statelessComponent("Presentation");

let make = (~lang, ~code, _children) => {
  ...component,
  render: (_self) => {
    // let prism: prismjs =
    //   switch(Js.Dict.get(window, "Prism")) {
    //     | Some(x) => x
    //     | None    => failwith("prism not found")
    //   };
    let language =
      switch(Js.Dict.get(languages, lang)) {
        | Some(x) => x
        | None    => failwith("language not found")
      };
    let wrapLine = (index, line) =>
      <div key=string_of_int(index) dangerouslySetInnerHTML={ "__html": line } />;
    let lines = Array.mapi(wrapLine, Js.String.split("\n", highlight(code, language)));
    <code style=ReactDOMRe.Style.make(~display="inline-block", ~textAlign="left", ())>
      ...lines
    </code>
  }
};
