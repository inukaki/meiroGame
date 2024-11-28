#include <stdio.h>
#include "../headers/meiro.h"

void print_meiro(Meiro *meiro) {
    for (int i = 0; i < meiro->height; i++) {
        for (int k = 0; k < 2; k++) { // 各行を2回繰り返す
            for (int j = 0; j < meiro->width; j++) {
                if (meiro->cells[i][j].state == 0) printf("..");
                else if (meiro->cells[i][j].state == 1) printf("##");
                else if (meiro->cells[i][j].state == 2) printf("..");
                else if (meiro->cells[i][j].state == 3) printf("..");
            }
            printf("\n");
        }
    }
}