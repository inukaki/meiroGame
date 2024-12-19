#include<stdio.h>
#include"../headers/meiro.h"

void play_meiro(Meiro *meiro){
    int x = 1;
    int y = 0;
    meiro->cells[y][x].isPassed = 1;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    int direction = 0;
    int endFlag = 0;
    char choice;
    while(1){
        print_meiro(meiro);
        // ゴールに到達した場合
        if(meiro->cells[y][x].state == 3){
            printf("ゴールに到達しました\n");
            break;
        }
        // 進行方向を選択
        printf("進行方向を選択してください\n");
        printf("w:上  a:左  s:下  d:右\n");
        while(choice = getchar()){
            if(choice == '\n') continue;
            if(choice == 'w'){
                direction = 0;
                break;
            }else if(choice == 'd'){
                direction = 1;
                break;
            }else if(choice == 's'){
                direction = 2;
                break;
            }else if(choice == 'a'){
                direction = 3;
                break;
            }else{
                printf("不正な入力です\n");
            }
        }
        // 配列外参照が起こらないように
        if(x+dx[direction] < 0 || x+dx[direction] >= meiro->width || y+dy[direction] < 0 || y+dy[direction] >= meiro->height){
            printf("スタート地点に戻らないでください\n");
            continue;
        }

        // 進行方向に壁がないか確認
        if(meiro->cells[y+dy[direction]][x+dx[direction]].state == 1){
            printf("壁があります\n");
            continue;
        }
        // 進行方向に壁がない場合、進行
        // 逆戻りする場合、通過済みを解除
        if(meiro->cells[y+dy[direction]][x+dx[direction]].isPassed == 1){
            meiro->cells[y][x].isPassed = 0;
        }
        x += dx[direction];
        y += dy[direction];
        meiro->cells[y][x].isPassed = 1;
    }
}