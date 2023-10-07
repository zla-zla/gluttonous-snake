#define ROW 22 //游戏区行数
#define COL 42 //游戏区列数

#define EMPTY 0 //标记空（什么也没有）
#define WALL 1 //标记墙
#define HEAD 2 //标记蛇头
#define BODY 3 //标记蛇身
#define FOOD 10 //标记食物
#define MONSTER 4//标记怪物

#define UP 72 //方向键：上
#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右
#define SPACE 32 //暂停
#define ESC 27 //退出

//蛇身
struct Body
{
	int x, y; //蛇身横，纵坐标
};

//蛇
struct Snake
{
	int len; //记录蛇身长度
	int x; //蛇头横坐标
	int y; //蛇头纵坐标
	int dir; //方向
	struct Body body[ROW * COL]; //蛇身
};