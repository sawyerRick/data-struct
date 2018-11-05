#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
typedef char VertexType;//顶点类型
typedef int EdgeType;//边的权类型
//邻接矩阵
typedef struct
{
	VertexType vexs[MaxVertexNum];//顶点表
	EdgeType edges[MaxVertexNum][MaxVertexNum];//邻接矩阵(边表)
	int n, e;//顶点数, 边数
}MGraph;

//邻接表
typedef struct node //表节点
{
	int adjvex;
	struct node * next;
}EdgeNode;
typedef struct headNode //表头节点
{
	VertexType vertex;//顶点
	EdgeNode * firstNode;
}VertexNode;
typedef struct //表
{
	VertexNode adjlist[MaxVertexNum];
	int visited[MaxVertexNum];//被访问过
	int n, e;
}ALGraph;

void CreateMGraph(MGraph * G);
void DisplayMGraph(MGraph * G);
void CreateALGraph(ALGraph * G);
void DFSAL(ALGraph * G, int i);

int main()
{
	//邻接矩阵
	//MGraph * G = (MGraph *)malloc(sizeof(MGraph));
	//CreateMGraph(G);
	//DisplayMGraph(G);

	//邻接表
	ALGraph * ALG = (ALGraph *)malloc(sizeof(ALGraph));
	CreateALGraph(ALG);
	DFSAL(ALG, 0);

	return 0;
}

void CreateMGraph(MGraph * G)
{
	int i, j, k;
	printf("请输入顶点数和边数(提示:顶点数,边数  如 3,2):\n");
	scanf("%d,%d", &(G->n), &(G->e));
	printf("请输入顶点信息(提示:顶点符号<回车> 如 a):\n");
	fflush(stdin);
	for (i = 0; i < G->n; i++)
	{
		scanf("%c", &(G->vexs[i]));
		fflush(stdin);
	}
	//输出顶点表:
	printf("顶点表:\n");
	printf("序号|符号\n");
	for (i = 0; i < G->n; i++)
	{
		printf("%4d|%4c\n", i, G->vexs[i]);
	}
	//初始化边表矩阵
	for (i = 0; i < G->n; i++)
	{
		for (j = 0; j < G->n; j++)
		{
			G->edges[i][j] = 0;
		}
	}
	printf("请输入每条边对应的两个顶点序号(从0开始:i, j):\n");
	fflush(stdin);
	for (k = 0; k < G->e; k++)
	{
		scanf("%d,%d", &i, &j);
		fflush(stdin);
		G->edges[i][j] = 1;
		//G->edges[j][i] = 1;无向
	}
}

void DisplayMGraph(MGraph * G)
{
	int i, j;
	for (i = 0; i <= G->e; i++)
	{
		for (j = 0; j <= G->e; j++)
		{
			if (G->edges[i][j] == 1)
			{
				printf("1  ");
			}
			else
			{
				printf("0  ");
			}
		}
		printf("\n");
	}
}

void CreateALGraph(ALGraph * G)
{
	int i, j, k;
	EdgeNode * newNode;
	printf("请输入顶点数和边数(提示:顶点数,边数  如 3,2):\n");
	scanf("%d,%d", &(G->n), &(G->e));
	printf("请输入顶点信息(提示:顶点符号<回车> 如 a):\n");
	fflush(stdin);
	//初始化表头各个顶点
	for (i = 0; i < G->n; i++)
	{
		scanf("%c", &(G->adjlist[i].vertex));
		G->adjlist[i].firstNode = NULL;
		G->visited[i] = 0;//初始化访问
		fflush(stdin);
	}
	printf("请输入每条边对应的两个顶点序号(从0开始:i, j):\n");
	fflush(stdin);
	//初始化邻接表
	for (k = 0; k < G->e; k++)
	{
		scanf("%d,%d", &i, &j);
		fflush(stdin);
		newNode = (EdgeNode *)malloc(sizeof(EdgeNode));
		newNode->adjvex = j;
		//头插
		newNode->next = G->adjlist[i].firstNode;
		G->adjlist[i].firstNode = newNode;
	}
}

void DFSAL(ALGraph * G, int i)
{
	EdgeNode * p;
	printf("visit vertex:V%c\n", G->adjlist[i].vertex);

	G->visited[i] = 1;
	p = G->adjlist[i].firstNode;
	while(p)
	{
		if (! G->visited[p->adjvex])//如果p->adjvex未访问
		{
			DFSAL(G, p->adjvex);
		}
		p = p->next;
	}
}