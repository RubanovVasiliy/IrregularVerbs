#include "menu.h"
#include "dictionary.h"
#include "menu_context.h"
#include "modes.h"
#include <ncurses.h>
#include <stdio.h>

void print_menu(WINDOW* menu_win, int highlight, int n_menu, const char** choices)
{
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (i = 0; i < n_menu; ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}

void main_menu()
{
    Dictionary* d = malloc(sizeof(Dictionary));
    fillDictionary(d);
    WINDOW* menu_win;
    int highlight = 1;
    int choice = 0;
    int c;
    initscr();
    clear();
    noecho();
    cbreak();
    int startx = (80 - WIDTH) / 2;
    int starty = (24 - HEIGHT) / 2;
    int n_menu = sizeof(menu) / sizeof(char*);
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);

    refresh();
    print_menu(menu_win, highlight, n_menu, menu);
    while (1) {
        c = wgetch(menu_win);
        switch (c) {
        case KEY_UP:
            if (highlight == 1)
                highlight = n_menu;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == n_menu)
                highlight = 1;
            else
                ++highlight;
            break;
        case KEY_F(1):
            choice = highlight;
            break;
        case 10:
            if (highlight == 3) {
                choice = highlight;
            } else if (highlight == 2) {
                instruction();
                clear();
                refresh();
            } else {
                mode_menu(d, highlight);
                clear();
                refresh();
            }
            refresh();
            break;
        default:
            refresh();
            break;
        }
        print_menu(menu_win, highlight, n_menu, menu);
        if (choice != 0)
            break;
    }
    clrtoeol();
    refresh();
    endwin();
}

void mode_menu(Dictionary* d, int mode)
{
    WINDOW* menu_2;
    int highlight = 1;
    int choice = 0;
    int c;

    clear();
    noecho();
    cbreak();
    int startx = (80 - WIDTH) / 2;
    int starty = (24 - HEIGHT) / 2;
    int n_menu2 = sizeof(menu2) / sizeof(char*);
    menu_2 = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_2, TRUE);
    refresh();
    print_menu(menu_2, highlight, n_menu2, menu2);
    while (1) {
        c = wgetch(menu_2);
        switch (c) {
        case KEY_UP:
            if (highlight == 1)
                highlight = n_menu2;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == n_menu2)
                highlight = 1;
            else
                ++highlight;
            break;
        case 10:
            if (highlight == 4) {
                choice = highlight;
            } else {
                mode_menu_2(d, highlight);
            }

            break;
        default:
            mvprintw(24, 0, "Hopefully it can be printed as '%c'. Select the field you need and press ENTER", c);
            refresh();
        }
        print_menu(menu_2, highlight, n_menu2, menu2);
        if (choice != 0)
            break;
    }
    clrtoeol();
    refresh();
    destroy_win(menu_2);
}

void destroy_win(WINDOW* local_win)
{
    wrefresh(local_win);
    delwin(local_win);
}

void mode_menu_2(Dictionary* d, int mode)
{
    WINDOW* menu_3;
    int highlight = 1;
    int choice = 0;
    int c;
    clear();
    noecho();
    cbreak();
    int startx = (80 - WIDTH) / 2;
    int starty = (24 - HEIGHT) / 2;
    int n_menu3 = sizeof(menu3) / sizeof(char*);
    menu_3 = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_3, TRUE);
    refresh();
    print_menu(menu_3, highlight, n_menu3, menu3);
    while (1) {
        c = wgetch(menu_3);
        switch (c) {
        case KEY_UP:
            if (highlight == 1)
                highlight = n_menu3;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == n_menu3)
                highlight = 1;
            else
                ++highlight;
            break;
        case 10:
            if (highlight == 4) {
                choice = highlight;
            } else {
                testing(d, mode, highlight);
                clear();
                refresh();
            }
            break;
        default:
            mvprintw(24, 0, "Hopefully it can be printed as '%c'. Select the field you need and press ENTER", c);
            refresh();
        }
        print_menu(menu_3, highlight, n_menu3, menu3);
        if (choice != 0)
            break;
    }
    clrtoeol();
    refresh();
    destroy_win(menu_3);
}

void instruction()
{
    int c;
    int highlight = 0;
    WINDOW* inst;
    clear();
    noecho();
    cbreak();
    int startx = 0;
    int starty = 0;
    int n_instruct = sizeof(instruct) / sizeof(char*);
    inst = newwin(LINES, COLS, starty, startx);
    keypad(inst, TRUE);
    refresh();
    print_menu(inst, highlight, n_instruct, instruct);
    wrefresh(inst);
    while (1) {
        c = wgetch(inst);
        switch (c) {
        case 10:
            break;
        }
        refresh();
        if (c != 0)
            break;
        clrtoeol();
    }
    clrtoeol();
    refresh();
    destroy_win(inst);
}

void testing(Dictionary* d, int mode, int level)
{
    int c;
    WINDOW* test;
    clear();
    cbreak();
    int startx = 0;
    int starty = 0;
    test = newwin(LINES, COLS, starty, startx);
    keypad(test, TRUE);

    refresh();
    wprintw(test, "\nTest\n");
    wrefresh(test);
    if (mode == 1) {
        first_mode(test, d, level * 5);
    } else if (mode == 2) {

    } else if (mode == 3) {
    }

    while (1) {
        c = wgetch(test);
        switch (c) {
        case 10:
            break;
        }
        refresh();
        if (c != 0)
            break;
        clrtoeol();
    }
    clrtoeol();
    refresh();
    destroy_win(test);
}