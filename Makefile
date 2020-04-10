all:
	gcc -Wall -o res main.c Dictionary.c -lm
debug:
	gcc -Wall -g3 -O0 -o debug main.c Dictionary.c -lm
clear:
	rm -rf main
	rm -rf debug

