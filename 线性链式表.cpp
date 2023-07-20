#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;          //������ṹ
ElemType x;
typedef struct Node
{
    ElemType data;              //������
    struct Node* next;           //ָ����
}Node,*LinkList;             //ͷָ��,�������ʼ��ַ
 //��ʼ��������
LinkList CreateList()
{
    Node* L = (Node*)malloc(sizeof(Node));    //ͷ���
    L->next =L;
    return L;
}
//ͷ�巨��������
LinkList CreateListH()
{
    Node* L = (Node*)malloc(sizeof(Node));
        L->next = NULL;
    while (scanf("%d", &x) != EOF)
    {
        Node* p = (Node*)malloc(sizeof(Node));
        p->data = x;
        p->next = L->next;
        L->next = p;
    }
    return L;
}
//��������������е�Ԫ��
void Display(LinkList L)
{
    Node* p = L;
    if (L->next == L)
    {
        printf("������Ϊ��\n");
    }
    else
    {
        while (p->next != L)
        {
            p = p->next;
            printf("%d\t", p->next);
        }
        printf("\n");
    }
}
//β�巨��������
LinkList CreateListT()
{
    ElemType x;
    Node* r;
    Node* L = (Node*)malloc(sizeof(Node));
    L->next = NULL;
    r = L;
    while (scanf("%d", &x) != EOF)
    {
        Node* p = (Node*)malloc(sizeof(Node));
        p->data = x;
        r->next = p;
        r = p;
    }
    r->next = L;
    return L;
}
//���ص������е�Ԫ�ظ���
int LengthList(LinkList L)
{
    int Length = 0;
    Node* p = L->next;       //�������е�һ��Ԫ�ؽ��
    while (p != NULL)
    {
        Length++;
        p = p->next;
    }
    return Length;
}
//�ж����Ա��Ƿ�Ϊ��
int IsEmpty(LinkList L)
{
    if (L->next == NULL)
        return 1;
    else
        return 0;
}
//������Ա�
void CkearList(LinkList L)
{
    L->next = NULL;
}
//�ڵ�������ָ��λ�ò���Ԫ��
    void InserList(LinkList L, int i, ElemType x)
{
    Node* p, * r = L;           //��ǰҪ����Ľ��,p��ǰҪ����Ľ�㣬r����λ�õ�ǰһ�����
    int j;
    if (i < 1)
    {
        printf("��������\n");
    }
    else
    {
        p = (Node*)malloc(sizeof(Node));
        p->data = x;
        for (j = 1; j < i; j++)
        {
            r = r->next;
            if (r == NULL)
            {
                printf("��������\n");
                return;
            }
        }
        p->next = r->next;
        r->next = p;
    }
}

//��ȡ��������ָ��λ�õ�Ԫ��ֵ
void GerElem(LinkList L, int i, ElemType * e)
{
    Node* p = L;
    int j;
    if (IsEmpty(L))
    {
        printf("���Ա�Ϊ��\n");
    }
    else if (i < 1)
    {
        printf("��������\n");
    }
    else
    {
        for (j = 1; j <= i; j++)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("��������\n");
                return;
            }
        }
        *e = p->data;
    }



}
//ɾ�����Ա��е�Ԫ�أ�����ȡɾ����Ԫ��ֵ
void DeleteList(LinkList L, int i, ElemType * e)
    {
      Node * r = L;
      int j;
      if (IsEmpty(L))
      {
        printf("���Ա�Ϊ��");
      }
       else if (i < 1)
      {
       printf("��������\n");
      }
      else
      {
         for (j = 1; j < i; j++)
         {
            r = r->next;
           if (r == NULL)
           {
              printf("��������\n");
              return;
            }
          }
          *e = r->next->data;
           r->next = r->next->next;
           }
    }
    int main()
    {
         /*LinkList L = CreateList();
          LinkList L = CreateListH();
          Display(L);
          LinkList L = CreateListT();
          printf("%d\n" / LengthList(L));
           InsertList(L, 3, 100);
           GetElem(L, 5, &e);
            printf("%d\n", e);
          DeleteList(L, 2, &e);
        Display(L);
        printf("%d\n", &e);*/
    }

