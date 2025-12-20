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
/* 插入操作：InsertSeqList(L,i,x)
初始条件：线性表L存在且未满，插入位置正确 (1<=i<=原表长+1)。
操作结果：在线性表L的第 i 个位置（下标为 i-1）上插入一个值为 x 的新元素，这样使原下标为 i-1, i，i+1, ... , L->length-1 的数据元素的下标变为 i，i+1, ... , L->length，插入后表长=原表长+1，若插入成功返回1，否则返回-1。 */
int InsertSeqList(SeqList *L,int i,elemtype x)
{
	// 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(i < 1 || i > L->length + 1)
	{
		printf("插入位置不合法\n");
		return -1;
	}
	if (L -> length == MAXSIZE)
	{
		printf("线性表已满\n");
		return -1;
	}

	for (int j = L -> length; j >= i; j--)
	{
		L -> data[j] = L -> data[j - 1];
	}
	L -> data[i - 1] = x;
	L -> length++;
	return 1;

    /********** End **********/
}
int main(){
	SeqList *L;
	int i,x,k;
    L=InitSeqList();
    if(L==NULL) 
		printf("初始化顺序表失败！\n");
	else
	{
		AssignSeqList(L);
		OutputSeqList(L);
		printf("请输入插入位置：\n");
		scanf("%d",&i);
		printf("请输入插入数据：\n");
		scanf("%d",&x);
		k=InsertSeqList(L,i,x);
		if(k==1)
		{
			printf("插入操作成功！插入元素后顺序表如下\n");
			OutputSeqList(L);
		}
		else 
			printf("插入操作失败\n");	
	} 
	return 0;
}