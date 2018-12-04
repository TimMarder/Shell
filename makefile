all: main.o shell.o
	gcc -o shell shell.o main.o -lm

main.o: main.c shell.h
	gcc -c main.c

shell.o: shell.h shell.c
	gcc -c shell.c

clean:
	rm *.o
	rm *~

run:
	./shell
