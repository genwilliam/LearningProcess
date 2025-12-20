#include <stdio.h>
#include <malloc.h>
typedef int datatype;
#define MAXSIZE 5
typedef struct // 定义顺序栈结构
{
    datatype data[MAXSIZE];
    int top;
} SeqStack;

/* 初始化空栈：InitSeqStack()
初始条件：顺序栈不存在。
操作结果：构造一个空栈。    */
SeqStack *InitSeqStack()
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    SeqStack *s;
    s = (SeqStack *)malloc(sizeof(SeqStack)); // 分配顺序栈空间
    if (s != NULL) {
        s->top = -1; // 初始化栈顶指针为-1，表示空栈
    }
    return s;

    /********** End **********/
}

/* 输出顺序栈：OutputSeqStack(S)
初始条件：顺序栈存在。
操作结果：输出顺序栈中的所有数据。    */
void OutputSeqStack(SeqStack *S)
{
    int i;
    if (S->top == -1)
        printf("当前顺序栈为空！\n");
    else
    {
        printf("当前顺序栈为：");
        for (i = 0; i <= S->top; i++)
            printf("%d->", S->data[i]);
        printf("Top\n");
    }
}

int main()
{
    SeqStack *S = NULL;
    S = InitSeqStack();
    if (S == NULL)
        printf("初始化顺序栈失败！\n");
    else
    {
        printf("初始化顺序栈成功！\n");
        OutputSeqStack(S);
    }
    return 0;
}