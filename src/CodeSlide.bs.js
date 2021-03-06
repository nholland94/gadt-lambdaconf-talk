// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var Js_null_undefined = require("bs-platform/lib/js/js_null_undefined.js");
var SpectacleCodeSlideJs = require("./SpectacleCodeSlide.js");

function make(lang, code, ranges, showLineNumbers, className, children) {
  return ReasonReact.wrapJsForReason(SpectacleCodeSlideJs.default, {
              lang: lang,
              code: code,
              ranges: ranges,
              showLineNumbers: Js_null_undefined.fromOption(showLineNumbers),
              className: Js_null_undefined.fromOption(className),
              style: {
                maxWidth: "none"
              }
            }, children);
}

exports.make = make;
/* ReasonReact Not a pure module */
