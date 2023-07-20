#define _CRT_SECURE_NO_WARNINGS 1
#define maxsize 10
#include <stdio.h>  
typedef int ElemType;
typedef struct//定义顺序结构线性表
{
	ElemType date[maxsize];//数组实现连续储存空间
	int length;//元素个数
}Sqlist;
//Sqlist Createlist()//初始化空线性表
//{
//	Sqlist L;
//	L.length = 0;
//	return L;
//}
void Createlist(Sqlist *L)
{
	L->length = 0;
}
//返回线性表中元素个数
int Lengthlist(Sqlist L)
{
	return L.length;
}
//判断线性表是否为空
int Emptylist(Sqlist L)
{
	if (L.length == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//判断线性表是否为满
int Fulllist(Sqlist L)
{
	if (L.length == maxsize)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//清空线性表
void Clearlist(Sqlist* L)
{
	L->length = 0;
}
//遍历线性表
void Traveselist(Sqlist L)
{
	if (Emptylist(L))
	{
		printf("空\n");
	}
	else
	{
		int i;
			for (i = 0; i < L.length - 1; i++)
			{
				printf("%d\t", L.date[i]);
			}
	}
}
//线性表插入元素
void Insertlist(Sqlist* L, int i, ElemType x)
{
	if (i<0 || i>L->length)
	{
		printf("error!");
	}
	else if (Fulllist(*L))
	{
		printf("满了");
	}
	//else if (i == L->length)//插入到最后一个
	//{
	//	L->date[i] = x;
	//	L->length++;
	//}
	else//插入到中间
	{
		int j;
		for (j =L->length - 1; j >= i; j--)
		{
			L->date[j + 1] = L->date[j];
		}
		L->date[i] = x;
		L->length++;
	}
}
//在线性表中查找指定位置的元素
void Searchlist(Sqlist L, int i, ElemType* e)
{
	if (L.length == 0)
	{
		printf("空\n");
	}
	else if (i<0 || i>L.length - 1)
	{
		printf("error!\n");
	}
	else
	{
		*e = L.date[i];
	}
}
//在线性表中查找指定元素的位置
int Seeklist(Sqlist L, ElemType x)
{
	int i;
	if(L.length==0)
	{
		return -1;
	}
	else
	{
		for (i = 0; i < L.length; i++)
		{
			if (L.date[i] == x)
			{
				return i;
			}
		}
		if (i == L.length)
		{
			return -1;
		}
	}
}
//在线性表中删除指定位置的元素
void Deletelist(Sqlist *L, int i, ElemType* e)
{
	int j;
	if (L->length == 0)
	{
		printf("空\n");
	}
	else if (i<0 || i>L->length - 1)
	{
		printf("error!\n");
	}
	else
	{
		*e = L->date[i];//获取要被删除的元素
		for (j = i + 1; j < L->length; j++)
		{
			L->date[j - 1] = L->date[j];
		}
		L->length--;
	}
}
//给定参数X，删掉线性表中所有值为X的元素
void DeleteX(Sqlist* L, ElemType X)
{
	int i, j;
	for (i = 0, j = 0; i < L->length; i++) 
	{
		if (L->date[i] != X) 
		{ 
			L->date[j] = L->date[i];// 如果元素不等于X，将其移动到j位置
			j++;
		}
	}
	L->length = j; // 更新线性表长度
}
int main()
{
	//Sqlist L=Createlist()
	Sqlist L;
	Createlist(&L);
	Insertlist(&L, 0, 10);//插入数据 从i=0开始
	printf("数据个数为%d", Lengthlist(L));
	Traveselist(L);
	//Searchlist(L, 3, &e);
	/*printf("%d", e);*/

}
