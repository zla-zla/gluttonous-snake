#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "saveScore.h"
#include "config.h"
#include "tools.h"


int state[ROW][COL], max = 0, grade, dir[2][4] = { {0,0,-1,1},{-1,1,0,0} }, T , count, hasMon;
char buffer[1024];
struct Snake snake;


//随机生成物体，用颜色type输出s，用于生成食物或怪物
int RandObject(int type, char* s)
{
	int i, j;
	for (i = rand() % ROW, j = rand() % COL; state[i][j] != EMPTY; i = rand() % ROW, j = rand() % COL) {}
	state[i][j] = type;
	DrawPic(i, j, type, s);
	return i * COL + j;
}


//界面初始化
void ChooseIneter() {
	char c;
	int choice = 0;
	DrawPic(ROW / 2 - 1, (COL / 3), 10, "请选择是否有怪物：");
	DrawPic(ROW / 2, (COL / 3) - 1, 10, "->无");
	DrawPic(ROW / 2 + 1, (COL / 3), 10, "有");
	while (c = getch()) {
		if (c == 13)break;//回车确定
		else if (c == DOWN) choice = (choice + 1) % 2;
		else if (c == UP) choice - 1 < 0 ? choice += 1 : choice--;
		else continue;
		DrawPic(ROW / 2, (COL / 3) - 1, 10, "  ");
		DrawPic(ROW / 2 + 1, (COL / 3) - 1, 10, "  ");
		DrawPic(ROW / 2 + choice, (COL / 3) - 1, 10, "->");
	}
	hasMon = choice;//选择是否有怪物

	DrawPic(ROW / 2 + choice, (COL / 3) - 1, 10, "  ");
	choice = 0;
	DrawPic(ROW / 2 - 1, (COL / 3),  10, "请选择难度模式：");
	DrawPic(ROW / 2, (COL / 3)-1, 10, "->困难");
	DrawPic(ROW / 2 + 1, (COL / 3), 10, "中等");
	DrawPic(ROW / 2 + 2, (COL / 3),  10, "简单");
	while (c = getch()) {
		if (c == 13)break;//回车确定
		else if (c == DOWN) choice = (choice + 1) % 3;		
		else if (c == UP) choice - 1 < 0 ? choice += 2 : choice--;
		else continue;
		DrawPic(ROW / 2, (COL / 3) - 1, 10, "  ");
		DrawPic(ROW / 2 + 1, (COL / 3) - 1, 10, "  ");
		DrawPic(ROW / 2 + 2, (COL / 3) - 1, 10, "  ");
		DrawPic(ROW / 2 + choice, (COL / 3) - 1, 10, "->");
	}
	T = 2000 + T * choice;//选择刷新间隔，即蛇的速度，用来调难度
}
void Init() {
	//初始化，读取最高分
	struct Snake tmp = { 2,COL / 2 ,ROW / 2 ,3,{{COL / 2 - 1,ROW / 2},{COL / 2 - 2,ROW / 2}} };
	snake = tmp;
	grade = 0;
	count = 0;
	max = ReadGrade();
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (j == 0 || j == COL - 1 || i == 0 || i == ROW - 1) state[i][j] = WALL;
			else state[i][j] = EMPTY;
		}
	}
	state[snake.y][snake.x] = HEAD;
	state[snake.body[0].y][snake.body[0].x] = BODY;
	state[snake.body[1].y][snake.body[1].x] = BODY;

	//绘图
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (state[i][j] == WALL) DrawPic(i, j, 6, "■");
			else if (state[i][j] == HEAD) DrawPic(i, j, 10, "■");
			else if (state[i][j] == BODY) DrawPic(i, j, 10, "□");
			else DrawPic(i, j, 10, "  ");
		}
	}
	srand((unsigned int)time(NULL));
	for (int i = 1; i <= 3; i++) RandObject(FOOD + i, "●");		//生成三种食物
	sprintf(buffer, "当前得分:%d", grade);
	DrawPic(ROW, 0, 7, buffer);
	sprintf(buffer, "历史最高得分:%d", max);
	DrawPic(ROW, COL / 2, 7, buffer);
	DrawPic(ROW + 2, 0, 7, "游戏说明：\n■代表蛇头          ●代表5分的食物          方向键进行上下左右移动\n□代表蛇身          ●代表10分的食物         SPACE键暂停\n■代表围墙          ●代表15分的食物         r/R键重开\n##代表陷阱                                   ESC键退出游戏");
	DrawPic(ROW + 3, 0, 10, "■");
	DrawPic(ROW + 4, 0, 10, "□");
	DrawPic(ROW + 5, 0, 6, "■");
	DrawPic(ROW + 6, 0, MONSTER, "##");
	for (int i = 0; i < 3; i++) DrawPic(ROW + i + 3, 10, i + 11, "●");
}


