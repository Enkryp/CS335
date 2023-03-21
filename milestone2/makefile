a.out: parser.tab.c lex.yy.c 
	g++ -w parser.tab.c lex.yy.c -o a.out
parser.tab.c: parser.y
	bison -tdv parser.y
lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

