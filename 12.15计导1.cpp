//һ�����Խ�����Ҫͳ��ͬѧ�ɼ���ƽ���֡�����ͬѧ������n�ˣ�nֵ���û�������n >= 10����
//ÿ��ͬѧ�ķ������û����롣�������ͬѧ�ĳɼ�ƽ���֣�������ɼ���õ�����ͬѧ�ĳɼ���
#define _CRT_SECURE_NO_WARNINGS 1
#define n 10
#include <stdio.h>  
#include <string.h>
int main()
{
	int i,t; float all[n] = { 0 }; float summation = 0; float average;
	printf("����ɼ�:\n");
	for (i = 0; i < n; i++)
	{
		scanf_s("%f", &all[i]);
		summation += all[i];
	}
	average = summation / n;
	printf("ƽ����Ϊ:%.2f\n",average);
	printf("�ɼ���õ�����ͬѧ�ĳɼ�Ϊ:\n");
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
//	printf("����ͬѧ����n��");
//	scanf("%d", &n);
//	printf("����ɼ�:\n");
//	for (i = 0; i < n; i++)
//	{
//		scanf("%f", &all[i]);
//		summation += all[i];
//	}
//	average = summation / n;
//	printf("ƽ����Ϊ:%.2f\n", average);
//	printf("�ɼ���õ�����ͬѧ�ĳɼ�Ϊ:\n");
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