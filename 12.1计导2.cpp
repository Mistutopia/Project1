/*дһ���Ӻ�������ͳ������һ��������ĳ����λ�����ֵĴ�����
����21252�У�2������3�Σ���ú���Ӧ�÷���3���Ӻ����ĵ�һ��
����Ϊ�û�������������ڶ�������Ϊ�û������Ҫ���ҵĸ�λ����*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
#include <string.h>
int main() 
{
	int a,b,c=0,i=0;
	scanf("%d%d", &a,&b);	
	while(a>=0)
	{
		if (a >= 10)
		{
			i = a % 10;
			if (i == b)
			{
				c++;
			}
			a = a / 10;
		}
		else
		{
			if (a == b)
			{
				c++;
			}
			break;
		}
	}
	printf("%d", c);
	return 0;
}