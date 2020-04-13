#pragma once
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

int listprint(List* node);
int printDictionary(Dictionary* d);
int fillDictionary(Dictionary* d);
List* list_createnode(char* key, int value);
List* list_lookup(List* list, char* key);
List* list_addend(List* node, char* key, int value);
void generate_rand(int** a, unsigned n, unsigned range);