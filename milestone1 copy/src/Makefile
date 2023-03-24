myASTGenerator: parser.tab.c lex.yy.c 
	g++ parser.tab.c lex.yy.c -o myASTGenerator
parser.tab.c: parser.y structs.h conversion.h
	bison -tdv parser.y
lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

