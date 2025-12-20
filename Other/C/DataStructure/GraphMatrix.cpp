#include <stdio.h>
#define MaxVertexNum 20     //定义图的最大顶点数
#define MaxEdgeNum 50		//定义图的最大边数
typedef int VertexType;	//定义图中顶点数据的类型VertexType为整型
typedef VertexType vexlist[MaxVertexNum];  //为存储顶点信息的数组类型
typedef int adjmatrix[MaxVertexNum][MaxVertexNum]; //为存储邻接矩阵的数组类型
int n;    //实际的顶点个数
int e;    //实际的边个数
int visited[MaxVertexNum]={0};  //全局数组标记置1表示已经访问，0为未访问

/* 建立图的邻接矩阵：Create(GV,GA)
操作结果：根据用户输入的n个顶点信息和e条无向带权边信息，建立邻接矩阵GA。	*/
void Create(vexlist GV,adjmatrix GA)
{
	int i,j;   
	VertexType vertex1,vertex2;
	//初始化顶点信息，将n个顶点的数据分别设置为1~n      
    printf("初始化 %d 个顶点对应的数据为1~%d\n",n,n);
	for(i=1;i<=n;i++)	 
		GV[i]=i; 
	//初始化邻接矩阵：首先假设n个顶点之间不存在边，即为0
	for(i=1;i<=n;i++)         
		for(j=1;j<=n;j++)  
			GA[i][j]=0;
	//存储邻接矩阵
	printf("请逐一输入图中 %d 条边对应的数据：\n", e);
	for(i=1;i<=e;i++) 
	{
		printf("请输入第 %d 条边的一端顶点：\n",i); 
		scanf("%d",&vertex1);
		printf("请输入第 %d 条边的另一端顶点：\n",i); 
		scanf("%d",&vertex2);		 
		GA[vertex1][vertex2]=GA[vertex2][vertex1]=1;   //置数组中相应对称元素的值为1，表示存在边
	}
}

/* 深度遍历邻接矩阵存储的图：dfs(GV,GA,i)
初始条件：图存在
操作结果：从顶点i出发的深度遍历邻接矩阵存储的图。  */
void dfs(vexlist GV,adjmatrix GA,int i)   
{   
	// 请在这里补充代码，完成本关任务
    /********** Begin *********/
	visited[i] = 1;
	printf("%d ",GV[i]);
	for(int j=1;j<=n;j++)
	{
		if(GA[i][j]==1 && !visited[j])
			dfs(GV,GA,j);
	}

    /********** End **********/
}

void printMatrix(adjmatrix GA)
{
	int i,j;
	printf("当前图的邻接矩阵如下：\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			printf("%4d",GA[i][j]);
		printf("\n");
	}
}

int main()
{
	vexlist GV;	
	adjmatrix GA;
	VertexType i;
    int j;
	printf("请输入图的顶点总数n=\n");
	scanf("%d",&n);	
	printf("请输入图的边总数e=\n");
	scanf("%d",&e);
	Create(GV,GA);
	printMatrix(GA);
	printf ("请输入从图的哪个顶点开始深度遍历：\n");
	scanf("%d",&i);  
	printf("深度遍历的结果为：");
	dfs(GV,GA,i);
    for(j=1;j<=n;j++)
        if(!visited[j])
            dfs(GV,GA,j);
	printf("END");
	return 0;
}
