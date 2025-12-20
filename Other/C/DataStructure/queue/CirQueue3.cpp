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

/* 出队：DeQueue(Q,&x)
初始条件：队列已存在且非空。
操作结果：将队头元素保存到x中后删除，若删除成功返回1，否则返回-1。	*/ 
int DeQueue(CirQueue *Q, DataType *x) 
{	
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if (Q -> rear == Q -> front) {
        return -1;
    }else {
        *x = Q -> data[Q -> front];
        Q -> front = (Q -> front + 1) % MAXSIZE;
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
		Q->front=0;
		Q->data[0]=15;
		Q->data[1]=98;
		Q->data[2]=67;
		Q->rear=3; 
		OutputCirQueue(Q);
		printf("请输入将出队的元素个数：\n");
		scanf("%d",&k);
		for(i=1;i<=k;i++)
		{
			printf("第%d次出队：\n",i);
			if(DeQueue(Q,&x)==1)
			{
				printf("出队元素为：%d\n",x);
				OutputCirQueue(Q);
			}
			else
			{
				printf("出队操作失败！\n");
				break;
			}
		}
		printf("出队结束！\n");
	}
	return 0;
}