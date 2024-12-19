#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include"../headers/meiro.h"

void generate_meiro(char choice, Meiro *meiro){
    if (choice == '1') {
        meiro->width = SMALL_X;
        meiro->height = SMALL_Y;
    } else if (choice == '2') {
        meiro->width = MEDIUM_X;
        meiro->height = MEDIUM_Y;
    } else if (choice == '3') {
        meiro->width = LARGE_X;
        meiro->height = LARGE_Y;
    } else {
        printf("error: 不正な入力です. in generate_meiro\n");
        return;
    }

    // 迷路用のメモリを確保
    meiro->cells = (Cell **)malloc(meiro->height * sizeof(Cell *));
    for (int i = 0; i < meiro->height; i++) {
        meiro->cells[i] = (Cell *)malloc(meiro->width * sizeof(Cell));
    }

    // 迷路の外周を生成
    for (int i = 0; i < meiro->height; i++) {
        for (int j = 0; j < meiro->width; j++) {
            if (i == 0 && j == 1) meiro->cells[i][j].state = 2;   // スタート地点
            else if (i == meiro->height - 1 && j == meiro->width - 2) meiro->cells[i][j].state = 3;   // ゴール地点
            else if (i == 0 || i == meiro->height - 1 || j == 0 || j == meiro->width - 1) meiro->cells[i][j].state = 1;    // 外周
            else meiro->cells[i][j].state = 0;   // 通路
        }
    }

    // 壁生成開始地点を格納する配列を生成
    int startPointXNum = (meiro->width - 3) / 2;
    int startPointYNum = (meiro->height - 3) / 2;
    int startPointNum = startPointXNum * startPointYNum;
    Point *startPoint = (Point *)malloc(startPointNum * sizeof(Point));
    for(int i = 0; i < startPointYNum; i++){
        for(int j = 0; j < startPointXNum; j++){
            startPoint[i * startPointXNum + j].x = 2 * (j+1);
            startPoint[i * startPointXNum + j].y = 2 * (i+1);
        }
    }

    // startPointをシャッフル
    shuffle_point_array(startPoint, startPointNum);

    // 進行方向を格納する配列
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    int directions[4] = {0, 1, 2, 3};

    // 生成中の壁を格納する配列
    Point *thisWall = (Point *)malloc(startPointNum * sizeof(Point));
    int thisWallNum = 0;

    // 壁を生成
    for(int i = 0; i < startPointNum; i++){
        int x = startPoint[i].x;
        int y = startPoint[i].y;
        // 既に壁がある場合はスキップ
        if (meiro->cells[y][x].state == 1) continue;
        meiro->cells[y][x].state = 1;

        // 生成中の壁に囲まれるか、生成済みの壁に到達するまで壁を生成
        while(1){
            shuffle_int_array(directions, 4);
            int direction = directions[0];

            // 壁に衝突しない場合
            if (meiro->cells[y + dy[direction] * 2][x + dx[direction] * 2].state != 1) {
                // 生成中の壁を記録
                thisWall[thisWallNum].x = x;
                thisWall[thisWallNum].y = y;
                thisWall[thisWallNum].direction = direction;
                thisWallNum++;

                // 壁を生成
                meiro->cells[y + dy[direction]][x + dx[direction]].state = 1;
                meiro->cells[y + dy[direction] * 2][x + dx[direction] * 2].state = 1;
                x += dx[direction] * 2;
                y += dy[direction] * 2;

                // 次のループへ
                continue;
            }

            // 壁に衝突する場合
            // 生成中の壁に囲まれているか判定
            int checkedWallNum = 0;
            int tryCount = 0;
            int endFlag = 0;
            // 次に進む方向が生成中の壁であるか確認
            while(checkedWallNum<thisWallNum){
                // もし次の進む方向が生成中の壁であれば、次の方向に変更
                if(x+dx[directions[tryCount]]*2 == thisWall[checkedWallNum].x && y+dy[directions[tryCount]]*2 == thisWall[checkedWallNum].y){
                    tryCount++;
                    // 四方向すべてが生成中の壁であれば、生成を終了
                    if(tryCount == 4){
                        // printf("四方向すべてが生成中の壁であるため、生成を終了します\n");
                        // printf("y:%d, x:%d\n", y, x);
                        endFlag = 1;
                        break;
                    }
                    // 次の方向に変更
                    direction = directions[tryCount];
                    checkedWallNum = 0;
                }
                else{
                    checkedWallNum++;
                }
            }
            // 四方向すべてが生成中の壁であれば、生成を終了
            if(endFlag == 1) break;

            // 生成中の壁にぶつかり、進路変更した場合
            if(tryCount != 0){
                // 壁に衝突しない場合
                if(meiro->cells[y+dy[direction]*2][x+dx[direction]*2].state != 1){
                    // 生成中の壁を記録
                    thisWall[thisWallNum].x = x;
                    thisWall[thisWallNum].y = y;
                    thisWall[thisWallNum].direction = direction;
                    thisWallNum++;

                    // 壁を生成
                    meiro->cells[y+dy[direction]][x+dx[direction]].state = 1;
                    meiro->cells[y+dy[direction]*2][x+dx[direction]*2].state = 1;
                    x += dx[direction]*2;
                    y += dy[direction]*2;
                    continue;
                }
            }

            // 壁に衝突する手前を生成して、生成を終了
            meiro->cells[y+dy[direction]][x+dx[direction]].state = 1;
            break;
        }
        // thisWallとthisWallNumを初期化
        thisWallNum = 0;
        for(int j = 0; j < startPointNum; j++){
            thisWall[j].x = 0;
            thisWall[j].y = 0;
        }
    }
    // startPointとthisWallを解放
    free(startPoint);
    free(thisWall);
}