//判断得分与结束
void fail() {
	Sleep(1000);
	system("cls");
	if (grade > max) {
		sprintf(buffer, "恭喜你打破最高记录，最高记录更新为%d", grade);
		WriteGrade(grade);
	}
	else if (grade == max) sprintf(buffer, "与最高记录持平，加油再创佳绩", grade);
	else sprintf(buffer, "请继续加油，当前与最高记录相差%d", max - grade);
	DrawPic(ROW / 2 - 3, COL / 3, 7, buffer);
	DrawPic(ROW / 2, COL / 3, 7, "GAME OVER");
	char ch;
	while (1) {
		DrawPic(ROW / 2 + 3, COL / 3, 7, "再来一局?(y/n):");
		ch = getch();
		if (ch == 'y' || ch == 'Y') {
			system("cls");
			return;
		}
		else if (ch == 'n' || ch == 'N') exit(0);
	}
}
int win() {
	if (grade >= 400) {
		Sleep(1000);
		system("cls");
		DrawPic(ROW / 2, COL / 3, 7, "YOU WIN!");
		char ch;
		while (1) {
			DrawPic(ROW / 2 + 3, COL / 3, 7, "再来一局?(y/n):");
			ch = getch();
			if (ch == 'y' || ch == 'Y') {
				system("cls");
				return 1;
			}
			else if (ch == 'n' || ch == 'N') exit(0);
		}
	}
	else return 0;
}

//判断蛇的运动状态
int JudgeFunc() {
	int nstate = state[snake.y + dir[1][snake.dir]][snake.x + dir[0][snake.dir]];

	if (nstate == WALL || nstate == BODY || nstate == MONSTER) {
		fail();
		return 1;
	}
	if (nstate > FOOD) {
		snake.len = -snake.len; //标记蛇身需要加长
		grade += (nstate - FOOD) * 5; //更新当前得分
		sprintf(buffer, "当前得分:%d", grade);
		DrawPic(ROW, 0, 7, buffer);
		RandObject(nstate, "●"); //重新随机生成食物
	}
	return 0;
}


//移动蛇
void MoveSnake()
{
	if (snake.len < 0) snake.len = -snake.len + 1;
	else {
		state[snake.body[snake.len - 1].y][snake.body[snake.len - 1].x] = EMPTY;
		DrawPic(snake.body[snake.len - 1].y, snake.body[snake.len - 1].x, 10, "  ");
	}

	memcpy(snake.body + 1, snake.body, sizeof(snake.body[0]) * (snake.len - 1));
	snake.body[0].x = snake.x;
	snake.body[0].y = snake.y;
	state[snake.y][snake.x] = BODY;
	DrawPic(snake.y, snake.x, 10, "□");
	snake.x = snake.x + dir[0][snake.dir];
	snake.y = snake.y + dir[1][snake.dir];
	state[snake.y][snake.x] = HEAD;
	DrawPic(snake.y, snake.x, 10, "■");
}

//执行按键
int run() {
	int t = 0;
	while (1) {
		if (t == 0) t = T;
		while (--t) {
			if (kbhit() != 0) break;
		}
		if (t == 0) {
			if (JudgeFunc()) return 1;
			MoveSnake();
			if (hasMon&&(count++) % 10 == 0) RandObject(MONSTER, "##");//蛇每移动k次，生成一个障碍物
		}
		else  break;
	}
	return 0;
}


//游戏主体逻辑函数
void Game() {
	int n = -1;
	while (1) {
		if (n == SPACE) system("pause>nul"); //暂停后按任意键继续
		else if (n == UP && snake.dir != 1) snake.dir = 0;
		else if (n == DOWN && snake.dir != 0) snake.dir = 1;
		else if (n == LEFT && snake.dir != 3) snake.dir = 2;
		else if (n == RIGHT && snake.dir != 2) snake.dir = 3;
		else if (n == 'r' || n == 'R') {
			system("cls"); //清空屏幕
			return;
		}
		else if (n == ESC) {
			system("cls"); //清空屏幕
			DrawPic(ROW / 2, COL / 2, 7, "  游戏结束  ");
			exit(0);
		}
		if (run()) return;
		if (win())return;
		n = getch();
	}
}


//主函数
void main() {
	system("title 贪吃蛇");
	system("mode con cols=84 lines=30");
	HideCursor();
	while (1) {
		ChooseIneter();
		Init();
		Game();
	}
	return 0;
}