flags = -Wall -Werror

all: bin build bin/v

bin/v: build/src/main.o build/src/dictionary.o build/src/menu.o build/src/modes.o
	gcc $(flags) build/src/main.o build/src/dictionary.o build/src/menu.o build/src/modes.o -o bin/v -lncursesw

build/src/main.o: src/main.c
	gcc $(flags) -c src/main.c -o build/src/main.o

build/src/dictionary.o: src/dictionary.c
	gcc $(flags) -c src/dictionary.c -o build/src/dictionary.o

build/src/menu.o: src/menu.c
	gcc $(flags) -c src/menu.c -o build/src/menu.o

build/src/modes.o: src/modes.c
	gcc $(flags) -c src/modes.c -o build/src/modes.o

bin:
	mkdir -p bin

build:
	mkdir -p build/src
	mkdir -p build/test

.PHONY: clean

clean:
	rm -rf build bin