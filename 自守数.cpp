#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
    long mul, number, k, a, b;
    printf("It exists following automorphic nmbers small than 100000:\n");
    for (number = 0; number < 100000; number++)
    {
        for (mul = number, k = 1; (mul /= 10) > 0; k *= 10);
        /*��number��λ��ȷ����ȡ���ֽ��г˷�ʱ��ϵ��k*/
        a = k * 10;  /*aΪ��ȡ���ֻ�ʱ��ϵ��*/
        mul = 0;  /*�������nλ*/
        b = 10;  /*bΪ��ȡ������Ӧλʱ��ϵ��*/
        while (k > 0)
        {
            mul = (mul + (number % (k * 10)) * (number % b - number % (b / 10))) % a;
            /*(���ֻ�+��ȡ�������ĺ�Nλ*��ȡ�����ĵ�Mλ)��%a�ٽ�ȡ���ֻ�*/
            k /= 10;  /*kΪ��ȡ������ʱ��ϵ��*/
            b *= 10;
        }
        if (number == mul)  /*�ж���Ϊ�����������*/
            printf("%ld  ", number);
    }
    printf("\n");
    return 0;
}
