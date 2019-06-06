[@bs.module("./SpectacleCodeSlide.js")] external reactClass: ReasonReact.reactClass = "default";

[@bs.deriving abstract]
type image;

[@bs.deriving abstract]
type range = {
  loc: array(int),
  // TODO: title and note could be elements or strings
  [@bs.optional] title: string,
  [@bs.optional] note: string,
  [@bs.optional] image: image
};

[@bs.deriving abstract]
type jsProps = {
  lang: string,
  code: string,
  ranges: array(range),
  showLineNumbers: Js.nullable(bool),
  className: Js.nullable(string),
  style: ReactDOMRe.Style.t
};

let make = (~lang, ~code, ~ranges, ~showLineNumbers=?, ~className=?, children) => {
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=jsProps(
      ~lang,
      ~code,
      ~ranges,
      ~showLineNumbers=Js.Nullable.fromOption(showLineNumbers),
      ~className=Js.Nullable.fromOption(className),
      ~style=ReactDOMRe.Style.make(~maxWidth="none", ())
    ),
    children
  )
};
