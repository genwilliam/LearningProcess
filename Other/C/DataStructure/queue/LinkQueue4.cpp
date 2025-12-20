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

/* 初始化空队列：InitLinkQueue(&Q)
操作结果：创建一个空队列，若创建成功返回1，否则返回-1。    */ 
int InitLinkQueue(LinkQueue *Q)
{  
	// 请在这里补充代码，完成本关任务
    /********** Begin *********/
    Q -> front = Q -> rear = (Qnode *)malloc(sizeof(Q));
    if (!Q -> front)
        return -1;
    Q -> front -> next = NULL;
    Q -> length = 0;
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
    if(InitLinkQueue(&Q)==1) 
	{
		printf("初始化链队列成功！\n");
        OutputLinkQueue(&Q);
	} 	
	else
		printf("初始化链队列失败！\n");
	return 0;
}