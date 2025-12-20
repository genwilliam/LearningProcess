#include<stdio.h>
#include<malloc.h>
typedef int DataType; 
typedef struct Qnode 
{      
    DataType data;
    struct Qnode *next;
} QueueNode;       
typedef struct 
{ 
    QueueNode *front,*rear;
    int length;
} LinkQueue; 

/* 出队：DeQueue(&Q,&x)
初始条件：队列已存在且非空。
操作结果：将队头元素保存到x中后删除，若删除成功返回1，否则返回-1。	*/ 
int DeQueue(LinkQueue *Q, DataType *x) 
{	
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	Qnode *p;
    if (Q -> front == Q -> rear)
        return -1;
    p = Q -> front -> next;
    *x = p -> data;
    Q -> front -> next = p -> next;
    if (p == Q -> rear)
        Q -> rear = Q -> front;
    free(p);
    Q -> length--;
    return 1;

    /********** End **********/
}

/* 输出链队列：OutputLinkQueue(&Q)
初始条件：链队列存在。
操作结果：输出链队列中的所有数据。    */
void OutputLinkQueue(LinkQueue *Q)
{
    QueueNode *p;
    if(Q==NULL)
        printf("当前尚未初始化链队列！\n");	
    else
    {
        if(Q->front==Q->rear)
            printf("当前队列为空！\n");	
        else
        {
            p=Q->front->next;
            printf("当前队列元素有：Front->");
            while(p!=NULL) 
            {	
                printf("%d->",p->data);
                p=p->next;
            }
            printf("Rear\n"); 
        } 
    }
}

int main(){
	LinkQueue Q;
	int i,k;
	DataType x;
	QueueNode *p,*q,*s;
    Q.front=(QueueNode *)malloc(sizeof(QueueNode));
	if(!Q.front)
		printf("初始化链队列失败！\n");
    else
    {
		Q.rear=Q.front;
	    Q.front->next=NULL;
	    Q.length=0;
        printf("初始化链队列成功！\n");
		p=(QueueNode *)malloc(sizeof(QueueNode));
		q=(QueueNode *)malloc(sizeof(QueueNode));
		s=(QueueNode *)malloc(sizeof(QueueNode));
		if(!p||!q||!s)
		{
			printf("分配空间失败！\n");
		}
		else
		{
			p->data=15;
			q->data=98;
			s->data=67;
			Q.front->next=p;
			p->next=q;
			q->next=s;
			s->next=NULL;
			Q.rear=s;
			Q.length=3;
			OutputLinkQueue(&Q);
			printf("请输入将出队的元素个数：\n");
			scanf("%d",&k);
			for(i=1;i<=k;i++)
			{
				printf("第%d次出队：\n",i);
				if(DeQueue(&Q,&x)==1)
				{
					printf("出队元素为：%d\n",x);
					OutputLinkQueue(&Q);
				}
				else
				{
					printf("出队操作失败！\n");
					break;
				}
			}
			printf("出队结束！\n");
		}
	}
	return 0;
}