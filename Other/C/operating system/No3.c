#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXNUM 100

// 页结构体
struct Page
{
    int num;
    int time;
    bool isVoid;
} page_LRU[MAXNUM], page_FIFO[MAXNUM];

// 块结构体
struct Block
{
    int num;
    int time;
} block_LRU[MAXNUM], block_FIFO[MAXNUM];

int pageNum;  // 页数
int blockNum; // 块数

int miss_LRU = 0, miss_FIFO = 0;
int pre_LRU = 0, pre_FIFO = 0;
float rate_LRU = 0, rate_FIFO = 0;

// 初始化函数
void init()
{
    printf("请输入页个数 和 块个数:\n");
    scanf_s("%d %d", &pageNum, &blockNum);

    printf("请输入每一页的页号:\n");
    for (int i = 0; i < pageNum; i++)
    {
        scanf_s("%d", &page_LRU[i].num);
        page_LRU[i].isVoid = false;
        page_LRU[i].time = -1;

        page_FIFO[i].num = page_LRU[i].num;
        page_FIFO[i].isVoid = false;
        page_FIFO[i].time = -1;
    }

    for (int i = 0; i < blockNum; i++)
    {
        block_LRU[i].num = -1;
        block_LRU[i].time = 999;

        block_FIFO[i].num = -1;
        block_FIFO[i].time = -1;
    }
}

// 判断页是否在块中
int isFound(struct Block *block, struct Page *page, int i)
{
    for (int k = 0; k < blockNum; k++)
    {
        if (page[i].num == block[k].num)
        {
            return k;
        }
    }
    return -1;
}

// 找出LRU中时间最长的块索引
int LongestTime()
{
    int time_l = -1;
    int index = 0;
    for (int k = 0; k < blockNum; k++)
    {
        if (block_LRU[k].time > time_l)
        {
            time_l = block_LRU[k].time;
            index = k;
        }
    }
    return index;
}

// LRU页面置换算法
void LRU(int i)
{
    int found = isFound(block_LRU, page_LRU, i);
    if (found < 0)
    { // 未命中
        miss_LRU++;
        page_LRU[i].isVoid = true;
        block_LRU[pre_LRU].num = page_LRU[i].num;
        block_LRU[pre_LRU].time = 0;
    }
    else
    { // 命中
        block_LRU[found].time = 0;
    }

    for (int k = 0; k < blockNum; k++)
    {
        if (block_LRU[k].num != -1)
            block_LRU[k].time++;
    }

    pre_LRU = LongestTime();
}

// FIFO页面置换算法
void FIFO(int i)
{
    if (isFound(block_FIFO, page_FIFO, i) < 0)
    { // 未命中
        miss_FIFO++;
        page_FIFO[i].isVoid = true;
        block_FIFO[pre_FIFO].num = page_FIFO[i].num;
        pre_FIFO = (pre_FIFO + 1) % blockNum;
    }
}

// 显示页面和缺页信息
void showPage()
{
    printf("\n******* FIFO vs LRU 页面访问结果 *******\n");
    printf("页表（*表示缺页）：\n");
    for (int i = 0; i < pageNum; i++)
    {
        printf("FIFO: [%2d]%s\tLRU: [%2d]%s\n",
               page_FIFO[i].num, page_FIFO[i].isVoid ? "*" : " ",
               page_LRU[i].num, page_LRU[i].isVoid ? "*" : " ");
    }
    printf("\n缺页率：FIFO = %.2f, LRU = %.2f\n", rate_FIFO, rate_LRU);
}

// 显示当前块表内容
void showBlock(int k)
{
    printf("\n访问第 %d 页后块表情况：\n", k + 1);
    printf("FIFO\t\tLRU\n");
    for (int i = 0; i < blockNum; i++)
    {
        printf("[%2d]\t\t[%2d]\n", block_FIFO[i].num, block_LRU[i].num);
    }
}

// 主函数
int main()
{
    init();

    for (int i = 0; i < pageNum; i++)
    {
        FIFO(i);
        LRU(i);
        showBlock(i);
    }

    rate_FIFO = (float)miss_FIFO / pageNum;
    rate_LRU = (float)miss_LRU / pageNum;
    showPage();

    return 0;
}
