#include <stdio.h>
#include <malloc.h>
typedef int datatype;
typedef struct node // 定义链式栈结构
{
	datatype data;
	struct node *next;
} StackNode, *LinkStack;

/* 出栈：PopLinkStack(top,&x)
初始条件：栈S已存在且非空。
操作结果：将栈顶元素保存到x中后删除，若删除成功返回1，否则返回-1。	*/
int PopLinkStack(LinkStack top, datatype *x)
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	StackNode *q;
	if (!top->next)
		return -1;
	q = top->next;
	top->next = q->next;
	*x = q->data;
	free(q);
	return 1;

	/********** End **********/
}

/* 输出链栈：OutputLinkStack(top)
初始条件：单链表L存在
操作结果：输出单链表中的所有数据 */
void OutputLinkStack(LinkStack top)
{
	if (top == NULL)
		printf("当前尚未初始化链栈！\n");
	else
	{
		StackNode *p = top->next;
		printf("当前链栈为:Top->");
		while (p != NULL)
		{
			printf("%d->", p->data);
			p = p->next;
		}
		printf("NULL\n");
	}
}

int main()
{
	LinkStack top;
	int i, k;
	datatype x;
	StackNode *p, *q, *s;
	top = (LinkStack)malloc(sizeof(StackNode));
	if (!top)
		printf("分配空间失败！\n");
	else
	{
		top->next = NULL;
		p = (StackNode *)malloc(sizeof(StackNode));
		q = (StackNode *)malloc(sizeof(StackNode));
		s = (StackNode *)malloc(sizeof(StackNode));
		if (!p || !q || !s)
		{
			printf("分配空间失败！\n");
		}
		else
		{
			p->data = 15;
			q->data = 98;
			s->data = 67;
			p->next = q;
			q->next = s;
			s->next = top->next;
			top->next = p;
		}
		OutputLinkStack(top);
		printf("请输入将出栈的元素个数：\n");
		scanf("%d", &k);
		for (i = 1; i <= k; i++)
		{
			printf("第%d次出栈：\n", i);
			if (PopLinkStack(top, &x) == 1)
			{
				printf("出栈元素为：%d\n", x);
				OutputLinkStack(top);
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