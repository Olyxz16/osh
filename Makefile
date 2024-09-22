run: build
	./osh.out

debug: build-debug
	valgrind ./osh.out
debug-trace: build-debug
	valgrind --track-origins=yes -s ./osh.out
debug-leak: build-debug
	valgrind --leak-check=full ./osh.out

build:
	gcc -Wall -Wextra -pedantic -std=c99 -o ./osh.out *.c
build-debug:
	gcc -g -Wall -Wextra -pedantic -std=c99 -o ./osh.out *.c

clean:
	rm *.out
	rm *.o
