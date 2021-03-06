#include "dictionary.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int list_free(List* head)
{
    int count = 0;
    while (head) {
        head = list_delete(head);
        count++;
    }
    return count;
}

int list_print(List* node)
{
    if (!node) {
        return -1;
    }

    List* ptr = node;

    for (; ptr != NULL;) {
        printf("%2d %-10s", ptr->value, ptr->key);
        ptr = ptr->next;
    }
    free(ptr);

    return 0;
}

int list_wprint(WINDOW* win, List* node)
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

int dictionary_print(Dictionary* d)
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

int dictionary_wprint(WINDOW* win, Dictionary* d)
{
    if (!d) {
        return -1;
    }
    for (int i = 0; i < d->count; i++) {
        list_wprint(win, d->lines[i]);
        wprintw(win, "\n");
    }
    return 0;
}

int dictionary_delete(Dictionary* d)
{
    if (d == NULL) {
        return -1;
    }
    int count = 0;

    for (int i = d->count; i >= 0; --i) {
        list_free(d->lines[i]);

        if (d->lines[i]) {
            count++;
        }
    }
    free(d);
    return count;
}

int dictionary_fill(Dictionary* d)
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

    d->count = 0;

    for (int i = 0; fgets(str, 100, file); i++) {
        d->count++;

        char* pch = strtok(str, " \n");

        for (int j = 1; j < 4 && pch != NULL; j++) {
            char* word = strdup(pch);
            d->lines[i] = list_addend(d->lines[i], word, j);
            pch = strtok(NULL, " \n");
        }

        while (pch != NULL) {
            char* word = strdup(pch);
            d->lines[i] = list_addend(d->lines[i], word, 0);
            pch = strtok(NULL, " \n");
        }
    }
    fclose(file);
    free(str);
    return d->count;
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

List* list_delete(List* list)
{
    List *p, *prev = NULL;
    for (p = list; p != NULL; p = p->next) {
        if (prev == NULL)
            list = p->next;
        else
            prev->next = p->next;
        free(p->key);
        free(p);
        return list;

        prev = p;
    }
    return NULL;
}
