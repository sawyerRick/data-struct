//图
//邻接矩阵MGraph，邻接表ALGraph
//Prim算法找最小生成树Prim(MGraph * G, int v);
//dijkstra算法找最短路径
//广度遍历找离k顶点最远的顶点n, void BFSMFindFurthestVex(MGraph * G, int k, int visited[]);
//FriendZone找朋友圈数量
#include <stdio.h>
#include <stdlib.h>
#include "Circle_queue.h"

#define MaxVertexNum 99
#define INF 32767 //无穷大
typedef char VertexType;//顶点类型
typedef int EdgeType;//边的权类型

//邻接矩阵MGraph
typedef struct
{
	VertexType vexs[MaxVertexNum];//邻接矩阵顶点符号表
	EdgeType edges[MaxVertexNum][MaxVertexNum];//邻接矩阵(边权构成的表)
	int n, e;//顶点数, 边数
}MGraph;

//邻接表ALGraph
typedef struct node //邻接表的小节点域
{
	int adjvex;//顶点序号
	struct node * next;
}EdgeNode;
typedef struct headNode //邻接表头节点域
{
	VertexType vertex;//邻接表顶点
	EdgeNode * firstNode;
}VertexNode;
typedef struct //邻接表
{
	VertexNode adjlist[MaxVertexNum];
	int n, e;//顶点数, 边数
}ALGraph;

//普里姆算法辅助数组closedge[n]为第n个顶点, adjvex:依附顶点, lowcost:closedge[n]与adjvex的边的权值
struct
{
	char adjvex;//依附顶点
	int lowcost;//最小权值
}closedge[MaxVertexNum];

void CreateMGraph(MGraph * G);//创建边不带权值的邻接矩阵
void CreateMGraphWithWeight(MGraph * G);//边带权值的邻接矩阵
void DisplayMGraph(MGraph * G);//display邻接矩阵
void CreateALGraph(ALGraph * G);//创建邻接表
void DFSAL(ALGraph * G, int k, int visited[]);//深度优先遍历--Depth First Search  用邻接表ALGraph实现
void DFSALIM(ALGraph * G);//优化深度优先遍历接口
void BFSM(MGraph * G, int k);//广度优先遍历--Breadth First Search  用邻接矩阵MGraph实现 
int BFSMFindFurthestVex(MGraph * G, int k);//广度优先找离K顶点最远的顶点
void Prim(MGraph * G, int v);//Prim算法最小生成树
void unitInitMGraphWithWeight(MGraph * G);//单元测试初始化带权邻接矩阵
void unitInitMGraph(MGraph * G);//单元测试初始化不带权邻接矩阵
void unitInitDirectedMGraphWithWeight(MGraph * G);//单元测试初始化带权有向邻接矩阵
void dijkstra(MGraph * G, int v);//dijkstra算法最短路径
void dispath(int dist[], int path[], int foundVexs[],int n, int v);//输出最短路径
void FriendZone(MGraph * G);//输入无向邻接矩阵，求朋友圈数量(用广度优先遍历)
void unitInitMGraphToFriendZone(MGraph * G);

int main()
{
	//邻接矩阵
	MGraph * G = (MGraph *)malloc(sizeof(MGraph));
	//printf("---------Prim算法找最小生成树:-----------\n");
	//unitInitMGraphWithWeight(G);
	//Prim(G, 0);

	//printf("---------在无向连通图中找离k最远的顶点----------\n");
	//unitInitMGraph(G);
	//BFSM(G, 0);
	//BFSMFindFurthestVex(G, 0);
	

	//CreateMGraphWithWeight(G);
	//DisplayMGraph(G);
	

	//邻接表
	//ALGraph * ALG = (ALGraph *)malloc(sizeof(ALGraph));
	//CreateALGraph(ALG);
	//DFSALIM(ALG);

	//dijkstra最短路径:
	printf("----------------dijkstra最短路径--------------------\n");
	unitInitDirectedMGraphWithWeight(G);
	dijkstra(G, 0);

	//找朋友圈
	printf("----------------找朋友圈--------------------\n");
	unitInitMGraphToFriendZone(G);
	FriendZone(G);
	free(G);

	return 0;
}

