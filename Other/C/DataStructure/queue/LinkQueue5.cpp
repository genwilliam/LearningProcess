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

/* 入队：EnQueue(&Q,x)
初始条件：链队列存在。
操作结果：在链队列队尾插入新元素x，若插入成功返回1，否则返回-1。	*/ 
int EnQueue(LinkQueue *Q, DataType x)        
{	
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	Qnode *p;
    p = (Qnode *)malloc(sizeof(Qnode));
    if (!p)
        return -1;
    p -> data = x;
    p -> next = NULL;
    Q -> rear -> next = p;
    Q ->rear = p;
    Q -> length++;
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
    Q.front=(QueueNode *)malloc(sizeof(QueueNode));
	if(!Q.front)
		printf("初始化链队列失败！\n");
    else
    {
        Q.rear=Q.front;
	    Q.front->next=NULL;
	    Q.length=0;
        printf("初始化链队列成功！\n");
        printf("请输入将入队的元素个数：\n");
		scanf("%d",&k);
		for(i=1;i<=k;i++)
		{
			printf("请输入第%d个入队的元素：\n",i);
			scanf("%d",&x);
			if(EnQueue(&Q,x)==1)
			{
				printf("入队操作成功！\n");
				OutputLinkQueue(&Q);
			}
			else
			{
				printf("入队操作失败！\n");
				break;
			}
		}
    }
	return 0;
}