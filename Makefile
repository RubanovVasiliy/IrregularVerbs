flags = -Wall -Werror

all: bin build bin/v

bin/v: build/main.o build/dictionary.o build/menu.o build/modes.o
	gcc $(flags) build/main.o build/dictionary.o build/menu.o build/modes.o -o bin/vw -lncursesw

build/main.o: src/main.c
	gcc $(flags) -c src/main.c -o build/main.o

build/dictionary.o: src/dictionary.c
	gcc $(flags) -c src/dictionary.c -o build/dictionary.o

build/menu.o: src/menu.c
	gcc $(flags) -c src/menu.c -o build/menu.o

build/modes.o: src/modes.c
	gcc $(flags) -c src/modes.c -o build/modes.o

bin:
	mkdir -p bin

build:
	mkdir -p build

.PHONY: clean

clean:
	rm -rf build bin