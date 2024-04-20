#include <stdio.h>
#include "struct.h"
#include <errno.h>
#include <string.h>

void input(TRAIN *RASP)
{
    for (int i = 0; i < RASP_SIZE; i++)
    {
        printf("Введите пункт назначения:\n");
        scanf("%s", RASP[i].NAZN);
        printf("Введите номер поезда\n");
        scanf("%s", RASP[i].NUM);
        printf("Введите время отправления:\n");
        for (int j = 0;; j++)
        {
            scanf("%d:%d", &RASP[i].time.hrs, &RASP[i].time.min);
            if (RASP[i].time.hrs == 24 | RASP[i].time.min > 0)
            {
                break;
            }
            else if (RASP[i].time.hrs == 0 | RASP[i].time.min > 59)
            {
                break;
            }
            else if (RASP[i].time.hrs > 23 | RASP[i].time.min > 59)
            {
                printf("%s", _INVALIDE_TIME_FORMAT_);
            }

            else
            {
                break;
            }
        }
    }
}

void printrasp(TRAIN *RASP)
{
    for (int i = 0; i < RASP_SIZE; i++)
    {
        printf("%s ", RASP[i].NAZN);
        printf("%s ", RASP[i].NUM);
        printf("%d:%d\n", RASP[i].time.hrs, RASP[i].time.min);
    }
}

void sort(TRAIN *RASP)
{
    TRAIN tmp;
    int noswap = 1;
    for (int i = 0; i < RASP_SIZE - 1; i++)
    {
        int time_in_min_i = RASP[i].time.hrs * 60 + RASP[i].time.min;
        int time_in_min_i1 = RASP[i + 1].time.hrs * 60 + RASP[i + 1].time.min;
        if (time_in_min_i > time_in_min_i1)
        {

            tmp = RASP[i];
            RASP[i] = RASP[i + 1];
            RASP[i + 1] = tmp;
        }
    }
}
void return_error(FILE *fp)
{
    if (fp == NULL)
    {
        perror("trains.csv");
    }
}

void read(TRAIN *RASP, FILE *fp)
{
   int res = fwrite(RASP, sizeof(TRAIN), RASP_SIZE, fp);
   printf("res = %d\n",  res);
   
    /*for (int i = 0; i < RASP_SIZE; i++)
    {
        fprintf(fp, "%s %s %d:%d\n", RASP[i].NAZN, RASP[i].NUM, RASP[i].time.hrs, RASP[i].time.min);
    }
    fclose(fp);*/
}

int putout(TRAIN *RASP, FILE *in, int *length)
{
        while (fread(&RASP[*length], sizeof(TRAIN),1,in) == 1)
        {
            *length++;
        }

        for (int i = 0; i < *length; i++)
        {
            printf("%s %s %d:%d\n ", RASP[i].NAZN, RASP[i].NUM, RASP[i].time.hrs, RASP[i].time.min);
        }

}