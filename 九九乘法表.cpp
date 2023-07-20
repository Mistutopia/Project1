#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
int main()
{
	int m=1, n=1, t;
	while (m <= 9) 
	{
		while (n <= m)
		{
			t = m * n;
			printf("%d*%d=%d\t", n, m, t);
			n++;
		}
		n = 1;
		printf("\n");
		m++;
	}
	return 0;
}