#include <Windows.h>

//隐藏光标
 void HideCursor() {
	CONSOLE_CURSOR_INFO curInfo = { 1,FALSE }; //如果没赋值1的话，光标隐藏无效                       
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo); 
}

//颜色设置
 void color(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);     
}

//光标跳转
 void CursorJump(int x, int y) {
	COORD pos = { x,y }; //定义光标位置的结构体变量
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);   
}

//绘图函数
//从第x行第j列位置处开始用颜色C输出content内容
 void DrawPic(int x, int y, int c, char* content) {
	color(c);
	CursorJump(y * 2, x);
	printf("%s", content);
}