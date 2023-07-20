#define _CRT_SECURE_NO_WARNINGS 1
#define maxsize 10
#include <stdio.h>  
typedef int ElemType;
typedef struct//����˳��ṹ���Ա�
{
	ElemType date[maxsize];//����ʵ����������ռ�
	int length;//Ԫ�ظ���
}Sqlist;
//Sqlist Createlist()//��ʼ�������Ա�
//{
//	Sqlist L;
//	L.length = 0;
//	return L;
//}
void Createlist(Sqlist *L)
{
	L->length = 0;
}
//�������Ա���Ԫ�ظ���
int Lengthlist(Sqlist L)
{
	return L.length;
}
//�ж����Ա��Ƿ�Ϊ��
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
//�ж����Ա��Ƿ�Ϊ��
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
//������Ա�
void Clearlist(Sqlist* L)
{
	L->length = 0;
}
//�������Ա�
void Traveselist(Sqlist L)
{
	if (Emptylist(L))
	{
		printf("��\n");
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
//���Ա����Ԫ��
void Insertlist(Sqlist* L, int i, ElemType x)
{
	if (i<0 || i>L->length)
	{
		printf("error!");
	}
	else if (Fulllist(*L))
	{
		printf("����");
	}
	//else if (i == L->length)//���뵽���һ��
	//{
	//	L->date[i] = x;
	//	L->length++;
	//}
	else//���뵽�м�
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
//�����Ա��в���ָ��λ�õ�Ԫ��
void Searchlist(Sqlist L, int i, ElemType* e)
{
	if (L.length == 0)
	{
		printf("��\n");
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
//�����Ա��в���ָ��Ԫ�ص�λ��
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
//�����Ա���ɾ��ָ��λ�õ�Ԫ��
void Deletelist(Sqlist *L, int i, ElemType* e)
{
	int j;
	if (L->length == 0)
	{
		printf("��\n");
	}
	else if (i<0 || i>L->length - 1)
	{
		printf("error!\n");
	}
	else
	{
		*e = L->date[i];//��ȡҪ��ɾ����Ԫ��
		for (j = i + 1; j < L->length; j++)
		{
			L->date[j - 1] = L->date[j];
		}
		L->length--;
	}
}
//��������X��ɾ�����Ա�������ֵΪX��Ԫ��
void DeleteX(Sqlist* L, ElemType X)
{
	int i, j;
	for (i = 0, j = 0; i < L->length; i++) 
	{
		if (L->date[i] != X) 
		{ 
			L->date[j] = L->date[i];// ���Ԫ�ز�����X�������ƶ���jλ��
			j++;
		}
	}
	L->length = j; // �������Ա���
}
int main()
{
	//Sqlist L=Createlist()
	Sqlist L;
	Createlist(&L);
	Insertlist(&L, 0, 10);//�������� ��i=0��ʼ
	printf("���ݸ���Ϊ%d", Lengthlist(L));
	Traveselist(L);
	//Searchlist(L, 3, &e);
	/*printf("%d", e);*/

}