void CreateMGraph(MGraph * G)
{
	int i, j, k;
	printf("请输入顶点数和边数:");
	scanf("%d %d", &(G->n), &(G->e));
	printf("请输入顶点符号\n");	//初始化表头各个顶点
	for (i = 0; i < G->n; i++)
	{
		getchar();
		scanf("%c", &(G->vexs[i]));
	}
	//输出顶点表:
	printf("顶点表:\n");
	printf("序号|符号\n");
	for (i = 0; i < G->n; i++)
	{
		printf("%4d|%4c\n", i, G->vexs[i]);
	}
	//初始化不带权值的矩阵
	for (i = 0; i < G->n; i++)
	{
		for (j = 0; j < G->n; j++)
		{
			G->edges[i][j] = 0;
		}
	}
	printf("请输入边对应的两个顶点序号:\n");
	for (k = 0; k < G->e; k++)
	{
		getchar();
		scanf("%d %d", &i, &j);
		G->edges[i][j] = 1;
		//G->edges[j][i] = 1;无向
	}
}

void CreateMGraphWithWeight(MGraph * G)
{
	int i, j, k;
	printf("请输入顶点数和边数:");
	scanf("%d %d", &(G->n), &(G->e));
	printf("请输入顶点符号\n");	//初始化表头各个顶点
	for (i = 0; i < G->n; i++)
	{
		getchar();
		scanf("%c", &(G->vexs[i]));
	}
	//输出顶点表:
	printf("顶点表:\n");
	printf("序号|符号\n");
	for (i = 0; i < G->n; i++)
	{
		printf("%4d|%4c\n", i, G->vexs[i]);
	}
	//初始化边带权值的矩阵
	for (i = 0; i < G->n; i++)
	{
		for (j = 0; j < G->n; j++)
		{
			G->edges[i][j] = 101;
		}
	}
	printf("请输入边对应的两个顶点序号i,j和权值w如0 1 3:\n");
	EdgeType weight;
	for (k = 0; k < G->e; k++)
	{
		getchar();
		scanf("%d %d %d", &i, &j, &weight);
		G->edges[i][j] = weight;
		G->edges[j][i] = weight;//无向 对称
	}
}

void DisplayMGraph(MGraph * G)
{
	int i, j;
	for (i = 0; i < G->n; i++)
	{
		for (j = 0; j < G->n; j++)
		{
			if(G->edges[i][j] == INF)
			{
				printf("∞ ");
			}
			else
			{
				printf("%-2d ", G->edges[i][j]);
			}
		}
		printf("\n");
	}
}

void CreateALGraph(ALGraph * G)
{
	int i, j, k;
	EdgeNode * newNode;
	printf("请输入顶点数和边数:");
	scanf("%d %d", &(G->n), &(G->e));
	printf("请输入顶点符号\n");	//初始化表头各个顶点
	for (i = 0; i < G->n; i++)
	{
		getchar();
		printf("顶点序号%3d:", i);
		scanf("%c", &(G->adjlist[i].vertex));
		G->adjlist[i].firstNode = NULL;
	}
	//初始化邻接表
	for (k = 0; k < G->e; k++)
	{
		getchar();
		printf("请继续输入边对应的两个顶点序号:\n");
		scanf("%d %d", &i, &j);
		newNode = (EdgeNode *)malloc(sizeof(EdgeNode));
		newNode->adjvex = j;
		//头插
		newNode->next = G->adjlist[i].firstNode;
		G->adjlist[i].firstNode = newNode;
	}
}

