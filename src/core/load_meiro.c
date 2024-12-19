#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../headers/meiro.h"

void load_meiro(Meiro *meiro){
    FILE *fp;
    char filename[256];
    char filepath[512] = "saved_files/";

    // ファイル一覧表示
    printf("保存されているファイル\n");
    system("ls saved_files");
    printf("\n");

    printf("読み込むファイル名を入力してください\n");
    scanf("%s", filename);
    
    // ファイルパスの作成
    strcat(filepath, filename);

    if((fp = fopen(filepath, "r")) == NULL){
        printf("ファイルを開けませんでした\n");
        return;
    }
    // 幅と高さを読み込む
    fscanf(fp, "%d %d", &meiro->width, &meiro->height);

    // 迷路用のメモリを確保
    meiro->cells = (Cell **)malloc(meiro->height * sizeof(Cell *));
    for (int i = 0; i < meiro->height; i++) {
        meiro->cells[i] = (Cell *)malloc(meiro->width * sizeof(Cell));
    }

    // 迷路の状態を読み込む
    for(int i = 0; i < meiro->height; i++){
        for(int j = 0; j < meiro->width; j++){
            fscanf(fp, "%d", &meiro->cells[i][j].state);
        }
    }
    fclose(fp);
    printf("ファイルを読み込みました\n");
}