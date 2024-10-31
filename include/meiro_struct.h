#define SMALL_X 20
#define SMALL_Y 10
#define MEDIUM_X 30
#define MEDIUM_Y 15
#define LARGE_X 40
#define LARGE_Y 20

typedef struct 
{
    int state; // 0:通路, 1:壁, 2:スタート, 3:ゴール
    int isPassed; // 0:未通過, 1:通過済み
}Cell;