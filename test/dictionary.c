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
    const int expected = 42; //words in d.txt

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
    //Given
    List* head = list_createnode("forest", 1);

    //Then
    List* add = list_addend(head, "box", 2);
    
    ASSERT_NOT_NULL(add);

    list_free(head);
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

    list_free(head);
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

    list_free(head);
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

    list_free(head);
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
