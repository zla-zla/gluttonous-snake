#include <Windows.h>

//���ع��
 void HideCursor() {
	CONSOLE_CURSOR_INFO curInfo = { 1,FALSE }; //���û��ֵ1�Ļ������������Ч                       
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo); 
}

//��ɫ����
 void color(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);     
}

//�����ת
 void CursorJump(int x, int y) {
	COORD pos = { x,y }; //������λ�õĽṹ�����
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);   
}

//��ͼ����
//�ӵ�x�е�j��λ�ô���ʼ����ɫC���content����
 void DrawPic(int x, int y, int c, char* content) {
	color(c);
	CursorJump(y * 2, x);
	printf("%s", content);
}