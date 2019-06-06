[@bs.deriving abstract]
type customStyles = {
  background: string
};

[@bs.deriving abstract]
type customStyleSet = {
  body: customStyles
};

[@bs.deriving abstract]
type customStylesOuter = {
  global: customStyleSet
};

[@bs.module("spectacle-theme-nova")] external createTheme: string => customStylesOuter => BsSpectacle.Theme.theme = "default";

let custom = customStylesOuter(
  ~global = customStyleSet(
    ~body = customStyles(~background="white")
  )
);

let t = createTheme("avon", custom);
