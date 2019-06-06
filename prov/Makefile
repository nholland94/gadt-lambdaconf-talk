all: all_byte all_png
all_byte: $(patsubst %.ml,%.byte,$(wildcard *.ml))
all_png: $(addsuffix .png,$(wildcard *.dot))

%.dot.png: %.dot
	dot -Tpng $< > $@

%.byte: %.ml
	ocamlfind ocamlc -package base -linkpkg -o $@ $<

%.utop: %.ml
	utop -init <(echo '#use "$<"')
