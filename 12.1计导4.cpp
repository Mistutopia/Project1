/*一个人赶着鸭子去每个村庄卖，每经过一个村子卖去所赶鸭子的一半又一只，
这样他经过七个村子后还剩两只鸭子。问他出发时共赶了多少只鸭子？经过每
个村子卖出多少只鸭子？（用递归和迭代两种方法实现）。*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>  
#include <string.h>
int fun(int n)
{
    int m;
    if (n == 7)
    {
        m = 2;
    }
    else
    {
        m = (fun(n + 1) + 1) * 2;
    }
    return m;
}
int main()
{
    printf("第7个=%d\n", fun(7));
    printf("第6个=%d\n", fun(6));
    printf("第5个=%d\n", fun(5));
    printf("第4个=%d\n", fun(4));
    printf("第3个=%d\n", fun(3));
    printf("第2个=%d\n", fun(2));
    printf("第1个=%d\n", fun(1));
    printf("总有=%d\n", fun(0));
    return 0;
}
