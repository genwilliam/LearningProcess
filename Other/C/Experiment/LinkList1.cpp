#include<stdio.h>
#include<malloc.h>
#define datatype int
typedef struct node			//定义单链表结点的结构
{  
	datatype data;			//数据域
	struct node *next;		//指针域
}LNode, *LinkList;
/* 单链表初始化：InitLinkList()
初始条件：单链表L不存在；
操作结果：构造一个空的单链表 */
LinkList InitLinkList()
{	
	LinkList L;
	L=(LinkList)malloc(sizeof(LNode));
	if(!L)
		return NULL;
	else
	{
		L->next=NULL;
		return L;	
	}
}
/* 头插入法构建单链表：CreatLinkList(L)
初始条件：单链表L不存在数据；
操作结果：构造一个具体指定数值的单链表 */
void CreatLinkList(LinkList L) 
{
	int length;  
	int i;
	printf("请输入元素个数：\n");
	scanf("%d",&length);
	printf("按照元素个数依次输入元素值：\n");
	for(i=0;i<length;i++)
	{
		LNode *node=(LNode *)malloc(sizeof(LNode));
		if(!node)
		{
			printf("构建过程分配内存错误！\n");
			return;
		}
		else
		{
			scanf("%d",&node->data);	
			node->next=L->next;
			L->next=node;
		}
	}
}
/* 输出单链表：OutputLinkList(L)
初始条件：单链表L存在
操作结果：输出单链表中的所有数据 */
void OutputLinkList(LinkList L)
{	
	LNode *p=L;
    printf("当前链表为：L->"); 
	while(p->next!=NULL)
	{ 
		p=p->next;
		printf("%d->",p->data);    //输出单链表中非最后一个元素
	}
    printf("NULL\n");      //输出单链表中最后一个元素
}
/* 插入操作：InsertLinkList(L,i,x)
初始条件：单链表L存在
操作结果：在单链表L的第 i 个位置上插入一个值为 x 的新元素，若插入成功返回1，否则返回-1。 */

int InsertLinkList(LinkList L, int i, datatype x)
{
	/********** Begin *********/
    // 检查插入位置是否合法
    if (i < 1)
    {
        printf("插入位置不合法\n");
        return -1;
    }

    // 创建新节点
    LNode *node = (LNode *)malloc(sizeof(LNode));
    if (!node)
    {
        printf("内存分配失败\n");
        return -1;
    }
    node->data = x;

    // 找到插入位置的前一个节点
    LNode *p = L;
    int j = 0;
    while (p && j < i - 1)
    {
        p = p->next;
        j++;
    }

    // 检查插入位置是否合法
    if (!p || j > i - 1)
    {
        printf("插入位置不合法\n");
        free(node);
        return -1;
    }

    // 插入新节点
    node->next = p->next;
    p->next = node;

    return 1;
	    /********** End **********/

}

int main(){
	LinkList L;
	int i,k;
	datatype x;
    L=InitLinkList();
    if(L==NULL) 
		printf("初始化链表失败！\n");
	else
	{
		CreatLinkList(L);
		OutputLinkList(L);
		printf("请输入插入位置：\n");
		scanf("%d",&i);
		printf("请输入插入数据：\n");
		scanf("%d",&x);
		k=InsertLinkList(L,i,x);
		if(k==1)
		{
			printf("插入操作成功！插入元素后链表如下\n");
			OutputLinkList(L);
		}
		else 
			printf("插入操作失败\n");	
	} 
	return 0;
}