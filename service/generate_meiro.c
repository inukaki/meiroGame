#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
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
            else if(i == size_y-1 && j == size_x-2) meiro[i][j].state = 3;   // ゴール地点
            else if(i == 0 || i == size_y-1 || j == 0 || j == size_x-1) meiro[i][j].state = 1;    // 外周
            else meiro[i][j].state = 0;   // 通路
        }
    }

    // 壁生成開始地点を格納する配列を生成
    int startPointXNum = (size_x-3) / 2;
    int startPointYNum = (size_y-3) / 2;
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

    int generateNumber[size_y][size_x];
    for(int i = 0; i < size_y; i++){
        for(int j = 0; j < size_x; j++){
            generateNumber[i][j] = 0;
        }
    }
    // 外壁を111に
    for(int i = 0; i < size_y; i++){
        generateNumber[i][0] = 11;
        generateNumber[i][size_x-1] = 11;
    }
    for(int i = 0; i < size_x; i++){
        generateNumber[0][i] = 111;
        generateNumber[size_y-1][i] = 111;
    }
    int wallCount = 0;

    // 壁を生成
    for(int i = 0; i < startPointNum; i++){
        int x = startPoint[i].x;
        int y = startPoint[i].y;
        // 既に壁がある場合はスキップ
        if(meiro[y][x].state == 1) continue;
        meiro[y][x].state = 1;
        wallCount++;
        if(generateNumber[y][x] != 0){
            printf("error1: generateNumber[%d][%d] = %d, 更新後 = %d\n", y, x, generateNumber[y][x], wallCount);
        }
        generateNumber[y][x] = wallCount;
                

        // 生成中の壁に囲まれるか、生成済みの壁に到達するまで壁を生成
        while(1){
            shuffle_int_array(directions, 4);
            int direction = directions[0];

            // 壁に衝突しない場合
            if(meiro[y+dy[direction]*2][x+dx[direction]*2].state != 1){
                // 生成中の壁を記録
                thisWall[thisWallNum].x = x;
                thisWall[thisWallNum].y = y;
                thisWall[thisWallNum].direction = direction;
                thisWallNum++;

                // 壁を生成
                meiro[y+dy[direction]][x+dx[direction]].state = 1;
                meiro[y+dy[direction]*2][x+dx[direction]*2].state = 1;
                wallCount++;
                if(generateNumber[y+dy[direction]][x+dx[direction]] != 0){
                    printf("error2: generateNumber[%d][%d] = %d, 更新後 = %d\n", y+dy[direction], x+dx[direction], generateNumber[y+dy[direction]][x+dx[direction]], wallCount);
                }
                generateNumber[y+dy[direction]][x+dx[direction]] = wallCount;
                wallCount++;
                if(generateNumber[y+dy[direction]*2][x+dx[direction]*2] != 0){
                    printf("erro3: generateNumber[%d][%d] = %d, 更新後 = %d\n", y+dy[direction]*2, x+dx[direction]*2, generateNumber[y+dy[direction]*2][x+dx[direction]*2], wallCount);
                }
                generateNumber[y+dy[direction]*2][x+dx[direction]*2] = wallCount;
                x += dx[direction]*2;
                y += dy[direction]*2;

                // 次のループへ
                continue;
            }

            // 壁に衝突する場合

            // 生成中の壁に囲まれているか判定
            int j=0;
            int tryCount = 0;
            int endFlag = 0;
            // 次に進む方向が生成中の壁であるか確認
            while(j<thisWallNum){
                // もし次の進む方向が生成中の壁であれば、次の方向に変更
                if(x+dx[directions[tryCount]]*2 == thisWall[j].x && y+dy[directions[tryCount]]*2 == thisWall[j].y){
                    tryCount++;
                    // 四方向すべてが生成中の壁であれば、生成を終了
                    if(tryCount == 4){
                        printf("四方向すべてが生成中の壁であるため、生成を終了します\n");
                        printf("y:%d, x:%d\n", y, x);
                        endFlag = 1;
                        break;
                    }
                    // 次の方向に変更
                    direction = directions[tryCount];
                    printf("data: y:%d, x:%d, direction:%d\n", y, x, direction);
                    j = 0;
                }
                else{
                    j++;
                }
            }
            // 四方向すべてが生成中の壁であれば、生成を終了
            if(endFlag == 1) break;

            // 生成中の壁にぶつかり、進路変更した場合
            if(tryCount != 0){
                // 壁に衝突しない場合
                if(meiro[y+dy[direction]*2][x+dx[direction]*2].state != 1){
                    // 生成中の壁を記録
                    thisWall[thisWallNum].x = x;
                    thisWall[thisWallNum].y = y;
                    thisWall[thisWallNum].direction = direction;
                    thisWallNum++;

                    // 壁を生成
                    meiro[y+dy[direction]][x+dx[direction]].state = 1;
                    wallCount++;
                    if(generateNumber[y+dy[direction]][x+dx[direction]] != 0){
                        printf("error4: generateNumber[%d][%d] = %d, 更新後 = %d\n", y+dy[direction], x+dx[direction], generateNumber[y+dy[direction]][x+dx[direction]], wallCount);
                    }
                    generateNumber[y+dy[direction]][x+dx[direction]] = wallCount;
                    meiro[y+dy[direction]*2][x+dx[direction]*2].state = 1;
                    wallCount++;
                    if(generateNumber[y+dy[direction]*2][x+dx[direction]*2] != 0){
                        printf("error5: generateNumber[%d][%d] = %d, 更新後 = %d\n", y+dy[direction]*2, x+dx[direction]*2, generateNumber[y+dy[direction]*2][x+dx[direction]*2], wallCount);
                    }
                    generateNumber[y+dy[direction]*2][x+dx[direction]*2] = wallCount;
                    x += dx[direction]*2;
                    y += dy[direction]*2;
                    continue;
                }
            }

            // 壁に衝突する手前を生成して、生成を終了
            printf("衝突前座標：y:%d, x:%d, num:%d\n", y, x, generateNumber[y][x]);
            printf("衝突予定座標：y:%d, x:%d, meiro[%d][%d].state = %d\n", y+dy[direction]*2, x+dx[direction]*2, y+dy[direction]*2, x+dx[direction]*2, meiro[y+dy[direction]*2][x+dx[direction]*2].state);
            meiro[y+dy[direction]][x+dx[direction]].state = 1;
            wallCount++;
            if(generateNumber[y+dy[direction]][x+dx[direction]] != 0){
                printf("error6: generateNumber[%d][%d] = %d, 更新後 = %d\n", y+dy[direction], x+dx[direction], generateNumber[y+dy[direction]][x+dx[direction]], wallCount);
            }
            generateNumber[y+dy[direction]][x+dx[direction]] = wallCount;
            break;
        }
        // thisWallとthisWallNumを初期化
        thisWallNum = 0;
        for(int j = 0; j < startPointNum; j++){
            thisWall[j].x = 0;
            thisWall[j].y = 0;
        }
    }
    free(startPoint);
    free(thisWall);

    print_meiro(meiro, size_x, size_y);

    // generateNumberを出力
    for(int i = 0; i < size_x + 1; i++)
        printf("%3d", i-1);
    printf("\n");
    for(int i = 0; i < size_y; i++){
        for(int j = 0; j < size_x; j++){
            if(j == 0) printf("%3d", i);
            printf("%3d", generateNumber[i][j]);
        }
        printf("\n");
    }
}