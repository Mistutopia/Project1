/*һ���˸���Ѽ��ȥÿ����ׯ����ÿ����һ��������ȥ����Ѽ�ӵ�һ����һֻ��
�����������߸����Ӻ�ʣ��ֻѼ�ӡ���������ʱ�����˶���ֻѼ�ӣ�����ÿ
��������������ֻѼ�ӣ����õݹ�͵������ַ���ʵ�֣���*/
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
    printf("��7��=%d\n", fun(7));
    printf("��6��=%d\n", fun(6));
    printf("��5��=%d\n", fun(5));
    printf("��4��=%d\n", fun(4));
    printf("��3��=%d\n", fun(3));
    printf("��2��=%d\n", fun(2));
    printf("��1��=%d\n", fun(1));
    printf("����=%d\n", fun(0));
    return 0;
}
