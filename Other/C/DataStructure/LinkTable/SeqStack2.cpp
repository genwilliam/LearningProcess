#include "stdio.h"
#include <stdlib.h>
#include "malloc.h"
#define MAXSIZE  10 //顺序栈的长度
typedef  int datatype; 
 //定义顺序栈结构
typedef  struct
{	datatype  data[MAXSIZE];
	int  top;
}SeqStack;

//顺序栈置空栈：首先建立栈空间，然后初始化栈顶指针。
SeqStack  *Init_SeqStack()
{	SeqStack  *s;
	s=(SeqStack *)malloc(sizeof(SeqStack));
	s->top= -1;  
	return s;
}
//顺序栈判空栈
int Empty_SeqStack(SeqStack *s)
{	if (s->top == -1)  return 1;
    else  return 0;
}
//顺序栈入栈
int Push_SeqStack (SeqStack *s, datatype  x)
{if (s->top == MAXSIZE-1)  return 0; //栈满不能入栈
else {	s->top++;
        s->data[s->top]=x;
        return 1;
	}
}
//顺序栈出栈
int  Pop_SeqStack(SeqStack *s, datatype *x)
{  	if  (Empty_SeqStack(s))  return 0; //栈空不能出栈 
    else  { *x=s->data[s->top];
			s->top--;  return 1;        //栈顶元素存入*x，返回
		  }
}

int Expression(SeqStack *S){
   // 请在这里补充代码，完成本关任务
    /********** Begin *********/
     char ch;
    while ((ch = getchar()) != '\n') {
        if (ch == '(') {
            if (!Push_SeqStack(S, ch)) {
                printf("栈满，无法入栈\n");
                return 0;
            }
        } else if (ch == ')') {
            datatype temp;
            if (!Pop_SeqStack(S, &temp)) {
                // printf("圆括号匹配失败（栈空，无法出栈）\n");
                return 0; // 栈空，无法出栈，表示不匹配
            }
        }
    }
    return Empty_SeqStack(S);
    /********** End **********/    
}


int main()
{
    SeqStack *S;
    int flag=2;   //为了测试数据
    S = Init_SeqStack();
    if (S==0)
    {
        printf("初始化顺序栈失败！\n");
    }
    else
    {
		printf("请输入待匹配的表达式字符串(以回车键为结束符)：\n");
        flag = Expression(S);
        if(flag==1)printf("圆括号匹配成功！");
        else if(flag==0) printf("圆括号匹配失败！");
    }
    return 0;

}

