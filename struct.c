#include <stdio.h>
#include "struct.h"
#include <errno.h>
#include <string.h>
#include <malloc.h>

void input(TRAIN *RASP) // manyal input from keyboard
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

void printrasp(TRAIN *RASP, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%s %s %d:%d\n", RASP[i].NAZN, RASP[i].NUM, RASP[i].time.hrs, RASP[i].time.min);
    }
}

void sort(TRAIN *RASP, int len) // sortirovka po vremeni
{
    TRAIN tmp;
    int noswap = 1;
    for (int i = 0; i < len - 1; i++)
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
void return_error(FILE *fp) // error return
{
    if (fp == NULL)
    {
        perror("trains.csv");
    }
}

TRAIN *read_from_txt_to_bin()
{
    FILE *in_txt = fopen("Trains.csv", "r");
    return_error(in_txt);

    int len = 0;

    fscanf(in_txt, "%d", &len);
    printf("%d\n", len);

    TRAIN *RASP = malloc(len * sizeof(TRAIN));
    for (int i = 0; i < len; i++)
    {
        fscanf(in_txt, "%s %s %d:%d\n", &RASP[i].NAZN, &RASP[i].NUM, &RASP[i].time.hrs, &RASP[i].time.min);
    }

    sort(RASP, len);
    printrasp(RASP, len);
    fclose(in_txt);

    FILE *to_bin = fopen("Trainsbin.csv", "wb");
    return_error(to_bin);
    fwrite(&len, sizeof(int), 1, to_bin);
    fwrite(RASP, sizeof(TRAIN), len, to_bin);
    fclose(to_bin);
    free(RASP);
}

void read_bin()
{

    int len = 0;
    FILE *from_bin = fopen("Trainsbin.csv", "rb");
    return_error(from_bin);
    fread(&len, sizeof(int), 1, from_bin);
    printf("%d", len);

    TRAIN *RASP = malloc(len * sizeof(TRAIN));

    fread(RASP, sizeof(TRAIN), len, from_bin);
    printf("\n");
    printrasp(RASP, len);
    fclose(from_bin);
    free(RASP);
}

void exctract()
{

    int len = 0;
    int exctract_Choice = 0;
    TRAIN record;
    FILE *from_bin = fopen("Trainsbin.csv", "rb");
    return_error(from_bin);
    fread(&len, sizeof(int), 1, from_bin);
    printf("%d\n", len);
    printf("Введите номер записи, которую хотите извлечь:\n");
    scanf("%d", &exctract_Choice);

    fseek(from_bin, sizeof(TRAIN) * (exctract_Choice - 1), SEEK_CUR);
    fread(&record, sizeof(TRAIN), 1, from_bin);
    fclose(from_bin);

    printf("%s ", record.NAZN);
    printf("%s ", record.NUM);
    printf("%d:%d\n", record.time.hrs, record.time.min);
}

void find_by_name()
{
    enum Find_by
    {
        NAZNACH = 1,
        NUM,
        TIME
    };
    int len = 0;
    int choice;
    FILE *from_bin = fopen("Trainsbin.csv", "rb");
    return_error(from_bin);

    fread(&len, sizeof(int), 1, from_bin);

    TRAIN *RASP = malloc(len * sizeof(TRAIN));

    fread(RASP, sizeof(TRAIN), len, from_bin);

    printf("Найти по:\n1)Пункту назначения\n2)Номеру поезда\n3)Времени\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case NAZNACH:

        char *tmp_nazn = malloc(NAZN_SIZE * sizeof(char));
        printf("Введите имя пункта\n");
        scanf("%s", tmp_nazn);
        for (int i = 0; i < len; i++)
        {
            if (strcmp(tmp_nazn, RASP[i].NAZN) == 0)
            {
                printf("%s %s %d:%d\n", RASP[i].NAZN, RASP[i].NUM, RASP[i].time.hrs, RASP[i].time.min);
                break;
            }
            else if (i == len-1)
            {
                printf("Ничего не найдено\n");
            }
        }
        free(tmp_nazn);
        break;
    
    case NUM:
    char *tmp_num = malloc(NUM_SIZE * sizeof(char));
        printf("Введите номер поезда\n");
        scanf("%s", tmp_num);
        for (int i = 0; i < len; i++)
        {
            if (strcmp(tmp_num, RASP[i].NUM) == 0)
            {
                printf("%s %s %d:%d\n", RASP[i].NAZN, RASP[i].NUM, RASP[i].time.hrs, RASP[i].time.min);
                break;
            }
            else if (i == len-1)
            {
                printf("Ничего не найдено\n");
            }
        }
        free(tmp_num);

        break;

    case TIME:
    int tmp_hrs, tmp_min;
    printf("Введите время\n");
    scanf("%d:%d", &tmp_hrs, &tmp_min);
    for (int i = 0; i < len; i++)
        {
            if (tmp_hrs == RASP[i].time.hrs && tmp_min == RASP[i].time.min)
            {
                printf("%s %s %d:%d\n", RASP[i].NAZN, RASP[i].NUM, RASP[i].time.hrs, RASP[i].time.min);
                break;
            }
            else if (i == len-1)
            {
                printf("Ничего не найдено\n");
            }
        }



        break;

    default:
        break;
    }

    fclose(from_bin);
    free(RASP);
}