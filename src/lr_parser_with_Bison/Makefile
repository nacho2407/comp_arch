all: main

main: main.c lex.yy.c y.tab.c y.tab.h
	gcc -g main.c lex.yy.c y.tab.c -o main

lex.yy.c: lex.l
	flex lex.l

y.tab.c: yacc.y
	bison -d -y yacc.y

y.tab.h: yacc.y
	bison -d -y yacc.y

clean:
	rm -f lex.yy.c main main.zip y.tab.c y.tab.h

zip: lex.l main.c Makefile yacc.y
	zip main.zip lex.l main.c Makefile yacc.y
