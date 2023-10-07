#include <stdio.h>
#include <stdlib.h>

//从文件读取最高分
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

//更新最高分到文件
 void WriteGrade(int score) {
	FILE* pf = fopen("record.txt", "w");
	if (pf == NULL) {
		printf("保存最高得分记录失败\n");
		exit(0);
	}
	fprintf(pf, "%d", score);
	fclose(pf); 
}