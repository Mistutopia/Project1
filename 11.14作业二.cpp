#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main()
{
	char grade;
	printf("���Գɼ���");
	scanf("%c", &grade);
	switch (grade)
	{
	case 'A':printf("\n������ӦΪ85-100"); break;
	case 'B':printf("\n������ӦΪ70-84"); break;
	case 'C':printf("\n������ӦΪ60-69"); break;
	case 'D':printf("\n������ӦΪ0-59");		
	}
	return 0;
}
