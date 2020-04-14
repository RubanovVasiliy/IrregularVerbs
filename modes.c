#include "modes.h"
#include "Dictionary.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



void mainMenu(void)
{
    printf("Greetings, this is a program for verifying irregular verbs, let's get started!\n");
    printf("Enter any character to display the menu.\n");
    char* a = malloc(sizeof(char) * 1000);
    fgets(a, 1000, stdin);
    free(a);
tryAgain:
    system("clear");
    printf("1)Start testing\n"
           "2)Instructions for working with the program\n"
           "3)Exit application\n");
    char b;
    scanf("%s", &b);
    if (!isdigit(b)) {
        printf("Error");
        exit(0);
    } else {
        switch (b) {
        case '1':
            system("clear");
            printf("Choose difficulty level:\n"
                   "\n"
                   "1)First level\n"
                   "2)Second leveкl\n"
                   "3)Third level\n");
            scanf("%s", &b);
            if (!isdigit(b)) {
                printf("error");
                exit(0);
            } else {
                switch (b) {
                case '1':
                    system("clear");
                    printf("1)Легкий режим тестирования\n"
                           "2)Средний режим тестировани\n"
                           "3)Сложный режим тестирования\n");
                    scanf("%s", &b);
                    if (!isdigit(b)) {
                        printf("errror");
                        exit(0);
                    } else {
                        switch (b) {
                        case '1':
                            system("clear");
                            printf("Тут будет код легкого режима тестирования\n");
                            break;
                        case '2':
                            system("clear");
                            printf("Тут будет код среднего режима тестирования\n");
                            break;
                        case '3':
                            system("clear");
                            printf("тут будет код сложного режима тестирования\n");
                            break;
                        }
                    }
                    break;
                case '2':
                    system("clear");
                    printf("1)Легкий режим тестирования\n"
                           "2)Средний режим тестировани\n"
                           "3)Сложный режим тестирования\n");
                    scanf("%s", &b);
                    if (!isdigit(b)) {
                        printf("errror");
                        exit(0);
                    } else {
                        switch (b) {
                        case '1':
                            system("clear");
                            printf("Тут будет код легкого режима тестирования\n");
                            break;
                        case '2':
                            system("clear");
                            printf("тут будет код cреднего режима тестирования\n");
                            break;
                        case '3':
                            system("clear");
                            printf("тут будет код сложного режима тестирования\n");
                            break;
                        }
                    }
                    break;
                case '3':
                    system("clear");
                    printf("1)Легкий режим тестирования\n"
                           "2)Средний режим тестировани\n"
                           "3)Сложный режим тестирования\n");
                    scanf("%s", &b);
                    if (!isdigit(b)) {
                        printf("eerror");
                        exit(0);
                    } else {
                        switch (b) {
                        case '1':
                            system("clear");
                            printf("Тут будет код легкого режима тестирования\n");
                            break;
                        case '2':
                            system("clear");
                            printf("тут будет код cреднего режима тестирования\n");
                            break;
                        case '3':
                            system("clear");
                            printf("тут будет код сложного режима тестирования\n");
                            break;
                        }
                    }
                    break;
                default:
                    exit(0);
                }
            }
            break;
        case '2':
            system("clear");
            printf("Тут будет инстуркция по работе, ее надо прорабоать\n");
            printf("Введите любой символ, чтобы выйти в главное меню\n");
            scanf("%s", &b);
            goto tryAgain;
            break;
        case '3':
            exit(0);
        default:
            exit(0);
        }
    } 
}

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

    sprintf(temp, "Перый режим, сложность %d слов.\n", count);
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
        sprintf(temp, "%d) Слово: %-10s Вы ввели: %-10s правильный ответ: %-10s\n", i, d->lines[a[i]]->key, str, node->key);
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