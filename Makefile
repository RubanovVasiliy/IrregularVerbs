flags = -Wall -Werror
debug_flags = -Wall -Werror -g -O0

all: clean build

build: bin build/src build/src/main.o build/src/dictionary.o build/src/menu.o build/src/modes.o
	gcc $(flags) build/src/*.o  -o bin/v -lncursesw

debug: bin build/debug build/debug/main.o build/debug/dictionary.o build/debug/menu.o build/debug/modes.o
	gcc $(debug_flags) build/debug/*.o  -o bin/d -lncursesw

run: all
	./bin/v

#src

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

build/test:
	mkdir -p build/test




bin:
	mkdir -p bin

.PHONY: clean

clean:
	rm -rf build bin