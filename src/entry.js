import Prism from 'prismjs';
// import './prism-theme.css'
import 'prism-themes/themes/prism-vs.css'
import 'prismjs/components/prism-ocaml'
import 'prismjs/components/prism-markup-templating'
window.Prism = Prism;
import './main.css'; // eslint-disable-line import/first
import main from './Main.bs.js'; // eslint-disable-line import/first

main();
