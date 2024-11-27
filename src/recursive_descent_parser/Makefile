all: main

main: include/comp2024.h include/lex.yy.h include/y.tab.h lib/libcomp2024.a lex.yy.c main.c y.tab.c
	gcc -g lex.yy.c main.c y.tab.c -o main -I./include -L./lib -lcomp2024

lib/libcomp2024.a: lib/src/comp2024.c
	gcc -c lib/src/comp2024.c -o lib/comp2024.o -I./include
	ar rcs lib/libcomp2024.a lib/comp2024.o
	rm -f lib/comp2024.o

zip: include lib/libcomp2024.a lex.yy.c main.c Makefile README.md y.tab.c
	zip -r main.zip include lib/libcomp2024.a lex.yy.c main.c Makefile README.md y.tab.c

clean: 
	rm -f main lib/libcomp2024.a main.zip
