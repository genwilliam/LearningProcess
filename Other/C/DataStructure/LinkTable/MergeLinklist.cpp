#include <iostream>
using namespace std;

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *LinkList;

void CreateList_R(LinkList &L, int n)
{
    L = new LNode;
    L->next = NULL;
    LinkList r = L;

    for (int i = 0; i < n; i++)
    {
        LinkList p = new LNode;
        scanf("%d", &p->data);
        p->next = NULL;
        r->next = p;
        r = p;
    }
}
void PrintList(LinkList &L)
{
    L = L->next;
    while (L)
    {
        if (L->next != NULL)
            printf("%d->", L->data);
        else
            printf("%d ", L->data);

        L = L->next;
    }
    printf("\n");
}
void MergeList(LinkList &LA, LinkList &LB)
{
    LinkList r1, r2, r3;
    r1 = LA->next;
    r2 = LB->next;
    r3 = LA;
    while (r1 != NULL && r2 != NULL)
    {
        if (r1->data < r2->data)
        {
            r3->next = r1;
            r3 = r1;
            r1 = r1->next;
        }
        else if (r1->data == r2->data)
        {
            r3->next = r1;
            r3 = r1;
            r1 = r1->next;
            r2 = r2->next;
        }
        else
        {
            r3->next = r2;
            r3 = r2;
            r2 = r2->next;
        }
    }
    r3 -> next = r1 ? r1 : r2;
}

int main()
{
    int n, m;

    while (1)
    {
        printf("请输入La链表的长度:\n");
        scanf("%d", &n);
        printf("请输入Lb链表的长度:\n");
        scanf("%d", &m);
        if (n == 0 && m == 0)
            break;
        LinkList LA, LB;
        printf("请输入链表La的元素:\n");
        CreateList_R(LA, n);
        printf("请输入链表Lb的元素:\n");
        CreateList_R(LB, m);
        MergeList(LA, LB);
        printf("合并后的链表为：\n");
        PrintList(LA);
        printf("\n");
    }
    return 0;
}