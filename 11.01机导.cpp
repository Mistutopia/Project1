#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h> 
#include<math.h>  
int main()
{
	int m, n, i, t, a = 0;
	scanf("%d%d", &m, &n);
	for (i = m; i <= n; i++)
	{
		for (t = i; t > 1; t--)
		{
			if (i % t == 0 && i != t)
			{
				a++;
			}
		}
		if (a == 0)
			printf("%d\n", i);
		a = 0;
	}
	return 0;
}