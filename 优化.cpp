//��дһ����������һ���ַ��������ַ����е��ַ���һ�����
//ʾ�����룺
//hello
//
//ʾ�������
//h
//e
//l
//l
//o
//
//ʾ�����룺
//world
//
//ʾ�������
//w
//o
//r
//l
//d
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main()
{
    char str[100];
    scanf("%s", str);
    int i = 0;
    while (str[i] != '\0')
    {
        printf("%c\n", str[i]);
        i++;
    }
    return 0;
}