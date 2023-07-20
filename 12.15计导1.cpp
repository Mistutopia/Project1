//一场考试结束后，要统计同学成绩的平均分。其中同学人数有n人，n值由用户决定（n >= 10），
//每个同学的分数由用户输入。输出所有同学的成绩平均分，并输出成绩最好的三名同学的成绩。
#define _CRT_SECURE_NO_WARNINGS 1
#define n 10
#include <stdio.h>  
#include <string.h>
int main()
{
	int i,t; float all[n] = { 0 }; float summation = 0; float average;
	printf("输入成绩:\n");
	for (i = 0; i < n; i++)
	{
		scanf_s("%f", &all[i]);
		summation += all[i];
	}
	average = summation / n;
	printf("平均分为:%.2f\n",average);
	printf("成绩最好的三名同学的成绩为:\n");
	int j;
	for (i = 0; i < n-1; i++)
	{
		for(j=i+1;j<n;j++)
		{ 
			if (all[j] < all[i])
			{
				t = all[i]; 
				all[i] = all[j]; 
				all[j] = t;
			}		
		}
	}
	printf("%.2f\n", all[9]);
	printf("%.2f\n", all[8]);
	printf("%.2f\n", all[7]);
	return 0;
}

//#define _CRT_SECURE_NO_WARNINGS 1
//#include <stdio.h>
//int main()
//{
//	int n;
//	int i, j, t;
//	float all[100] = { 0 };
//	float summation = 0;
//	float average;
//	printf("输入同学人数n：");
//	scanf("%d", &n);
//	printf("输入成绩:\n");
//	for (i = 0; i < n; i++)
//	{
//		scanf("%f", &all[i]);
//		summation += all[i];
//	}
//	average = summation / n;
//	printf("平均分为:%.2f\n", average);
//	printf("成绩最好的三名同学的成绩为:\n");
//	for (i = 0; i < n - 1; i++)
//	{
//		for (j = i + 1; j < n; j++)
//		{
//			if (all[j] < all[i])
//			{
//				t = all[i];
//				all[i] = all[j];
//				all[j] = t;
//			}
//			else
//			{
//				continue;
//			}
//		}
//	}
//	printf("%.2f\n", all[n - 1]);
//	printf("%.2f\n", all[n - 2]);
//	printf("%.2f\n", all[n - 3]);
//	return 0;
//}