void DFSAL(ALGraph * G, int k, int visited[])
{
	//深度优先遍历
	printf("visit vertex:V%c\n", G->adjlist[k].vertex);

	visited[k] = 1;
	EdgeNode * p;
	p = G->adjlist[k].firstNode;
	while(p)
	{
		if (!visited[p->adjvex])//如果p->adjvex未访问
		{
			DFSAL(G, p->adjvex, visited);
		}
		p = p->next;
	}
}

void DFSALIM(ALGraph * G)
{
	//包装一个空Vistited给DFSAL使用
	int visited[10] = {0};
	DFSAL(G, 0, visited);
}

void BFSM(MGraph * G, int k)
{
	//用队列进行广度优先遍历邻接矩阵MGraph
	//从第k个顶点开始
	CirQueue * queue = initQueue();
	printf("visit vertex:V%c\n", G->vexs[k]);
	int visited[MaxVertexNum] = {0};
	visited[k] = 1;
	enQueue(queue, k);
	while (!isEmpty(queue))
	{
		//出队访问同时将依附顶点入队
		int i = deQueue(queue);
		for (int j = 0; j < G->n; j++)
		{
			if (G->edges[i][j] == 1 && !visited[j])
			{
				printf("visit vertex:V%c\n", G->vexs[j]);
				visited[j] = 1;
				enQueue(queue, j);
			}
		}
	}
	freeCirQueue(queue);
}

int BFSMFindFurthestVex(MGraph * G, int k)
{
	//用队列进行广度优先遍历MGraph
	//从第k个顶点开始,找离k最远的顶点,返回最远的顶点的序号
	int furthest = k;
	CirQueue * queue = initQueue();
	printf("visit vertex:V%c\n", G->vexs[k]);
	int visited[MaxVertexNum] = {0};
	visited[k] = 1;
	enQueue(queue, k);
	while (!isEmpty(queue))
	{
		//出队访问同时将依附顶点入队
		int i = deQueue(queue);
		for (int j = 0; j < G->n; j++)
		{
			if (G->edges[i][j] == 1 && !visited[j])
			{
				printf("visit vertex:V%c\n", G->vexs[j]);
				visited[j] = 1;
				enQueue(queue, j);
				furthest = j;
			}
		}
	}
	freeCirQueue(queue);
	printf("furthest:%d\n", furthest);

	return furthest;
}

void Prim(MGraph * G, int v)
{
	/*Prim算法最小生成树
	思想:
	从某一个顶点进入连通子图,顶点加入U
	1.记录该点与依附顶点的边的权值(用closedge数组保存这个表)
	2.选取权值最小的依附边的顶点加入集合U
	3.如果有更小的权值,更新表并回到1.
	*/
	printf("从%c开始(空值为a):\n", G->vexs[v]);
	int k = 0;//最新添加的顶点的index
	int j;
	int i;
	int minCost;
	//加入第一个U
	closedge[v].lowcost = -1;
	//初始化closedge数组
	for (j = 0; j < G->n; j++)
	{
		if(j != v)
		{
			closedge[j].adjvex = v;
			closedge[j].lowcost = G->edges[v][j];
		}
	} 
	
	//依次把后续顶点加入U
	for  (i = 1; i < G->n; i++)
	{
		//找到下一个不在U中的
		for (j = 0; j < G->n; j++)
		{
			if (closedge[j].lowcost != -1)
			{
				k = j;
				break;
			}
		}
		minCost = closedge[k].lowcost;
		//定位不在U中权值最小的
		for (j = 0; j < G->n; j++)
		{
			if (closedge[j].lowcost < minCost && closedge[j].lowcost != -1)
			{
				minCost = closedge[j].lowcost;
				k = j;
			}
		}
		printf("边:(%c, %c)\n", closedge[k].adjvex, G->vexs[k]);

		//加入U
		closedge[k].lowcost = -1;
		//如果新加入的顶点的依附边的权值比原有closedge[j].lowcost权值小
		//更新closedge
		for (j = 0; j < G->n; j++)
		{
			//k为新加入的顶点的index
			if (G->edges[k][j] < closedge[j].lowcost)
			{
				closedge[j].adjvex = G->vexs[k];
				closedge[j].lowcost = G->edges[k][j];
			}
		}
	}
}

