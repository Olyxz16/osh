run: build
	./osh.out

debug: build
	valgrind ./osh.out
debug-trace: build
	valgrind --track-origins=yes -s ./osh.out
debug-leak: build
	valgrind --leak-check=full ./osh.out

build:
	gcc -Wall -Wextra -pedantic -std=c99 -o ./osh.out *.c

clean:
	rm *.out
	rm *.o
