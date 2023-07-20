#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
#include <string.h>
int main()
{
	char a [999];
	char b [] = "jyx";
	scanf("%s", &a);
	if (strcmp(a ,b)==0)
		printf("Éµ±Æ");
	return 0;
}