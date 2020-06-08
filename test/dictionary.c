#include "../src/dictionary.h"
#include "../ctest/ctest.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST(dictionary, dictionary_fill)
{
    // Given
    Dictionary* d = calloc(sizeof(Dictionary), 1);

    // When
    int real = dictionary_fill(d);
    dictionary_delete(d);

    // Then
    const int expected = 42; // words in d.txt

    ASSERT_EQUAL(expected, real);
}

CTEST(dictionary, list_creatnode)
{
    // Given
    List* l = list_createnode("phone", 1);

    // Then
    ASSERT_NOT_NULL(l);

    free(l);
}

CTEST(dictionary, list_addend)
{
    // Given
    char* str1 = strdup("forest");
    char* str2 = strdup("box");

    List* head = list_createnode(str1, 1);

    // Then
    List* add = list_addend(head, str2, 2);

    ASSERT_NOT_NULL(add);

    list_free(head);
}

CTEST(dictionary, list_lookup)
{
    // Given
    char* str1 = strdup("phone");
    char* str2 = strdup("box");
    char* str3 = strdup("table");

    List* head = list_createnode(str1, 1);
    list_addend(head, str2, 2);
    list_addend(head, str3, 3);

    // Then
    List* l = list_lookup(head, "box");

    ASSERT_NOT_NULL(l);

    list_free(head);
}

CTEST(dictionary, list_lookup_bad)
{
    // Given
    char* str1 = strdup("phone");
    char* str2 = strdup("box");
    char* str3 = strdup("table");

    List* head = list_createnode(str1, 1);
    list_addend(head, str2, 2);
    list_addend(head, str3, 3);

    // Then
    List* l = list_lookup(head, "cherry");

    ASSERT_NULL(l);

    list_free(head);
}

CTEST(dictionary, list_search)
{
    // Given
    char* str1 = strdup("phone");
    char* str2 = strdup("box");
    char* str3 = strdup("table");

    List* head = list_createnode(str1, 1);
    list_addend(head, str2, 2);
    list_addend(head, str3, 3);

    // Then
    List* l = list_search(head, 2);

    ASSERT_NOT_NULL(l);

    list_free(head);
}

CTEST(dictionary, list_search_bad)
{
    // Given
    char* str1 = strdup("phone");
    char* str2 = strdup("box");
    char* str3 = strdup("table");

    List* head = list_createnode(str1, 1);
    list_addend(head, str2, 2);
    list_addend(head, str3, 3);

    // Then
    List* l = list_search(head, 5);

    ASSERT_NULL(l);

    list_free(head);
}

CTEST(dictionary, dictionary_fill_bad_1)
{
    // Given
    Dictionary* d = calloc(sizeof(Dictionary), 1);

    // When
    int real = dictionary_fill(d);
    dictionary_delete(d);

    // Then
    const int expected = -1;

    ASSERT_NOT_EQUAL(expected, real);
}

CTEST(dictionary, list_print)
{
    // Given
    List* head = list_createnode("phone", 1);

    // When
    int real = list_print(head);
    free(head);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}

CTEST(dictionary, printDictionary)
{
    // Given
    Dictionary* d = calloc(sizeof(Dictionary), 1);

    // When
    int real = dictionary_fill(d);

    // Then
    const int expected = 0;

    real = dictionary_print(d);
    dictionary_delete(d);

    ASSERT_EQUAL(expected, real);
}

CTEST(dictionary, dictionary_delete)
{
    // Given
    Dictionary* d = calloc(sizeof(Dictionary), 1);

    // When
    int real = dictionary_fill(d);

    // Then
    const int expected = dictionary_delete(d);

    ASSERT_EQUAL(expected, real);
}

CTEST(dictionary, list_delete)
{
    // Given
    char* str1 = strdup("phone");
    char* str2 = strdup("box");
    List* l = list_createnode(str1, 1);
    list_addend(l, str2, 2);

    // Then
    l = list_delete(l);
    l = list_delete(l);

    ASSERT_NULL(l);
}

CTEST(dictionary, list_free)
{
    // Given
    char* str1 = strdup("phone");
    char* str2 = strdup("box");
    List* l = list_createnode(str1, 1);
    list_addend(l, str2, 2);

    // When
    int real = list_free(l);

    // Then
    const int expected = 2;

    ASSERT_EQUAL(expected, real);
}