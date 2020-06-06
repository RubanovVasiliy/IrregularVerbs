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

int list_free(List* head);
int list_print(List* node);
int list_wprint(WINDOW* win, List* node);
int dictionary_print(Dictionary* d);
int dictionary_wprint(WINDOW* win, Dictionary* d);
int dictionary_delete(Dictionary* d);
int dictionary_fill(Dictionary* d);
List* list_createnode(char* key, int value);
List* list_lookup(List* list, char* key);
List* list_search(List* node, int value);
List* list_addend(List* node, char* key, int value);
List* list_delete(List* list);
