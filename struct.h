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
void printrasp(TRAIN *, int len);
void sort(TRAIN *, int len);
void return_error(FILE *);
TRAIN *read_from_txt_to_bin();
void read_bin();
void exctract();
void find_by_name();


#endif