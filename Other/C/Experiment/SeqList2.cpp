#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100					//线性表允许的最大长度
typedef int elemtype;
typedef struct						//定义线性表的结构
{	
	elemtype data[MAXSIZE];			//表示线性表（a1，a2，….,an）
	int length;						//length表示线性表的实际长度
}SeqList;
/* 线性表初始化：InitSeqList()
初始条件：表L不存在；
操作结果：构造一个空的线性表 */
SeqList * InitSeqList()
{	
	SeqList *L;
	L=(SeqList *)malloc(sizeof(SeqList));
	if(!L)
		return NULL;
	else
	{
		L->length=0;
		return L;	
	}
}
/* 线性表赋值：AssignSeqList(L)
初始条件：表L不存在数据
操作结果：构造一个具体指定数值的线性表 */
void AssignSeqList(SeqList *L)   
{	
	int i;
	printf("请输入元素个数：\n");
	scanf("%d",&L->length);
	printf("按照元素个数依次输入元素值：\n");
	for(i=0;i<L->length;i++)
		scanf("%d",&L->data[i]);
}
/* 线性表输出：OutputSeqList(L)
初始条件：表L存在
操作结果：输出线性表中的所有数据 */
void OutputSeqList(SeqList *L)
{	
	int i;
	printf("顺序表的长度是%d\n",L->length);
	if(L->length!=0)
	{
		printf("顺序表的元素依次是：");
		for(i=0;i<L->length;i++)
			printf("%4d",L->data[i]);
	}
	else
	{
		printf("当前顺序表为空！");
	}
	printf("\n");
}
/*删除操作：DeleteSeqList(L,i)
初始条件：线性表L存在且非空，删除位置正确（1<=i<=原表长）。
操作结果：在线性表L中删除第i个位置（下标为 i-1）的数据元素，删除后使下标为 i, i+1,..., L->length-1 的元素变为下标为 i-1, i,...,L->length-2，删除后新表长＝原表长-1，若删除成功返回1，否则返回-1。    */
int DeleteSeqList(SeqList *L, int i)
{
    // 检查顺序表是否为空
    if (L->length == 0)
    {
        printf("线性表为空\n");
        return -1;
    }

    // 检查删除位置是否合法
    if (i < 1 || i > L->length)
    {
        printf("删除位置不合法\n");
        return -1;
    }

    // 从删除位置开始，依次向前移动元素
    for (int j = i; j < L->length; j++)
        L->data[j - 1] = L->data[j];

    // 更新顺序表的长度
    L->length--;

    return 1;
}


int main(){
	SeqList *L;
	int i,k;
    L=InitSeqList();
    if(L==NULL) 
		printf("初始化顺序表失败！\n");
	else
	{
		AssignSeqList(L);
		OutputSeqList(L);
		printf("请输入删除位置：\n");
		scanf("%d",&i);
		k=DeleteSeqList(L,i);
		if(k==1)
		{
			printf("删除操作成功！删除元素后顺序表如下\n");
			OutputSeqList(L);
		}
		else 
			printf("删除操作失败\n");	
	} 
	return 0;
}