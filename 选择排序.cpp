//输入n个同学的成绩，求他们的最高分和最低分。
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main(void)
{
	int i, n, j, t;
	float arr[100] = { 0 };
	printf("人数：");
	scanf("%d", &n);
	for (i = 0; i < n;i++)
	{
		scanf("%f", &arr[i]);
	}
	for (i = 0; i < n - 1; i++)
	{
		for (j = i+1; j < n; j++)
		{
			if (arr[i] > arr[j])
			{
				t = arr[j];
				arr[j] = arr[i];
				arr[i] = t;
			}
			else
			{
				continue;
			}
		}
	}

	printf("最高分成绩为：%f\n", arr[n - 1]);
	printf("最低分成绩为：%f\n", arr[0]);
	return 0;
}