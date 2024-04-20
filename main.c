#include <stdio.h>
#include "struct.h"
#include <errno.h>
#include <string.h>

enum
{
    INPUT = 1,
    OUTPUT
};

int main()
{
    TRAIN RASP[RASP_SIZE];
    int item;
    printf("1)Записать информацию в файл\n2)Считать информацию из файла\n");
    scanf("%d", &item);
    fflush(stdin);

    switch (item)
    {
    case INPUT:
        printf("input:\n");

        input(RASP);
        sort(RASP);
        printrasp(RASP);

        FILE *fp = fopen("Trains.csv", "wb");
        return_error(fp);
        read(RASP, fp);
        fclose(fp);
        break;

    case OUTPUT:
        int length = 0;
        FILE *in = fopen("Trains.csv", "rb");
        return_error(in);
        putout(RASP, in, &length);
        fclose(in);

        break;

    default:
        break;
    }
    return 0;
}
