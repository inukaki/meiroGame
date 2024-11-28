typedef struct 
{
    int state; // 0:通路, 1:壁, 2:スタート, 3:ゴール
    int isPassed; // 0:未通過, 1:通過済み
} Cell;

typedef struct
{
    int x;
    int y;
    int direction;
} Point;

typedef struct
{
    int width;
    int height;
    Cell **cells;
} Meiro;