void unitInitMGraphWithWeight(MGraph * G)
{
	//用于测试Prim算法的带权邻接矩阵
	G->n = 4;//顶点数
	G->e = 5;//边数
	VertexType * vexs = "abcd";//测试顶点
	//测试对应顶点边的权
	int xyweight[5][3] = {
		{1, 2, 3},
		{0, 1, 6},
		{0, 2, 1},
		{2, 3, 5},
		{0, 3, 2},
	};
	for (int i = 0; i < G->n; i++)
	{
		G->vexs[i] = vexs[i];
	}
	//初始化权值为Max
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			G->edges[i][j] = INF;
			G->edges[j][i] = INF;
		}
	}
	//初始化
	for (int k = 0 ; k < G->e; k++)
	{
		int i = xyweight[k][0];
		int j = xyweight[k][1];
		G->edges[i][j] = xyweight[k][2];
		G->edges[j][i] = xyweight[k][2]; //无向 对称
	}
	printf("测试Prim的带权邻接矩阵:\n");
	DisplayMGraph(G);
}

void unitInitMGraph(MGraph * G)
{
	//用于测试BFSMFindFurthestVex的不带权邻接矩阵
	G->n = 5;//顶点数
	G->e = 3;//边数
	VertexType * vexs = "abcde";//测试顶点
	//测试对应顶点的边
	int xyweight[5][2] = {
		{1, 2},
		{0, 1},
		{3, 4},
	};
	for (int i = 0; i < G->n; i++)
	{
		G->vexs[i] = vexs[i];
	}
	//初始化权值为0
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			G->edges[i][j] = 0;
			G->edges[j][i] = 0;
		}
	}
	//初始化
	for (int k = 0 ; k < G->e; k++)
	{
		int i = xyweight[k][0];
		int j = xyweight[k][1];
		G->edges[i][j] = 1;
		G->edges[j][i] = 1; //无向 对称
	}
	printf("测试邻接矩阵:\n");
	DisplayMGraph(G);
}

void unitInitMGraphToFriendZone(MGraph * G)
{
	//用于测试BFSMFindFurthestVex的不带权邻接矩阵
	G->n = 9;//顶点数
	G->e = 5;//边数
	VertexType * vexs = "abcdefghi";//测试顶点
	//测试对应顶点的边
	int xyweight[5][2] = {
		{1, 2},
		{0, 1},
		{3, 4},
		{7, 8},
		{6, 5},
	};
	for (int i = 0; i < G->n; i++)
	{
		G->vexs[i] = vexs[i];
	}
	//初始化权值为0
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			G->edges[i][j] = 0;
			G->edges[j][i] = 0;
		}
	}
	//初始化
	for (int k = 0 ; k < G->e; k++)
	{
		int i = xyweight[k][0];
		int j = xyweight[k][1];
		G->edges[i][j] = 1;
		G->edges[j][i] = 1; //无向 对称
	}
	printf("测试朋友圈邻接矩阵:\n");
	DisplayMGraph(G);
}

void unitInitDirectedMGraphWithWeight(MGraph * G)
{
	//用于测试dijkstra最短路径算法的带权有向邻接矩阵
	G->n = 5;//顶点数
	G->e = 5;//边数
	VertexType * vexs = "abcde\0";//测试顶点
	//测试对应顶点边的权
	int xyweight[5][3] = {
		{1, 2, 3},
		{0, 1, 6},
		{0, 2, 1},
		{2, 3, 5},
		{2, 4, 2},
	};
	for (int i = 0; i < G->n; i++)
	{
		G->vexs[i] = vexs[i];
	}
	//初始化权值为Max
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			G->edges[i][j] = INF;
			G->edges[j][i] = INF;
		}
	}
	//初始化
	for (int k = 0 ; k < G->e; k++)
	{
		int i = xyweight[k][0];
		int j = xyweight[k][1];
		G->edges[i][j] = xyweight[k][2];
		//G->edges[j][i] = xyweight[k][2]; //无向 对称
	}
	printf("测试dijkstra邻接矩阵:\n");
	DisplayMGraph(G);
}

