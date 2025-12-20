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
/*按值查找：LocateSeqList(L,x)，x是给定的一个数据元素。
初始条件：线性表L存在
操作结果：在表L中查找值为x的数据元素，其结果返回在L中首次出现的值为x的那个元素的序号或地址，称为查找成功; 否则，在L中未找到值为x的数据元素，返回-1表示查找失败。    */


int LocationSeqList(SeqList *L, elemtype x)
{
	// 请在这里补充代码，完成本关任务
    /********** Begin *********/

    // 遍历顺序表，查找值为 x 的元素
    for (int i = 0; i < L->length; i++)
    {
        if (L->data[i] == x)
            return i;  // 返回元素的下标
    }
    return -1;  // 未找到值为 x 的元素


    /********** End **********/
}

int main(){
	SeqList *L;
	elemtype x;
	int k;
    L=InitSeqList();
    if(L==NULL) 
		printf("初始化顺序表失败！\n");
	else
	{
		AssignSeqList(L);
		OutputSeqList(L);
		printf("请输入要查找的数值x：\n");
		scanf("%d",&x);
		k=LocationSeqList(L,x);
		if(k!=-1) 
		{
			printf("值为%d的元素在线性表中的第%d个位置\n",x,k+1);
		}
		else
			printf("线性表中没有值为%d的元素\n",x);
	} 
	return 0;
}