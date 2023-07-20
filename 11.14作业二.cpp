#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main()
{
	char grade;
	printf("考试成绩：");
	scanf("%c", &grade);
	switch (grade)
	{
	case 'A':printf("\n分数段应为85-100"); break;
	case 'B':printf("\n分数段应为70-84"); break;
	case 'C':printf("\n分数段应为60-69"); break;
	case 'D':printf("\n分数段应为0-59");		
	}
	return 0;
}
