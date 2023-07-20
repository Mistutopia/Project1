#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
    long mul, number, k, a, b;
    printf("It exists following automorphic nmbers small than 100000:\n");
    for (number = 0; number < 100000; number++)
    {
        for (mul = number, k = 1; (mul /= 10) > 0; k *= 10);
        /*由number的位数确定截取数字进行乘法时的系数k*/
        a = k * 10;  /*a为截取部分积时的系数*/
        mul = 0;  /*积的最后n位*/
        b = 10;  /*b为截取乘数相应位时的系数*/
        while (k > 0)
        {
            mul = (mul + (number % (k * 10)) * (number % b - number % (b / 10))) % a;
            /*(部分积+截取被乘数的后N位*截取乘数的第M位)，%a再截取部分积*/
            k /= 10;  /*k为截取被乘数时的系数*/
            b *= 10;
        }
        if (number == mul)  /*判定若为自守数则输出*/
            printf("%ld  ", number);
    }
    printf("\n");
    return 0;
}
