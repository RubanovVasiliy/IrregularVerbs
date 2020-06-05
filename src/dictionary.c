#include "dictionary.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int list_print(List* node)
{
    if (!node) {
        return -1;
    }

    List* ptr = node;
    do {
        printf("%2d %-10s", ptr->value, ptr->key);
        ptr = ptr->next;
    } while (ptr != NULL);
    return 0;
}

int print_dictionary(Dictionary* d)
{
    if (!d) {
        return -1;
    }
    for (int i = 0; i < d->count; i++) {
        list_print(d->lines[i]);
        printf("\n");
    }
    return 0;
}

int wlist_print(WINDOW* win, List* node)
{
    if (!node) {
        return -1;
    }

    List* ptr = node;
    do {
        wprintw(win, "%2d %-10s", ptr->value, ptr->key);
        ptr = ptr->next;
    } while (ptr != NULL);
    return 0;
}

int wprint_dictionary(WINDOW* win, Dictionary* d)
{
    if (!d) {
        return -1;
    }
    for (int i = 0; i < d->count; i++) {
        wlist_print(win, d->lines[i]);
        wprintw(win, "\n");
    }
    return 0;
}

List* list_createnode(char* key, int value)
{
    List* p;
    p = calloc(sizeof(*p), 1);
    if (p != NULL) {
        p->key = key;
        p->value = value;
        p->next = NULL;
    }
    return p;
}

List* list_lookup(List* list, char* key)
{
    for (; list != NULL; list = list->next) {
        if (strcmp(list->key, key) == 0) {
            return list;
        }
    }
    return NULL; /* Не нашли */
}

List* list_search(List* node, int value)
{
    for (; node != NULL; node = node->next) {
        if (node->value == value) {
            return node;
        }
    }
    return NULL;
}

List* list_addend(List* node, char* key, int value)
{
    List* newnode = list_createnode(key, value);

    if (node == NULL) {
        return newnode;
    }

    List* temp = node;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newnode;
    return node;
}

int fill_dictionary(Dictionary* d)
{
    if (d == NULL) {
        return -1;
    }

    FILE* file;
    char name[] = "./source/d.txt";
    if ((file = fopen(name, "r")) == NULL) {
        printf("Не удалось открыть файл\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long pos = ftell(file);
    if (pos > 0) {
        rewind(file);
    } else {
        return -1;
    }

    char* str = calloc(sizeof(char), 100);
    if (str == NULL) {
        return -1;
    }
    char* pch;
    char* word;
    d->count = 0;

    for (int i = 0; fgets(str, 100, file); i++) {
        d->count++;

        pch = strtok(str, " \n");

        for (int j = 1; j < 4 && pch != NULL; j++) {
            word = strdup(pch);
            d->lines[i] = list_addend(d->lines[i], word, j);
            pch = strtok(NULL, " \n");
        }

        while (pch != NULL) {
            word = strdup(pch);
            d->lines[i] = list_addend(d->lines[i], word, 0);
            pch = strtok(NULL, " \n");
        }
    }
    fclose(file);
    free(str);
    free(word);
    free(pch);
    return d->count;
}
