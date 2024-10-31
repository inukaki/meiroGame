#include<stdio.h>
#include"meiro.h"

int main(){
    printf("迷路生成プログラム\n\n");

    printf("モードを選択してください\n");
    printf("1:迷路生成\n");
    printf("2:迷路読み込み\n");
    char mode;
    while(mode = getchar()){
        if(mode == '\n') continue;
        if(mode == '1'){
            generate_mode();
            break;
        }else if(mode == '2'){
            printf("読み込みモード\n");
            break;
        }else{ 
            printf("不正な入力です\n");
        }
    }
}