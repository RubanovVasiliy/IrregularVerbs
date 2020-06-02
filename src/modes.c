#include "modes.h"
#include "dictionary.h"
#include <assert.h>
#include <ctype.h>
#include <ncurses.h>
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

int first_mode(WINDOW* win, Dictionary* d, int count)
{
    scrollok(win, TRUE);
    echo();
    time_t t = time(NULL);
    struct tm* aTm = localtime(&t);

    List* node;
    int* a = NULL;
    float score = 0;

    char* result = calloc(sizeof(char), 1000);
    char* temp = calloc(sizeof(char), 1000);
    char* str = calloc(sizeof(char), 100);

    if (result == NULL || temp == NULL || str == NULL) {
        return -1;
    }

    result[0] = '\0';

    wprintw(win, "Первый режим, сложность %d слов.\n", count);
    sprintf(temp, "%04d-%02d-%02d\n%02d:%02d:%02d\n", aTm->tm_year + 1900, aTm->tm_mon + 1, aTm->tm_mday, aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
    strcat(result, temp);
    generate_rand(&a, count, d->count - 1);

    for (int i = 0; i < count; i++) {
        wprintw(win, "Введите перевод слова %s на русский язык:\n", d->lines[a[i]]->key);
        wscanw(win, "%s", str);
        node = list_lookup(d->lines[a[i]], str);
        if (node != NULL) {
            score++;
        }
        node = list_search(d->lines[a[i]], 0);
        sprintf(temp, "%d) Слово: %-10s Вы ввели: %-10s правильный ответ: %-10s\n", i + 1, d->lines[a[i]]->key, str, node->key);
        strcat(result, temp);
    }
    sprintf(temp, "Ваш счет %.0f слов из %d, %.0f%%\n\n", score, count, score / count * 100);
    strcat(result, temp);

    FILE* file;
    if ((file = fopen("results.log", "a+")) == NULL) {
        wprintw(win, "Не удалось открыть файл, результаты не будут записаны.");
    }

    fprintf(file, "%s", result);
    wprintw(win, "%s", result);
    fclose(file);
    free(a);
    free(temp);
    free(result);
    return score;
}

int second_mode(WINDOW *win, Dictionary* d, int count)
{
    scrollok(win, TRUE);
    echo();
    time_t t = time(NULL);
    struct tm* aTm = localtime(&t);

    List* node;
    List* r_word;
    int* a = NULL;
    float score = 0;

    char* result = calloc(sizeof(char), 800);
    char* temp = calloc(sizeof(char), 100);
    char* str = calloc(sizeof(char), 10);

    if (result == NULL || temp == NULL || str == NULL) {
        return -1;
    }

    result[0] = '\0';

    wprintw(win, "Второй режим, сложность %d слов.\n", count);
    sprintf(temp, "%04d-%02d-%02d\n%02d:%02d:%02d\n", aTm->tm_year + 1900, aTm->tm_mon + 1, aTm->tm_mday, aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
    strcat(result, temp);
    generate_rand(&a, count, d->count - 1);

    for (int i = 0; i < count; i++) {
        r_word=list_search(d->lines[a[i]], 0);
        wprintw(win, "Введите перевод слова %s на английский язык:\n", r_word->key);
        wscanw(win, "%s", str);
        node = list_lookup(d->lines[a[i]], str);
        if (node != NULL) {
            score++;
        }
        node = list_search(d->lines[a[i]], 1);
        sprintf(temp, "%d) Слово: %-10s Вы ввели: %-10s правильный ответ: %-10s\n", i + 1, d->lines[a[i]]->key, str, node->key);
        strcat(result, temp);
    }
    sprintf(temp, "Ваш счет %.0f слов из %d, %.0f%%\n\n", score, count, score / count * 100);
    strcat(result, temp);

    FILE* file;
    if ((file = fopen("results.log", "a+")) == NULL) {
        wprintw(win, "Не удалось открыть файл, результаты не будут записаны.");
    }

    fprintf(file, "%s", result);
    wprintw(win, "%s", result);
    fclose(file);
    free(a);
    free(r_word);
    free(node);
    return score;
}

int third_mode(WINDOW *win, Dictionary* d, int count)
{
    scrollok(win, TRUE);
    echo();
    time_t t = time(NULL);
    struct tm* aTm = localtime(&t);

    List* e1_word;
    List* e2_word;
    List* e3_word;

    List* r_word;
    int* a = NULL;
    float score = 0;
    
    char* result = malloc(sizeof(char) * 8000);
    char* temp = malloc(sizeof(char) * 1000);
    char* str = calloc(sizeof(char), 100);
    char* str1 = calloc(sizeof(char), 100);
    char* str2 = calloc(sizeof(char), 100);

    if (result == NULL || temp == NULL || str == NULL) {
        return -1;
    }
    result[0] = '\0';

    wprintw(win, "Третий режим, сложность %d слов.\n", count);
    sprintf(temp, "%04d-%02d-%02d\n%02d:%02d:%02d\n", aTm->tm_year + 1900, aTm->tm_mon + 1, aTm->tm_mday, aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
    strcat(result, temp);
    generate_rand(&a, count, d->count - 1);
    for (int i = 0; i < count; i++) {

        r_word = list_search(d->lines[a[i]], 0);
        wprintw(win, "Введите три формы неправильного глагола слова %s на английский язык:\n", r_word->key);
        wscanw(win, "%s %s %s", str, str1, str2);
        e1_word=list_lookup(d->lines[a[i]], str);
        e2_word=list_lookup(d->lines[a[i]], str1);
        e3_word=list_lookup(d->lines[a[i]], str2);

        if ((e1_word != NULL) && (e2_word != NULL) && (e3_word != NULL)) {
            score++;
        }

        e1_word=list_search(d->lines[a[i]], 1);
        e2_word=list_search(d->lines[a[i]], 2);
        e3_word=list_search(d->lines[a[i]], 3);

        sprintf(temp, "%d) Слово: %-2s Вы ввели: %-2s %-2s %-2s правильный ответ: %-2s %-2s %-2s\n", i +1, r_word->key, str,str1, str2, e1_word->key, e2_word->key, e3_word->key);
        strcat(result, temp);
    }
    sprintf(temp, "Ваш счет %.0f слов из %d, %.0f%%\n\n", score, count, score / count * 100);
    strcat(result, temp);
    FILE* file;
    if ((file = fopen("results.log", "a+")) == NULL) {
         wprintw(win, "Не удалось открыть файл, результаты не будут записаны.");
    }
    fprintf(file, "%04d-%02d-%02d\n%02d:%02d:%02d\n", aTm->tm_year + 1900, aTm->tm_mon + 1, aTm->tm_mday, aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
    fprintf(file, "%s", result);
    wprintw(win, "%s", result);
    fclose(file);
    free(str);
    free(str1);
    free(str2);
    free(a);
    free(e1_word);
    free(e2_word);
    free(e3_word);
    return score;
}
