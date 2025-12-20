#include<stdio.h>
#include<malloc.h>
typedef int datatype;                  
typedef struct node   //定义链式栈结构
{	
    datatype data;
	struct node *next;
}StackNode,*LinkStack;

/* 入栈：PushLinkStack(top,x)
初始条件：链栈存在。
操作结果：插入元素x为新的栈顶元素，若插入成功返回1，否则返回-1。	*/ 
int PushLinkStack(LinkStack top, datatype x)         
{	
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	StackNode *q;
	q=(StackNode *)malloc(sizeof(StackNode));
	if (!q)
		return -1;
	q -> data=x;
	q -> next=top -> next;
	top -> next=q;
	return 1;
	

    /********** End **********/
}

/* 输出链栈：OutputLinkStack(top)
初始条件：单链表L存在
操作结果：输出单链表中的所有数据 */
void OutputLinkStack(LinkStack top)
{	
    if(top==NULL)
        printf("当前尚未初始化链栈！\n");	
    else
    {
        StackNode *p=top->next;
        printf("当前链栈为：Top->"); 
	    while(p!=NULL) 
	    {	
            printf("%d->",p->data);
		    p=p->next;
	    }
        printf("NULL\n"); 
    } 
}

int main(){
	LinkStack top;
	int i,k;
	datatype x;
	top=(LinkStack)malloc(sizeof(StackNode));
	if(!top) 
		printf("分配空间失败！\n");
	else
	{
		top->next=NULL;
		printf("请输入将入栈的元素个数：\n");
		scanf("%d",&k);
		for(i=1;i<=k;i++)
		{
			printf("请输入第%d个入栈的元素：\n",i);
			scanf("%d",&x);
			if(PushLinkStack(top,x)==1)
			{
				printf("入栈操作成功！\n");
				OutputLinkStack(top);
			}
			else
			{
				printf("入栈操作失败！\n");
			}
		}
	}
	return 0;
}