#include<stdio.h>
#include<string.h>
#include"../headers/meiro.h"

int save_meiro(Meiro *meiro){
    FILE *fp;
    char filename[256];
    char filepath[256] = "saved_files/";
    printf("保存するファイル名を入力してください\n");
    scanf("%s", filename);
    
    // ファイルパスの作成
    strcat(filepath, filename);

    if((fp = fopen(filepath, "w")) == NULL){
        printf("ファイルを開けませんでした\n");
        return -1;
    }

    // ファイルへの書き込み
    fprintf(fp, "%d %d\n", meiro->width, meiro->height);
    for(int i = 0; i < meiro->height; i++){
        for(int j = 0; j < meiro->width; j++){
            fprintf(fp, "%d ", meiro->cells[i][j].state);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("ファイルを保存しました\n");
}