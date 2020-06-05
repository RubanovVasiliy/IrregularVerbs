#pragma once
#include "dictionary.h"
#include <ncurses.h>
#include <stdio.h>

#define WIDTH 30
#define HEIGHT 10

void main_menu();
void modes_test(dictionary* d, int mode);
void destroy_win(WINDOW* local_win);
void instruction();
void difficulty_test(dictionary* d, int mode);
void print_menu(
        WINDOW* menu_win, int highlight, int n_choices, const char** choices);
void testing(dictionary* d, int mode, int level);
