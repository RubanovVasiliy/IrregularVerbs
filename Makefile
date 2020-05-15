all:
	gcc -Wall -o res main.c Dictionary.c modes.c -lm
debug:
	gcc -Wall -g3 -O0 -o debug main.c Dictionary.c modes.c -lm
clear:
	rm -rf main
	rm -rf debug

