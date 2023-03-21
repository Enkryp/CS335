a.out: parser_1st.tab.c lex.yy.c 
	g++ -w parser_1st.tab.c lex.yy.c -o a.out
parser.tab.c: parser_1st.y
	bison -tdv parser_1st.y
lex.yy.c: lexer.l parser_1st.tab.h
	flex lexer.l

