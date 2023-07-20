//编写一个程序，输入一个字符串，将字符串中的字符逐一输出。
//示例输入：
//hello
//
//示例输出：
//h
//e
//l
//l
//o
//
//示例输入：
//world
//
//示例输出：
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