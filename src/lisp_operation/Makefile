all: main

main: lex.yy.c main.c y.tab.c y.tab.h
	gcc -g lex.yy.c main.c y.tab.c -o main

lex.yy.c: lex.l
	flex lex.l

y.tab.c: yacc.y
	bison -dy yacc.y

y.tab.h: yacc.y
	bison -dy yacc.y

zip: lex.l main.c Makefile README.md yacc.y
	zip main.zip lex.l main.c Makefile README.md yacc.y

clean:
	rm -f main lex.yy.c y.tab.c y.tab.h main.zip
