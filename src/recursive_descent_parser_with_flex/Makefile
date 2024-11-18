all: main

main: lex.yy.c main.c lib/libcomp2024.a
	gcc -g lex.yy.c main.c -o main -I./include -L./lib -lcomp2024

lex.yy.c: lex.l
	flex lex.l

lib/libcomp2024.a: lib/src/comp2024.c
	gcc -c lib/src/comp2024.c -o lib/comp2024.o -I./include
	ar rcs lib/libcomp2024.a lib/comp2024.o
	rm -f lib/comp2024.o

clean: 
	rm -f lex.yy.c main main.zip lib/libcomp2024.a

zip: lex.l lex.yy.h main.c Makefile include lib/libcomp2024.a
	zip -r main.zip lex.l lex.yy.h main.c Makefile include lib/libcomp2024.a
