#pragma once 
#include <stdio.h>
#include <ncurses.h>

#define WIDTH 30
#define HEIGHT 10

void main_menu();
void mode_menu(int mode);
void destroy_win(WINDOW *local_win);
void instruction (int mode);
void mode_menu_2 (int mode);
void print_menu(WINDOW* menu_win, int highlight,int n_choices, const char ** choices);
void testing (int mode);
