#include <stdio.h>
#include "../headers/meiro.h"

void menu_mode(){
    printf("モードを選択してください\n");
    printf("1:迷路生成\n");
    printf("2:迷路読み込み\n");
    printf("3:迷路をプレイ\n");
    char mode;
    while(mode = getchar()){
        if(mode == '\n') continue;
        if(mode == '1'){
            generate_mode();
            break;
        }else if(mode == '2'){
            load_mode();
            break;
        }else if(mode == '3'){
            play_mode();
            break;
        }else{ 
            printf("不正な入力です\n");
        }
    }
}