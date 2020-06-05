#include "modes.h"
#include "dictionary.h"
#include <assert.h>
#include <ctype.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STRLEN_(x) #x
#define STRLEN(x) STRLEN_(x)
#define LEN 20

void generate_rand(int** rand_sequence, unsigned n, unsigned range)
{
    *rand_sequence = calloc(sizeof(int), n);
    unsigned temp = 0;

    for (unsigned i = 0; i < range; ++i) {
        if (rand() % (range - i) < n - temp) {
            (*rand_sequence)[temp++] = i;
        }
    }
    assert(temp == n);
}

int first_mode(WINDOW* win, Dictionary* d, int count)
{
    scrollok(win, TRUE);
    echo();

    char* result_str = calloc(sizeof(char), 450 + 110 * count);
    char temp[110];
    char* str = calloc(sizeof(char), 21);

    List* node;

    if (result_str == NULL || temp == NULL || str == NULL) {
        return -1;
    }

    time_t t = time(NULL);
    struct tm* aTm = localtime(&t);

    result_str[0] = '\0';

    sprintf(temp, "Первый режим, сложность %d слов.\n", count);
    wprintw(win, temp);
    strcat(result_str, temp);
    sprintf(temp,
            "%04d-%02d-%02d\n%02d:%02d:%02d\n",
            aTm->tm_year + 1900,
            aTm->tm_mon + 1,
            aTm->tm_mday,
            aTm->tm_hour,
            aTm->tm_min,
            aTm->tm_sec);
    strcat(result_str, temp);

    int* rand_sequence = NULL;
    float score = 0;

    generate_rand(&rand_sequence, count, d->count - 1);

    for (int i = 0; i < count; i++) {
        wprintw(win,
                "Введите перевод слова %s на русский язык:\n",
                d->lines[rand_sequence[i]]->key);
        if (wscanw(win, "%" STRLEN(LEN) "s", str) == -1) {
            str[0] = '\0';
        }
        node = list_lookup(d->lines[rand_sequence[i]], str);
        if (node != NULL) {
            score++;
        }
        node = list_search(d->lines[rand_sequence[i]], 0);
        sprintf(temp,
                "%2d) Слово: %-10s Вы ввели: %-10s правильный ответ: %-10s\n",
                i + 1,
                d->lines[rand_sequence[i]]->key,
                str,
                node->key);
        strcat(result_str, temp);
    }

    wprintw(win, "\n");
    sprintf(temp,
            "Ваш счет %.0f слов из %d, %.0f%%\n\n",
            score,
            count,
            score / count * 100);
    strcat(result_str, temp);

    FILE* file;
    if ((file = fopen("results.log", "a+")) == NULL) {
        wprintw(win, "Не удалось открыть файл, результаты не будут записаны.");
    }

    wclear(win);
    fprintf(file, "%s", result_str);
    wprintw(win, "%s\n\n", result_str);
    wprintw(win, "Нажмине F1 для выхода.\n");
    fclose(file);

    free(rand_sequence);
    free(str);
    free(result_str);

    return score;
}

int second_mode(WINDOW* win, Dictionary* d, int count)
{
    scrollok(win, TRUE);
    echo();

    List* node;
    List* r_word;

    int* rand_sequence = NULL;
    float score = 0;

    char* result_str = calloc(sizeof(char), 450 + 110 * count);
    char* temp = calloc(sizeof(char), 110);
    char* str = calloc(sizeof(char), 21);

    if (result_str == NULL || temp == NULL || str == NULL) {
        return -1;
    }

    time_t t = time(NULL);
    struct tm* aTm = localtime(&t);

    result_str[0] = '\0';

    sprintf(temp, "Второй режим, сложность %d слов.\n", count);
    wprintw(win, temp);
    strcat(result_str, temp);
    sprintf(temp,
            "%04d-%02d-%02d\n%02d:%02d:%02d\n",
            aTm->tm_year + 1900,
            aTm->tm_mon + 1,
            aTm->tm_mday,
            aTm->tm_hour,
            aTm->tm_min,
            aTm->tm_sec);
    strcat(result_str, temp);
    generate_rand(&rand_sequence, count, d->count - 1);

    for (int i = 0; i < count; i++) {
        r_word = list_search(d->lines[rand_sequence[i]], 0);
        wprintw(win,
                "Введите перевод слова %s на английский язык:\n",
                r_word->key);
        if (wscanw(win, "%" STRLEN(LEN) "s", str) == -1) {
            str[0] = '\0';
        }
        node = list_lookup(d->lines[rand_sequence[i]], str);
        if (node != NULL) {
            score++;
        }
        node = list_search(d->lines[rand_sequence[i]], 1);
        sprintf(temp,
                "%2d) Слово: %10s Вы ввели: %-10s правильный ответ: %-10s\n",
                i + 1,
                r_word->key,
                str,
                node->key);
        strcat(result_str, temp);
    }

    wprintw(win, "\n");
    sprintf(temp,
            "Ваш счет %.0f слов из %d, %.0f%%\n\n",
            score,
            count,
            score / count * 100);
    strcat(result_str, temp);

    FILE* file;
    if ((file = fopen("results.log", "a+")) == NULL) {
        wprintw(win, "Не удалось открыть файл, результаты не будут записаны.");
    }

    wclear(win);
    fprintf(file, "%s", result_str);
    wprintw(win, "%s\n\n", result_str);
    wprintw(win, "Нажмине F1 для выхода.\n");
    fclose(file);

    free(rand_sequence);
    free(str);
    free(temp);
    free(result_str);

    return score;
}

