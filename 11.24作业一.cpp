#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
int main()
{
	int x, i = 0;
	scanf("%d", &x);
	do {
		i = i * 10;
		i = x % 10 + i;
		x = x / 10;
	} while (x);
	printf("%d", i);
	return 0;
}