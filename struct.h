#ifndef __STRUCT_H__
#define __STRUCT_H__

#define NAZN_SIZE 64
#define NUM_SIZE 16
#define RASP_SIZE 2
#define _INVALIDE_TIME_FORMAT_ "Нерпавильный формат времени, введите заново\n"

typedef struct TIME
{
    int hrs;
    int min;
} TIME;


typedef struct 
{
    char NAZN[NAZN_SIZE];
    char NUM[NUM_SIZE];
    TIME time;
} TRAIN;


void input(TRAIN *);
void printrasp(TRAIN *);
void sort(TRAIN *);
void return_error(FILE *);
void read(TRAIN *, FILE *);
int putout(TRAIN *, FILE *, int *);

#endif