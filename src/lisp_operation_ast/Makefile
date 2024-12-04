all: main

main: include/ast.h ast.c lex.yy.c main.c y.tab.c y.tab.h
	gcc -g ast.c lex.yy.c main.c y.tab.c -o main -I./include

lex.yy.c: lex.l
	flex lex.l

y.tab.c: yacc.y
	bison -d -y yacc.y

y.tab.h: yacc.y
	bison -d -y yacc.y

zip: include/ast.h ast.c lex.l main.c Makefile README.md yacc.y
	zip main.zip include/ast.h ast.c lex.l main.c Makefile README.md yacc.y

clean:
	rm -f main lex.yy.c y.tab.c y.tab.h main.zip
