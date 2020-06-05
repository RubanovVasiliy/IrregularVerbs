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
    y = 3;
    box(menu_win, 0, 0);

    for (i = 0; i < n_menu; ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } 
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }

    wrefresh(menu_win);
}

void main_menu()
{
    dictionary* d = calloc(sizeof(dictionary), 1);

    int code = fillDictionary(d);
    if (code == -1) {
        free(d);
        return;
    } 
    else if (code < 16) {
        free(d);
        printf("%s\n", "Словарь слишком мал!");
        return;
    }

    WINDOW* main_menu;

    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();
    int startx = (COLS - WIDTH) / 2;
    int starty = (LINES - HEIGHT) / 2;
    int n_main_menu = sizeof(start_menu) / sizeof(char*);
    main_menu = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(main_menu, TRUE);
    refresh();

    print_menu(main_menu, highlight, n_main_menu, start_menu);
    mvwprintw(main_menu, 1, 7, "%s", "IrregularVerbs:");
    curs_set(0);

    while (1) {
        c = wgetch(main_menu);
        switch (c) {
        case KEY_UP:
            if (highlight == 1)
                highlight = n_main_menu;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == n_main_menu)
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
            } 
            else if (highlight == 2) {
                instruction();
                clear();
                refresh();
            } 
            else {
                modes_test(d, highlight);
                clear();
                refresh();
            }
            refresh();
            break;
        default:
            refresh();
            break;
        }
        print_menu(main_menu, highlight, n_main_menu, start_menu);
        if (choice != 0)
            break;
    }

    clrtoeol();
    refresh();
    endwin();
    free(d);
}

void modes_test(dictionary* d, int mode)
{
    WINDOW* modes_test;

    int highlight = 1;
    int choice = 0;
    int c;

    clear();
    noecho();
    cbreak();
    int startx = (COLS - WIDTH) / 2;
    int starty = (LINES - HEIGHT) / 2;
    int n_menu_test = sizeof(menu_test) / sizeof(char*);
    modes_test = newwin(HEIGHT, WIDTH, starty, startx);
    mvwprintw(modes_test, 1, 2, "%s", "Выберите режим:");
    keypad(modes_test, TRUE);
    refresh();

    print_menu(modes_test, highlight, n_menu_test, menu_test);

    while (1) {
        c = wgetch(modes_test);
        switch (c) {
        case KEY_UP:
            if (highlight == 1)
                highlight = n_menu_test;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == n_menu_test)
                highlight = 1;
            else
                ++highlight;
            break;
        case KEY_F(1):
            choice = highlight;
            break;
        case 10:
            if (highlight == 4) {
                choice = highlight;
            } else {
                difficulty_test(d, highlight);
            }
            break;
        }
        print_menu(modes_test, highlight, n_menu_test, menu_test);
        if (choice != 0)
            break;
    }

    clrtoeol();
    refresh();
    destroy_win(modes_test);
}

void destroy_win(WINDOW* local_win)
{
    wrefresh(local_win);
    delwin(local_win);
}

void difficulty_test(dictionary* d, int mode)
{
    WINDOW* diff_test;

    int highlight = 1;
    int choice = 0;
    int c;

    clear();
    noecho();
    cbreak();
    int startx = (COLS - WIDTH) / 2;
    int starty = (LINES - HEIGHT) / 2;
    int n_diff_test = sizeof(menu_diff_test) / sizeof(char*);
    diff_test = newwin(HEIGHT, WIDTH, starty, startx);
    mvwprintw(diff_test, 1, 2, "%s", "Уровень сложности:");
    keypad(diff_test, TRUE);
    refresh();

    print_menu(diff_test, highlight, n_diff_test, menu_diff_test);

    while (1) {
        c = wgetch(diff_test);
        switch (c) {
        case KEY_UP:
            if (highlight == 1)
                highlight = n_diff_test;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == n_diff_test)
                highlight = 1;
            else
                ++highlight;
            break;
        case KEY_F(1):
            choice = highlight;
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
        }
        print_menu(diff_test, highlight, n_diff_test, menu_diff_test);
        if (choice != 0)
            break;
    }

    clrtoeol();
    refresh();
    destroy_win(diff_test);
}

void instruction()
{
    WINDOW* inst;

    int c;
    int highlight = 0;
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

void testing(dictionary* d, int mode, int level)
{
    WINDOW* test;

    int c;
    clear();
    cbreak();
    int startx = 0;
    int starty = 0;
    test = newwin(LINES, COLS, starty, startx);
    keypad(test, TRUE);
    refresh();
    wrefresh(test);

    if (mode == 1) {
        first_mode(test, d, level * 5);
    } else if (mode == 2) {
        second_mode(test, d, level * 5);
    } else if (mode == 3) {
        third_mode(test, d, level * 5);
    }
    while (1) {
        c = wgetch(test);
        switch (c) {
        case 10:
            break;
        }
        refresh();
        if (c == KEY_F(1))
            break;
    }
    
    clrtoeol();
    refresh();
    destroy_win(test);
}
