#define ROW 22 //��Ϸ������
#define COL 42 //��Ϸ������

#define EMPTY 0 //��ǿգ�ʲôҲû�У�
#define WALL 1 //���ǽ
#define HEAD 2 //�����ͷ
#define BODY 3 //�������
#define FOOD 10 //���ʳ��
#define MONSTER 4//��ǹ���

#define UP 72 //���������
#define DOWN 80 //���������
#define LEFT 75 //���������
#define RIGHT 77 //���������
#define SPACE 32 //��ͣ
#define ESC 27 //�˳�

//����
struct Body
{
	int x, y; //����ᣬ������
};

//��
struct Snake
{
	int len; //��¼������
	int x; //��ͷ������
	int y; //��ͷ������
	int dir; //����
	struct Body body[ROW * COL]; //����
};