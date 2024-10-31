#include <stdio.h>
#include "meiro.h"

void print_meiro(Cell **meiro, int size_x, int size_y){
    for (int i = 0; i < size_y; i++)
    {
        for (int j = 0; j < size_x; j++)
        {
            if(meiro[i][j].state == 0) printf(" ");
            else if(meiro[i][j].state == 1) printf("#");
            else if(meiro[i][j].state == 2) printf("S");
            else if(meiro[i][j].state == 3) printf("G");
        }
        printf("\n");
    }
}