#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"headers/meiro.h"

int main(){
    srand(time(NULL));
    
    printf("迷路生成プログラム\n\n");

    menu_mode();

    return 0;
}