int third_mode(WINDOW* win, Dictionary* d, int count)
{
    scrollok(win, TRUE);
    echo();

    List* e1_word;
    List* e2_word;
    List* e3_word;
    List* r_word;

    char* result_str = calloc(sizeof(char), 450 + count * 155);
    char* temp = calloc(sizeof(char), 155);
    char* str1 = calloc(sizeof(char), 21);
    char* str2 = calloc(sizeof(char), 21);
    char* str3 = calloc(sizeof(char), 21);

    if (result_str == NULL || temp == NULL || str1 == NULL || str2 == NULL
        || str3 == NULL) {
        return -1;
    }

    time_t t = time(NULL);
    struct tm* aTm = localtime(&t);

    result_str[0] = '\0';

    sprintf(temp, "Третий режим, сложность %d слов.\n", count);
    wprintw(win, temp);
    strcat(result_str, temp);
    sprintf(temp,
            "%04d-%02d-%02d\n%02d:%02d:%02d\n",
            aTm->tm_year + 1900,
            aTm->tm_mon + 1,
            aTm->tm_mday,
            aTm->tm_hour,
            aTm->tm_min,
            aTm->tm_sec);
    strcat(result_str, temp);

    int* rand_sequence = NULL;
    float score = 0;

    generate_rand(&rand_sequence, count, d->count - 1);

    for (int i = 0; i < count; i++) {
        r_word = list_search(d->lines[rand_sequence[i]], 0);
        wprintw(win,
                "Введите три формы неправильного глагола слова %s на "
                "английский "
                "язык:\n",
                r_word->key);

        switch (
                wscanw(win,
                       "%" STRLEN(LEN) "s"
                                       "%" STRLEN(LEN) "s"
                                                       "%" STRLEN(LEN) "s",
                       str1,
                       str2,
                       str3)) {
        case -1:
            str1[0] = '\0';
            str2[0] = '\0';
            str3[0] = '\0';
            break;

        case 1:
            str2[0] = '\0';
            str3[0] = '\0';
            break;
        case 2:
            str3[0] = '\0';
            break;
        }

        e1_word = list_lookup(d->lines[rand_sequence[i]], str1);
        e2_word = list_lookup(d->lines[rand_sequence[i]], str2);
        e3_word = list_lookup(d->lines[rand_sequence[i]], str3);

        if ((e1_word != NULL) && (e2_word != NULL) && (e3_word != NULL)) {
            score++;
        }

        e1_word = list_search(d->lines[rand_sequence[i]], 1);
        e2_word = list_search(d->lines[rand_sequence[i]], 2);
        e3_word = list_search(d->lines[rand_sequence[i]], 3);

        sprintf(temp,
                "%d) Слово: %-2s Вы ввели: %-2s %-2s %-2s правильный ответ: "
                "%-2s "
                "%-2s %-2s\n",
                i + 1,
                r_word->key,
                str1,
                str2,
                str3,
                e1_word->key,
                e2_word->key,
                e3_word->key);
        strcat(result_str, temp);
    }

    wprintw(win, "\n");
    sprintf(temp,
            "Ваш счет %.0f слов из %d, %.0f%%\n\n",
            score,
            count,
            score / count * 100);
    strcat(result_str, temp);

    FILE* file;
    if ((file = fopen("results.log", "a+")) == NULL) {
        wprintw(win, "Не удалось открыть файл, результаты не будут записаны.");
    }

    wclear(win);
    fprintf(file, "%s", result_str);
    wprintw(win, "%s\n\n", result_str);
    wprintw(win, "Нажмине F1 для выхода.\n");
    fclose(file);

    free(rand_sequence);
    free(temp);
    free(str1);
    free(str2);
    free(str3);
    free(result_str);

    return score;
}
