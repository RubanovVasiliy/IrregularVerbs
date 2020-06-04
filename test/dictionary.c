#include "../src/dictionary.h"
#include "../ctest/ctest.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST(dictionary, fillDictionary)
{
    // Given
    Dictionary* d = calloc(sizeof(Dictionary), 1);

    // When
    int real = fillDictionary(d);

    // Then
    const int expected = 42; //words in d.txt

    ASSERT_EQUAL(expected, real);
    free(d);
}

CTEST(dictionary, printDictionary)
{
    // Given
    Dictionary* d = calloc(sizeof(Dictionary), 1);

    // When
    int real = fillDictionary(d);

    // Then
    const int expected = 0;

    real = printDictionary(d);

    ASSERT_EQUAL(expected, real);
    free(d);
}

CTEST(dictionary, list_creatnode)
{
    // Given
    List* l = list_createnode("phone", 1);

    // Then
    ASSERT_NOT_NULL(l);
}

CTEST(dictionary, list_addend)
{
    //Given
    List* head = list_createnode("forest", 1);

    //Then
    List* add = list_addend(head, "box", 2);

    ASSERT_NOT_NULL(add);
}

CTEST(dictionary, list_lookup)
{
    // Given
    List* head = list_createnode("phone", 1);
    list_addend(head, "box", 2);
    list_addend(head, "table", 3);

    // Then
    List* l = list_lookup(head, "box");

    ASSERT_NOT_NULL(l);
}

CTEST(dictionary, list_lookup_bad)
{
    // Given
    List* head = list_createnode("phone", 1);
    list_addend(head, "box", 2);
    list_addend(head, "table", 3);

    // Then
    List* l = list_lookup(head, "cherry");

    ASSERT_NULL(l);
}

CTEST(dictionary, list_search)
{
    // Given
    List* head = list_createnode("phone", 1);
    list_addend(head, "box", 2);
    list_addend(head, "table", 3);

    // Then

    List* l = list_search(head, 2);

    ASSERT_NOT_NULL(l);
}

CTEST(dictionary, list_search_bad)
{
    // Given
    List* head = list_createnode("phone", 1);
    list_addend(head, "box", 2);
    list_addend(head, "table", 3);

    // Then
    List* l = list_search(head, 5);

    ASSERT_NULL(l);
}

CTEST(dictionary, fillDictionary_bad_1)
{
    // Given
    Dictionary* d = calloc(sizeof(Dictionary), 1);

    // When
    int real = fillDictionary(d);

    // Then
    const int expected = -1;

    ASSERT_NOT_EQUAL(expected, real);
    free(d);
}

CTEST(dictionary, listprint)
{

    // Given
    List* head = list_createnode("phone", 1);

    // When
    int real = listprint(head);
    
    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}

