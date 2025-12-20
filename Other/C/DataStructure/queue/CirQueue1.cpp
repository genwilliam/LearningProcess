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

/* 初始化空队列：InitCirQueue()
初始条件：循环队列不存在。
操作结果：构造一个空队列。    */ 
CirQueue *InitCirQueue()
{	
	// 请在这里补充代码，完成本关任务
    /********** Begin *********/
	CirQueue *Q;
    Q = (CirQueue *)malloc(sizeof(CirQueue));
    if (!Q) {
        return NULL;
    }else {
        Q -> front = Q -> rear = 0;
        return Q;
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
	CirQueue *Q=NULL;
	Q=InitCirQueue();
    if(Q==NULL) 
		printf("初始化循环队列失败！\n");
	else
	{
		printf("初始化循环队列成功！\n");
        OutputCirQueue(Q);
	} 
	return 0;
}