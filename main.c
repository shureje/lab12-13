#include <stdio.h>
#include "struct.h"
#include <errno.h>
#include <string.h>

#define NAZN_SIZE 64
#define NUM_SIZE 16
#define RASP_SIZE 2
#define _INVALIDE_TIME_FORMAT_ "Нерпавильный формат времени, введите заново\n"

struct TIME
{
    int hrs;
    int min;
};

typedef struct TIME TIME;
struct TRAIN
{
    char NAZN[NAZN_SIZE];
    char NUM[NUM_SIZE];
    TIME time;
};

typedef struct TRAIN TRAIN;

enum
{
    INPUT = 1,
    OUTPUT
};

void input(TRAIN *);
void printrasp(TRAIN *);
void sort(TRAIN *);

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

        FILE *fp = fopen("Trains.csv", "w");
        if (fp == NULL)
        {
            perror("trains.csv");
            return 1;
        }
        fclose(fp);

        break;

    case OUTPUT:
        printf("output:\n");
        break;

    default:
        break;
    }
    return 0;
}

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
    for (int i = 0; i < RASP_SIZE-1; i++)
    {
        if (RASP[i].time.hrs > RASP[i + 1].time.hrs | (RASP[i].time.hrs > RASP[i + 1].time.hrs && RASP[i].time.min > RASP[i+1].time.min))
        {

            tmp = RASP[i];
            RASP[i] = RASP[i + 1];
            RASP[i + 1] = tmp;
        }
    }
}
