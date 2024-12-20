#include<stdio.h>
#include"../headers/meiro.h"

void generate_mode(void){
    char choice;
    Meiro meiro;
    printf("生成モード\n");
    printf("生成する迷路のサイズを選択してください\n");
    printf("1:小    2:中    3:大\n");
    while(choice = getchar()){
        if(choice == '\n') continue;
        if(choice == '1'){
            printf("小サイズの迷路を生成します\n");
            break;
        }else if(choice == '2'){
            printf("中サイズの迷路を生成します\n");
            break;
        }else if(choice == '3'){
            printf("大サイズの迷路を生成します\n");
            break;
        }else{
            printf("不正な入力です\n");
        }
    }
    generate_meiro(choice, &meiro);
    print_meiro(&meiro);
    
    printf("生成した迷路を保存しますか？\n");
    printf("1:保存する  2:保存しない\n");
    while(choice = getchar()){
        if(choice == '\n') continue;
        if(choice == '1'){
            while(save_meiro(&meiro)==-1);
            break;
        }else if(choice == '2'){
            break;
        }else{
            printf("不正な入力です\n");
        }
    }
    printf("\n\n");
    menu_mode();
}