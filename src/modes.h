#pragma once
#include "dictionary.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void generate_rand(int** a, unsigned n, unsigned range);
int first_mode(WINDOW* win, Dictionary* d, int count);
int second_mode(Dictionary* d, int count);
int third_mode(Dictionary* d, int count);