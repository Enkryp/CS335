run: a.out
	./a.out <a.java >out.dot
	# dot -Tpdf out.dot > out.pdf
a.out: parser.tab.c lex.yy.c 
	g++ parser.tab.c lex.yy.c
parser.tab.c: parser.y
	bison -tdv parser.y
lex.yy.c: lexer.l parser.tab.h
	flex lexer.l
parser_example: parser.y
	bison -tdv -Wcounterexamples parser.y 2> output

