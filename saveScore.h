#include <stdio.h>
#include <stdlib.h>

//���ļ���ȡ��߷�
int ReadGrade() {
	int score;
	FILE* pf = fopen("record.txt", "r"); 
	if (pf == NULL) {
		pf = fopen("record.txt", "w");
		fprintf(pf, "%d", 0);
	}
	fseek(pf, 0, SEEK_SET); 
	fscanf(pf, "%d", &score); 
	fclose(pf); 
	return score;
}

//������߷ֵ��ļ�
 void WriteGrade(int score) {
	FILE* pf = fopen("record.txt", "w");
	if (pf == NULL) {
		printf("������ߵ÷ּ�¼ʧ��\n");
		exit(0);
	}
	fprintf(pf, "%d", score);
	fclose(pf); 
}