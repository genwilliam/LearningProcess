#include<stdio.h>
#include<malloc.h>
typedef int datatype;
#define MAXSIZE 5   
typedef struct  //定义顺序栈结构
{	
	datatype data[MAXSIZE];
	int top;
} SeqStack;

/* 入栈：PushSeqStack(S,x)
初始条件：顺序栈存在且未满。
操作结果：插入元素x为新的栈顶元素，若插入成功返回1，否则返回-1。	*/ 
int PushSeqStack(SeqStack *S, datatype x)         
{	
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(S->top==MAXSIZE-1)
		return 0;
	else
	{
		S->top++;
		S->data[S->top]=x;
		return 1;
	}

    /********** End **********/
}

/* 输出顺序栈：OutputSeqStack(S)
初始条件：顺序栈存在。
操作结果：输出顺序栈中的所有数据。    */
void OutputSeqStack(SeqStack *S)
{
    int i;
    if(S->top==-1)
        printf("当前顺序栈为空！\n");	
    else
    {
        printf("当前顺序栈为："); 
	    for(i=0;i<=S->top;i++)	
            printf("%d->",S->data[i]);
        printf("Top\n"); 
    }
}

int main(){
	SeqStack *S;
	int i,k;
	datatype x;
	S=(SeqStack *)malloc(sizeof(SeqStack));
	if(!S) 
		printf("初始化顺序栈失败！\n");
	else
	{
		S->top=-1; 
		printf("请输入将入栈的元素个数：\n");
		scanf("%d",&k);
		for(i=1;i<=k;i++)
		{
			printf("请输入第%d个入栈的元素：\n",i);
			scanf("%d",&x);
			if(PushSeqStack(S,x)==1)
			{
				printf("入栈操作成功！\n");
				OutputSeqStack(S);
			}
			else
			{
				printf("入栈操作失败！\n");
                break;
			}
		}
	}
	return 0;
}