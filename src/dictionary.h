#pragma once
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    char* key;
    int value;
    struct List* next;
} List;

typedef struct Dictionary {
    List* lines[45];
    int count;
} Dictionary;

int free_list(List* head);
int list_print(List* node);
int print_dictionary(Dictionary* d);
int wlist_print(WINDOW* win, List* node);
int wprint_dictionary(WINDOW* win, Dictionary* d);
List* list_delete(List* list);
int delete_dictionary(Dictionary* d);
int fill_dictionary(Dictionary* d);
List* list_createnode(char* key, int value);
List* list_lookup(List* list, char* key);
List* list_search(List* node, int value);
List* list_addend(List* node, char* key, int value);
