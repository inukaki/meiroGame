#include<stdio.h>
#include"../headers/meiro.h"

void play_mode(void){
    char choice;
    Meiro meiro;
    printf("プレイモード\n");
    load_meiro(&meiro);
    play_meiro(&meiro);
}