run: build
	./osh.out
debug: build
	valgrind ./osh.out

build:
	gcc -Wall -Wextra -pedantic -std=c99 -o ./osh.out *.c
