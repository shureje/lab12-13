#include <stdio.h>
#include "struct.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>

enum
{
    INPUT_BIN = 1,
    OUTPUT_BIN,
    EXTRACT,
    FIND_BY_NAME,

};

int main()
{
    int item;
    printf("1)Записать информацию в бинарный файл из текстового\n2)Считать информацию из бинарного файла\n3)Извлечь по номеру записи\n4)Поиск по Пункту назначения/номеру поезда/времени\n");
    scanf("%d", &item);
    fflush(stdin);

    switch (item)
    {
    case INPUT_BIN:
        read_from_txt_to_bin();
        break;

    case OUTPUT_BIN:
        read_bin();

        break;

    case EXTRACT:
    exctract();
    break;

    case FIND_BY_NAME:
    find_by_name();
    break;

    default:
        break;
    }
    return 0;
}
