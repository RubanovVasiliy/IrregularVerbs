#include "Dictionary.h"
#include "modes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand((unsigned)time(NULL));
    Dictionary* d = malloc(sizeof(Dictionary));
    fillDictionary(d);
    //printDictionary(d);

    int level = 3;
    float score = firstMode(d, level);
    fprintf(stdout, "Ваш счет %.0f из %d, %.0f%%\n\n", score, level, score / level * 100);
    return 0;
}