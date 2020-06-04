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
