#include<stdio.h>
#include<malloc.h>
#include"../include/meiro.h"

void generate_meiro(char choice){
    int size_x, size_y;
    if(choice == '1'){
        size_x = SMALL_X;
        size_y = SMALL_Y;
    }else if(choice == '2'){
        size_x = MEDIUM_X;
        size_y = MEDIUM_Y;
    }else if(choice == '3'){
        size_x = LARGE_X;
        size_y = LARGE_Y;
    }else{
        printf("error: 不正な入力です. in generate_meiro\n");
        return;
    }

    // 迷路用のメモリを確保
    Cell **meiro = (Cell **)malloc(size_y * sizeof(Cell *));
    for(int i = 0; i < size_y; i++){
        meiro[i] = (Cell *)malloc(size_x * sizeof(Cell));
    }

    // 迷路の外周を生成
    for(int i = 0; i < size_y; i++){
        for(int j = 0; j < size_x; j++){
            if(i == 0 && j == 1) meiro[i][j].state = 2;   // スタート地点
            else if(i == size_x-1 && j == size_y-2) meiro[i][j].state = 3;   // ゴール地点
            else if(i == 0 || i == size_y-1 || j == 0 || j == size_x-1) meiro[i][j].state = 1;    // 外周
            else meiro[i][j].state = 0;   // 通路
        }
    }

    print_meiro(meiro, size_x, size_y);

    // 壁伸ばし法で迷路を生成
}