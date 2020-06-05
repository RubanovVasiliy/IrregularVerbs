#pragma once
#include "dictionary.h"
#include <ncurses.h>
#include <stdio.h>

#define WIDTH 30
#define HEIGHT 10

void main_menu();
void modes_test(Dictionary* d, int mode);
void destroy_win(WINDOW* local_win);
void instruction();
void mode_menu_2(Dictionary* d, int mode);
void print_menu(
        WINDOW* menu_win, int highlight, int n_choices, const char** choices);
void testing(Dictionary* d, int mode, int level);
