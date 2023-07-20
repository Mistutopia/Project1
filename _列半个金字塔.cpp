#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>                                         
int main()
{
    int a, b, c;
    scanf("%d", &a);
    for (b = 0; b < a; b++)
    {
        for (c = 0; c <= b; c++)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}