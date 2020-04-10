#include "Dictionary.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 42
#define LENGHT 10

int fillEngDictionary(Dictionary* d)
{
    d->wordsEngl1 = malloc(SIZE * sizeof(char*));
    d->wordsEngl2 = malloc(SIZE * sizeof(char*));
    d->wordsEngl3 = malloc(SIZE * sizeof(char*));
    d->count = 0;
    if (d->wordsEngl1 == NULL || d->wordsEngl2 == NULL || d->wordsEngl3 == NULL) {
        return -1;
    }

    FILE* file;
    char name[] = "d.txt";
    if ((file = fopen(name, "r")) == NULL) {
        printf("Не удалось открыть файл");
        return -1;
    }

    for (int i = 0; i < SIZE; i++) {
        d->wordsEngl1[i] = malloc(LENGHT * sizeof(char));
        d->wordsEngl2[i] = malloc(LENGHT * sizeof(char));
        d->wordsEngl3[i] = malloc(LENGHT * sizeof(char));
        if (!fscanf(file, "%s %s %s", d->wordsEngl1[i], d->wordsEngl2[i], d->wordsEngl3[i])) {
            return -1;
        }
        d->count++;
    }
    fclose(file);
    return 0;
}

int printEngDictionary(Dictionary* d)
{
    if (d->wordsEngl1 == NULL || d->wordsEngl2 == NULL || d->wordsEngl3 == NULL) {
        return -1;
    }
    fprintf(stdout, "Current dictionary:\n");
    for (int i = 0; i < d->count; i++) {
        fprintf(stdout, "%2d) %-10s %-10s %-10s\n", i + 1, d->wordsEngl1[i], d->wordsEngl2[i], d->wordsEngl3[i]);
    }
    return 0;
}