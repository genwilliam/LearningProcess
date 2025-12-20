#include<stdio.h>
#include<malloc.h>
typedef int datatype;
#define MAXSIZE 5   
typedef struct  //定义顺序栈结构
{	
	datatype data[MAXSIZE];
	int top;
} SeqStack;

/* 出栈：PopSeqStack(S,&x)
初始条件：栈S已存在且非空。
操作结果：将栈顶元素保存到x中后删除，若删除成功返回1，否则返回-1。	*/ 
int PopSeqStack(SeqStack *S, datatype *x)
{	
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if (S -> top == -1)
	{
		return -1;
	}
	*x = S -> data[S -> top];
	S -> top --;
	return 1;
	

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
		S->data[0]=15;
		S->data[1]=98;
		S->data[2]=67;
		S->top=2; 
		OutputSeqStack(S);
		printf("请输入将出栈的元素个数：\n");
		scanf("%d",&k);
		for(i=1;i<=k;i++)
		{
			printf("第%d次出栈：\n",i);
			if(PopSeqStack(S,&x)==1)
			{
				printf("出栈元素为：%d\n",x);
				OutputSeqStack(S);
			}
			else
			{
				printf("出栈操作失败！\n");
				break;
			}
		}
		printf("出栈结束！\n");
	}
	return 0;
}