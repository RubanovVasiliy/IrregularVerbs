#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Dictionary {
    char** wordsEngl1;
    char** wordsEngl2;
    char** wordsEngl3;
    int count;
} Dictionary;

int printEngDictionary(Dictionary* d);
int fillEngDictionary(Dictionary* d);
