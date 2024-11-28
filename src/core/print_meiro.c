#include <stdio.h>
#include "../headers/meiro.h"

void print_meiro(Meiro *meiro){
    for (int i = 0; i < meiro->height; i++)
    {
        for (int j = 0; j < meiro->width; j++)
        {
            if(meiro->cells[i][j].state == 0) printf(".");
            else if(meiro->cells[i][j].state == 1) printf("#");
            else if(meiro->cells[i][j].state == 2) printf("S");
            else if(meiro->cells[i][j].state == 3) printf("G");
        }
        printf("\n");
    }
}