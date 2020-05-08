#include "Dictionary.h"
#include "menu.h"
#include "modes.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    setlocale(LC_ALL, "");
    srand((unsigned)time(NULL));
    main_menu();
    return 0;
}