void dijkstra(MGraph * G, int v)
{
	int dist[MaxVertexNum];//dist[n]保存v到n的距离
	int path[MaxVertexNum];//path[n]表示 v到n的前一个顶点的index
	int foundVexs[MaxVertexNum];//保存已经找到的最短路径的顶点

	int mindis;
	int i;
	int j;
	int k;

	//初始化
	for ( i = 0; i < G->n; i++)
	{
		dist[i] = G->edges[v][i];
		foundVexs[i] = 0;
		if (G->edges[v][i] < INF)
		{
			path[i] = v;
		}
		else
		{
			path[i] = -1;
		}
	}
	foundVexs[v] = 1;
	for (i = 0; i < G->n; i++)
	{
		mindis = INF;
		k = v;
		//从未加入foundVexs中的顶点中找离v最近的
		for (j = 0; j < G->n; j++)
		{
			if (foundVexs[j] == 0 && dist[j] < mindis)
			{
				k = j;
				mindis = dist[j];
			}
		}
		//把离v最小的顶点加入到foundVexs
		foundVexs[k] = 1;
		//更新距离
		for (j = 0; j < G->n; j++)
		{
			if (foundVexs[j] == 0 && G->edges[k][j] < INF && dist[k] + G->edges[k][j] < dist[j])
			{
				dist[j] = dist[k] + G->edges[k][j];
				path[j] = k;
			}
		}
	}
	printf("dijkstra测试矩阵:");
	dispath(dist, path, foundVexs, G->n, v);
}

void dispath(int dist[], int path[], int foundVexs[],int n, int v)
{
	int i, k;

	for (i = 0; i < n; i++)
	{
		if (i == v) //防止V0到V0
		{
			continue;
		}
		if (foundVexs[i] == 1)
		{
			k = i;
			printf("V%d 到 V%d 的最短路径为:", v, i);
			while (k != v)
			{
				printf("V%d <- ", k);
				k = path[k];
			}
			printf("V%d 路径长度为:%d\n", v, dist[i]);
		}
		else
		{
			printf("V%d <- V%d 不存在路径\n", i, v);
		}
	}
}

void FriendZone(MGraph * G)
{
	//思想:广度优先遍历邻接矩阵
	//1遍历过的顶点都存入foundVexs
	//2退出遍历FriendZoneCounter++
	//3从不在foundVexs里的顶点取顶点，继续1
	printf("Zone1:\n");
	int foundVexs[MaxVertexNum] = {0};//找到顶点数组
	int finder = 1;//找到顶点个数
	int FriendZoneCounter = 0;
	int k = 0;
	int i = 0;

	CirQueue * queue = initQueue();
	printf("V%d -- ", k);
	foundVexs[k] = 1;
	enQueue(queue, k);

	while (finder < G->n)
	{
		//出队访问同时将依附顶点入队
		i = deQueue(queue);
		for (int j = 0; j < G->n; j++)
		{
			if (G->edges[i][j] == 1 && !foundVexs[j])
			{
				printf("V%d -- ", j);
				foundVexs[j] = 1;
				enQueue(queue, j);
				finder++;
			}
		}
		if (isEmpty(queue))//一个朋友圈结束
		{
			FriendZoneCounter++;
			printf("\nnew Zone:\n");
			//从不在foundVexs里的顶点取顶点
			for (int j = 0; j < G->n; j++)
			{
				if (foundVexs[j] != 1)
				{
					enQueue(queue, j);
					break;
				}
			}
		}
	}
	printf("\n一共有%d个朋友圈。\n", FriendZoneCounter);
}