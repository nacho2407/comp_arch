all: main

main: main.c lib/libcomp2024.a
	gcc -g main.c -o main -I./include -L./lib -lcomp2024

lib/libcomp2024.a: lib/src/comp2024.c
	gcc -c lib/src/comp2024.c -o lib/comp2024.o -I./include
	ar rcs lib/libcomp2024.a lib/comp2024.o
	rm -f lib/comp2024.o

clean: 
	rm -f main main.zip lib/libcomp2024.a

zip: main.c Makefile include lib/libcomp2024.a
	zip -r main.zip main.c Makefile include lib/libcomp2024.a
