#pragma once
#include "dictionary.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void generate_rand(int** a, unsigned n, unsigned range);
int firstMode(WINDOW* win, Dictionary* d, int count);
int secondMode(Dictionary* d, int count);
int thirdMode(Dictionary* d, int count);