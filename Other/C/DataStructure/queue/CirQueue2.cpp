#include<stdio.h>
#include<malloc.h>
typedef int DataType;   
//循环队列的最大容量
#define MAXSIZE 5 
//定义队列的结构体
typedef struct {      
	DataType data[MAXSIZE];
	int front, rear;
}CirQueue;

/* 入队：EnQueue(Q,x)
初始条件：循环队列存在且未满。
操作结果：在循环队列队尾插入新元素x，若插入成功返回1，否则返回-1。	*/ 
int EnQueue(CirQueue *Q, DataType x)          
{	
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if ((Q -> rear + 1) % MAXSIZE == Q -> front)
        return -1;
    else {
        Q ->data[Q -> rear] = x;
        Q -> rear = (Q -> rear + 1) % MAXSIZE;
        return 1;
    }

    /********** End **********/
}

/* 输出循环队列：OutputCirQueue(Q)
初始条件：循环队列存在。
操作结果：输出循环队列中的所有数据。    */
void OutputCirQueue(CirQueue *Q)
{
    int i;
	if(Q->rear==Q->front)
		printf("当前队列为空！\n");
	else 
	{
		printf("当前队列元素有：Front->");
		for(i=Q->front;i<Q->rear;i=(i+1)%MAXSIZE)
			printf("%d->",Q->data[i]);
		printf("Rear\n");
	}
}

int main(){
	CirQueue *Q;
	int i,k;
	DataType x;
	Q=(CirQueue *)malloc(sizeof(CirQueue));
	if(!Q) 
		printf("初始化循环队列失败！\n");
	else
	{
		Q->front=Q->rear=0; 
		printf("初始化循环队列成功！\n");
		printf("请输入将入队的元素个数：\n");
		scanf("%d",&k);
		for(i=1;i<=k;i++)
		{
			printf("请输入第%d个入队的元素：\n",i);
			scanf("%d",&x);
			if(EnQueue(Q,x)==1)
			{
				printf("入队操作成功！\n");
				OutputCirQueue(Q);
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