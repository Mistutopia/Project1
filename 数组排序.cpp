#define _CRT_SECURE_NO_WARNINGS 1
#define n 10
#include <stdio.h>  
#include<stdio.h>
int main()
{
	int n, i, t, j, minindex;
	printf("������Ԫ�ظ�����\n");
	scanf_s("%d", &n);
	int a[n];
	//ѭ����������������ÿ������Ԫ�ص�ֵ
	for (i = 0; i < n; i++)
	{
		printf("�������%d��Ԫ�ص�ֵ", i + 1);
		scanf("%d" & a[i]);
	}
	//ѡ������
	for (i = 0; i < n - 1; i++)
	{
		minindex = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j] < a[minindex])
			{
				minindex = j;
			}
		}
		if (minindex != i)
		{
			t = a[i];
			a[i] = a[minindex];
			a[minindex] = t;
		}
	}
	//ѭ��������������е�ÿ��Ԫ��
	for (i = 0; i < n; i++)
	{
		printf("%d", a[i]);
		printf("\n");
	}
	return 0;
}

//#include<stdio.h>
//void main()
//{
//	int a[10];
//	int i;
//	for (i = 0; i < 10; i++)
//		scanf("%d", &a[i]);
//	printf("\n");
//	for (i = 0; i < 10; i++)
//		printf("%d\n", *(a + i));
//	printf("\n");
//}


//#include<stdio.h>
//void main()
//{
//	int a[10];
//	int i;
//	for (i = 0; i < 10; i++)
//		scanf("%d", &a[i]);
//	for (i = 0; i < 10; i++)
//		printf("%d\n", a[i]);
//	printf("\n");
//}