#include<stdio.h>
#include<malloc.h>
typedef int datatype;                  
typedef struct node   //定义链式栈结构
{	
    datatype data;
	struct node *next;
}StackNode,*LinkStack;

/* 初始化空栈：InitLinkStack()
初始条件：链栈不存在。
操作结果：构造一个空栈。    */ 
LinkStack  InitLinkStack()
{  
	// 请在这里补充代码，完成本关任务
    /********** Begin *********/
    StackNode *S;
    S = (StackNode*) malloc(sizeof(StackNode));
    return S;

    /********** End **********/    
}

/* 输出链栈：OutputLinkStack(top)
初始条件：链栈存在。
操作结果：输出链栈中的所有数据。    */
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
	LinkStack top=NULL;
	top=InitLinkStack();
    if(top==NULL) 
		printf("初始化链栈失败！\n");
	else
	{
		printf("初始化链栈成功！\n");
        OutputLinkStack(top);
	} 
	return 0;
}