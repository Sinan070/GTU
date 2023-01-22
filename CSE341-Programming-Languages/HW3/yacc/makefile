run:
	yacc -d gpp_parser.y
	flex gpp_lexer.l
	gcc y.tab.c lex.yy.c
	./a.out
