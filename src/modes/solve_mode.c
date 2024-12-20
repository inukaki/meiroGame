#include<stdio.h>
#include"../headers/meiro.h"

void solve_mode(void){
    char choice;
    Meiro meiro;
    printf("迷路の答えを表示します\n");
    load_meiro(&meiro);
    solve_meiro(&meiro);
    print_meiro(&meiro);
    printf("\n\n");
    menu_mode();
}