/*写一个子函数，可统计任意一个整数中某个个位数出现的次数，
例如21252中，2出现了3次，则该函数应该返回3。子函数的第一个
参数为用户输入的整数，第二个参数为用户输入的要查找的个位数。*/
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