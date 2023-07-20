#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;          //定义结点结构
ElemType x;
typedef struct Node
{
    ElemType data;              //数据域
    struct Node* next;           //指针域
}Node,*LinkList;             //头指针,链表的起始地址
 //初始化空链表
LinkList CreateList()
{
    Node* L = (Node*)malloc(sizeof(Node));    //头结点
    L->next =L;
    return L;
}
//头插法建立整表
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
//遍历输出单链表中的元素
void Display(LinkList L)
{
    Node* p = L;
    if (L->next == L)
    {
        printf("单链表为空\n");
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
//尾插法建立整表
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
//返回单链表中的元素个数
int LengthList(LinkList L)
{
    int Length = 0;
    Node* p = L->next;       //单链表中第一个元素结点
    while (p != NULL)
    {
        Length++;
        p = p->next;
    }
    return Length;
}
//判断线性表是否为空
int IsEmpty(LinkList L)
{
    if (L->next == NULL)
        return 1;
    else
        return 0;
}
//清空线性表
void CkearList(LinkList L)
{
    L->next = NULL;
}
//在单链表中指定位置插入元素
    void InserList(LinkList L, int i, ElemType x)
{
    Node* p, * r = L;           //当前要插入的结点,p当前要插入的结点，r插入位置的前一个结点
    int j;
    if (i < 1)
    {
        printf("参数错误\n");
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
                printf("参数错误\n");
                return;
            }
        }
        p->next = r->next;
        r->next = p;
    }
}

//获取单链表中指定位置的元素值
void GerElem(LinkList L, int i, ElemType * e)
{
    Node* p = L;
    int j;
    if (IsEmpty(L))
    {
        printf("线性表为空\n");
    }
    else if (i < 1)
    {
        printf("参数错误\n");
    }
    else
    {
        for (j = 1; j <= i; j++)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("参数错误\n");
                return;
            }
        }
        *e = p->data;
    }



}
//删除线性表中的元素，并获取删除的元素值
void DeleteList(LinkList L, int i, ElemType * e)
    {
      Node * r = L;
      int j;
      if (IsEmpty(L))
      {
        printf("线性表为空");
      }
       else if (i < 1)
      {
       printf("参数错误\n");
      }
      else
      {
         for (j = 1; j < i; j++)
         {
            r = r->next;
           if (r == NULL)
           {
              printf("参数错误\n");
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

