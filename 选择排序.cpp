//����n��ͬѧ�ĳɼ��������ǵ���߷ֺ���ͷ֡�
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main(void)
{
	int i, n, j, t;
	float arr[100] = { 0 };
	printf("������");
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

	printf("��߷ֳɼ�Ϊ��%f\n", arr[n - 1]);
	printf("��ͷֳɼ�Ϊ��%f\n", arr[0]);
	return 0;
}