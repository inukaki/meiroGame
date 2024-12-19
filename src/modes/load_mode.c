#include<stdio.h>
#include"../headers/meiro.h"

void load_mode(void){
    char choice;
    Meiro meiro;
    printf("読み込みモード\n");
    load_meiro(&meiro);
    print_meiro(&meiro);
    menu_mode();
}