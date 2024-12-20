#include<stdio.h>
#include"../headers/meiro.h"

int isGoal = 0;

void dfs(Meiro *meiro, int x, int y){
    // ゴールに到達していた場合、再帰を終了
    if(isGoal == 1) return;
    // ゴールに到達した場合
    if(meiro->cells[y][x].state == 3){
        isGoal = 1;
        return;
    }
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    // 通過済みを記録
    meiro->cells[y][x].isPassed = 1;
    for (int i = 0; i < 4; i++)
    {
        // 配列外参照が起こらないように
        if(x + dx[i] < 0 || x + dx[i] >= meiro->width || y + dy[i] < 0 || y + dy[i] >= meiro->height){
            continue;
        }
        // 進行方向に壁がないか確認
        if(meiro->cells[y + dy[i]][x + dx[i]].state == 1){
            continue;
        }
        // 進行方向に通過済みか確認
        if(meiro->cells[y + dy[i]][x + dx[i]].isPassed == 1){
            continue;
        }
        // 再起
        dfs(meiro, x + dx[i], y + dy[i]);
        // ゴールに到達した場合、再帰を終了
        if(isGoal == 1){
            return;
        }
    }
    // 通過済みを解除
    meiro->cells[y][x].isPassed = 0;
}

void solve_meiro(Meiro *meiro){

    // 深さ優先探索でゴールまで進む
    dfs(meiro, 1, 0);

}