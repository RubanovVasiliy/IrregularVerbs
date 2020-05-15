flags = -Wall -Werror

all: bin build bin/v

w: bin build bin/vw

bin/v: build/main.o build/func.o
	gcc $(flags) build/main.o build/dictionary.o build/menu.o build/modec.o -o bin/v -lncurses

bin/vw: build/main.o build/func.o
	gcc $(flags) build/main.o build/dictionary.o build/menu.o build/modec.o -o bin/vw -lncursesw

build/main.o: src/main.c
	gcc $(flags) -c src/main.c -o build/main.o

build/func.o: src/dictionary.c
	gcc $(flags) -c src/dictionary.c -o build/dictionary.o

build/func.o: src/menu.c
	gcc $(flags) -c src/menu.c -o build/menu.o

build/func.o: src/modes.c
	gcc $(flags) -c src/modes.c -o build/modes.o

bin:
	mkdir -p bin

build:
	mkdir -p build

.PHONY: clean

clean:
	rm -rf build bin