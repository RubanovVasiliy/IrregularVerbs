#include "modes.h"
#include "Dictionary.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void generate_rand(int** a, unsigned n, unsigned range)
{
    *a = malloc(sizeof(int) * n);
    unsigned temp = 0;

    for (unsigned i = 0; i < range; ++i) {
        if (rand() % (range - i) < n - temp) {
            (*a)[temp++] = i;
        }
    }
    assert(temp == n);
}

int firstMode(Dictionary* d, int count)
{
    time_t t = time(NULL);
    struct tm* aTm = localtime(&t);

    List* node;
    int* a = NULL;
    float score = 0;

    char* result = malloc(sizeof(char) * 800);
    char* temp = malloc(sizeof(char) * 100);
    char* str = malloc(sizeof(char) * 10);

    if (result == NULL || temp == NULL || str == NULL) {
        return -1;
    }

    result[0] = '\0';

    sprintf(temp, "Первый режим, сложность %d слов.\n", count);
    strcat(result, temp);
    generate_rand(&a, count, d->count - 1);

    for (int i = 0; i < count; i++) {
        fprintf(stdout, "Введите перевод слова %s на русский язык:\n", d->lines[a[i]]->key);
        fscanf(stdin, "%s", str);
        node = list_lookup(d->lines[a[i]], str);
        if (node != NULL) {
            score++;
        }
        node = list_search(d->lines[a[i]], 0);
        sprintf(temp, "%d) Слово: %-10s Вы ввели: %-10s правильный ответ: %-10s\n", i+1, d->lines[a[i]]->key, str, node->key);
        strcat(result, temp);
    }
    sprintf(temp, "Ваш счет %.0f слов из %d, %.0f%%\n\n", score, count, score / count * 100);
    strcat(result, temp);

    FILE* file;
    if ((file = fopen("results.log", "a+")) == NULL) {
        fprintf(stdout, "Не удалось открыть файл, результаты не будут записаны.");
    }
    fprintf(file, "%04d-%02d-%02d\n%02d:%02d:%02d\n", aTm->tm_year + 1900, aTm->tm_mon + 1, aTm->tm_mday, aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
    fprintf(file, "%s", result);
    fclose(file);
    free(a);
    return score;
}

int secondMode(Dictionary *d, int count) {

    time_t t = time(NULL);
    struct tm* aTm = localtime(&t);

    List* e_word;
    List* r_word;
    int* a = NULL;
    float score = 0;

    char* result = malloc(sizeof(char) * 800);
    char* temp = malloc(sizeof(char) * 100);
    char* str = malloc(sizeof(char) * 10);

    if (result == NULL || temp == NULL || str == NULL) {
        return -1;
    }

    result[0] = '\0';

    sprintf(temp, "Второй режим, сложность %d слов.\n", count);
    strcat(result, temp);
    generate_rand(&a, count, d->count - 1);

    for (int i = 0; i < count; i++) {
        r_word=list_search(d->lines[a[i]], 0);
        fprintf(stdout, "Введите перевод слова %s на английский язык:\n", r_word->key);
        fscanf(stdin, "%s", str);
        e_word = list_lookup(d->lines[a[i]], str);
        if (e_word != NULL) {
            score++;
        }
        sprintf(temp, "%d) Слово: %-10s Вы ввели: %-10s правильный ответ: %-10s\n", i+1, r_word->key, str, e_word->key);
        strcat(result, temp);
    }
    sprintf(temp, "Ваш счет %.0f слов из %d, %.0f%%\n\n", score, count, score / count * 100);
    strcat(result, temp);

    FILE* file;
    if ((file = fopen("results.log", "a+")) == NULL) {
        fprintf(stdout, "Не удалось открыть файл, результаты не будут записаны.");
    }
    fprintf(file, "%04d-%02d-%02d\n%02d:%02d:%02d\n", aTm->tm_year + 1900, aTm->tm_mon + 1, aTm->tm_mday, aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
    fprintf(file, "%s", result);
    fclose(file);
    free(a);
    return score;
}