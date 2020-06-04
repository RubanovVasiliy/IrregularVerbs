flags = -Wall -Werror
debug_flags = -Wall -Werror -g -O0

all: clean src

run: clean test
	./bin/t


#src

src: bin build/src build/src/main.o build/src/dictionary.o build/src/menu.o build/src/modes.o
	gcc $(flags) build/src/*.o  -o bin/v -lncursesw

build/src:
	mkdir -p build/src

build/src/main.o: src/main.c
	gcc $(flags) -c src/main.c -o build/src/main.o

build/src/dictionary.o: src/dictionary.c
	gcc $(flags) -c src/dictionary.c -o build/src/dictionary.o

build/src/menu.o: src/menu.c
	gcc $(flags) -c src/menu.c -o build/src/menu.o

build/src/modes.o: src/modes.c
	gcc $(flags) -c src/modes.c -o build/src/modes.o


#debug

debug: bin build/debug build/debug/main.o build/debug/dictionary.o build/debug/menu.o build/debug/modes.o
	gcc $(debug_flags) build/debug/*.o  -o bin/d -lncursesw

build/debug:
	mkdir -p build/debug

build/debug/main.o: src/main.c
	gcc $(debug_flags) -c src/main.c -o build/debug/main.o

build/debug/dictionary.o: src/dictionary.c
	gcc $(debug_flags) -c src/dictionary.c -o build/debug/dictionary.o

build/debug/menu.o: src/menu.c
	gcc $(debug_flags) -c src/menu.c -o build/debug/menu.o

build/debug/modes.o: src/modes.c
	gcc $(debug_flags) -c src/modes.c -o build/debug/modes.o


#test

test: src build/test build/test/main.o build/test/dictionary.o 
	gcc $(flags)  build/test/*.o build/src/dictionary.o -o bin/t -lncursesw

build/test:
	mkdir -p build/test

build/test/main.o: test/main.c
	gcc $(flags) -c test/main.c -o build/test/main.o

build/test/dictionary.o: test/dictionary.c
	gcc $(flags) -c test/dictionary.c -o build/test/dictionary.o



bin:
	mkdir -p bin

.PHONY: clean

clean:
	rm -rf build bin