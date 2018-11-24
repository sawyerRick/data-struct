//ͼ
//�ڽӾ���MGraph���ڽӱ�ALGraph
//Prim�㷨����С������Prim(MGraph * G, int v);
//��ȱ�������k������Զ�Ķ���n, void BFSMFindFurthestVex(MGraph * G, int k, int visited[]);
#include <stdio.h>
#include <stdlib.h>
#include "Circle_queue.h"

#define MaxVertexNum 99
typedef char VertexType;//��������
typedef int EdgeType;//�ߵ�Ȩ����
//�ڽӾ���MGraph
typedef struct
{
	VertexType vexs[MaxVertexNum];//�ڽӾ��󶥵���ű�
	EdgeType edges[MaxVertexNum][MaxVertexNum];//�ڽӾ���(��Ȩ���ɵı�)
	int n, e;//������, ����
}MGraph;

//�ڽӱ�ALGraph
typedef struct node //�ڽӱ��С�ڵ���
{
	int adjvex;//�������
	struct node * next;
}EdgeNode;
typedef struct headNode //�ڽӱ�ͷ�ڵ���
{
	VertexType vertex;//�ڽӱ���
	EdgeNode * firstNode;
}VertexNode;
typedef struct //�ڽӱ�
{
	VertexNode adjlist[MaxVertexNum];
	int n, e;//������, ����
}ALGraph;

//����ķ�㷨��������closedge[n]Ϊ��n������, adjvex:��������, lowcost:closedge[n]��adjvex�ıߵ�Ȩֵ
struct
{
	char adjvex;//��������
	int lowcost;//��СȨֵ
}closedge[MaxVertexNum];

void CreateMGraph(MGraph * G);//�����߲���Ȩֵ���ڽӾ���
void CreateMGraphWithWeight(MGraph * G);//�ߴ�Ȩֵ���ڽӾ���
void DisplayMGraph(MGraph * G);//display�ڽӾ���
void CreateALGraph(ALGraph * G);//�����ڽӱ�
void DFSAL(ALGraph * G, int k, int visited[]);//������ȱ���--Depth First Search  ���ڽӱ�ALGraphʵ��
void DFSALIM(ALGraph * G);//�Ż�������ȱ����ӿ�
void BFSM(MGraph * G, int k);//������ȱ���--Breadth First Search  ���ڽӾ���MGraphʵ�� 
int BFSMFindFurthestVex(MGraph * G, int k);//�����������K������Զ�Ķ���
void Prim(MGraph * G, int v);//Prim�㷨��С������
void unitInitMGraphWithWeight(MGraph * G);//��Ԫ���Գ�ʼ����Ȩ�ڽӾ���
void unitInitMGraph(MGraph * G);//��Ԫ���Գ�ʼ������Ȩ�ڽӾ���

int main()
{
	//�ڽӾ���
	MGraph * G = (MGraph *)malloc(sizeof(MGraph));
	printf("---------Prim�㷨����С������:-----------\n");
	unitInitMGraphWithWeight(G);
	Prim(G, 0);

	printf("---------��������ͨͼ������k��Զ�Ķ���----------\n");
	unitInitMGraph(G);
	//BFSM(G, 0);
	BFSMFindFurthestVex(G, 0);
	

	//CreateMGraphWithWeight(G);
	//DisplayMGraph(G);
	

	//�ڽӱ�
	//ALGraph * ALG = (ALGraph *)malloc(sizeof(ALGraph));
	//CreateALGraph(ALG);
	//DFSALIM(ALG);
	free(G);

	return 0;
}

void CreateMGraph(MGraph * G)
{
	int i, j, k;
	printf("�����붥�����ͱ���:");
	scanf("%d %d", &(G->n), &(G->e));
	printf("�����붥�����\n");	//��ʼ����ͷ��������
	for (i = 0; i < G->n; i++)
	{
		getchar();
		scanf("%c", &(G->vexs[i]));
	}
	//��������:
	printf("�����:\n");
	printf("���|����\n");
	for (i = 0; i < G->n; i++)
	{
		printf("%4d|%4c\n", i, G->vexs[i]);
	}
	//��ʼ������Ȩֵ�ľ���
	for (i = 0; i < G->n; i++)
	{
		for (j = 0; j < G->n; j++)
		{
			G->edges[i][j] = 0;
		}
	}
	printf("������߶�Ӧ�������������:\n");
	for (k = 0; k < G->e; k++)
	{
		getchar();
		scanf("%d %d", &i, &j);
		G->edges[i][j] = 1;
		//G->edges[j][i] = 1;����
	}
}

void CreateMGraphWithWeight(MGraph * G)
{
	int i, j, k;
	printf("�����붥�����ͱ���:");
	scanf("%d %d", &(G->n), &(G->e));
	printf("�����붥�����\n");	//��ʼ����ͷ��������
	for (i = 0; i < G->n; i++)
	{
		getchar();
		scanf("%c", &(G->vexs[i]));
	}
	//��������:
	printf("�����:\n");
	printf("���|����\n");
	for (i = 0; i < G->n; i++)
	{
		printf("%4d|%4c\n", i, G->vexs[i]);
	}
	//��ʼ���ߴ�Ȩֵ�ľ���
	for (i = 0; i < G->n; i++)
	{
		for (j = 0; j < G->n; j++)
		{
			G->edges[i][j] = 101;
		}
	}
	printf("������߶�Ӧ�������������i,j��Ȩֵw��0 1 3:\n");
	EdgeType weight;
	for (k = 0; k < G->e; k++)
	{
		getchar();
		scanf("%d %d %d", &i, &j, &weight);
		G->edges[i][j] = weight;
		G->edges[j][i] = weight;//���� �Գ�
	}
}

void DisplayMGraph(MGraph * G)
{
	int i, j;
	for (i = 0; i < G->n; i++)
	{
		for (j = 0; j < G->n; j++)
		{
			printf("%-4d", G->edges[i][j]);
		}
		printf("\n");
	}
}

void CreateALGraph(ALGraph * G)
{
	int i, j, k;
	EdgeNode * newNode;
	printf("�����붥�����ͱ���:");
	scanf("%d %d", &(G->n), &(G->e));
	printf("�����붥�����\n");	//��ʼ����ͷ��������
	for (i = 0; i < G->n; i++)
	{
		getchar();
		printf("�������%3d:", i);
		scanf("%c", &(G->adjlist[i].vertex));
		G->adjlist[i].firstNode = NULL;
	}
	//��ʼ���ڽӱ�
	for (k = 0; k < G->e; k++)
	{
		getchar();
		printf("���������߶�Ӧ�������������:\n");
		scanf("%d %d", &i, &j);
		newNode = (EdgeNode *)malloc(sizeof(EdgeNode));
		newNode->adjvex = j;
		//ͷ��
		newNode->next = G->adjlist[i].firstNode;
		G->adjlist[i].firstNode = newNode;
	}
}

void DFSAL(ALGraph * G, int k, int visited[])
{
	//������ȱ���
	printf("visit vertex:V%c\n", G->adjlist[k].vertex);

	visited[k] = 1;
	EdgeNode * p;
	p = G->adjlist[k].firstNode;
	while(p)
	{
		if (!visited[p->adjvex])//���p->adjvexδ����
		{
			DFSAL(G, p->adjvex, visited);
		}
		p = p->next;
	}
}

void DFSALIM(ALGraph * G)
{
	//��װһ����Vistited��DFSALʹ��
	int visited[10] = {0};
	DFSAL(G, 0, visited);
}

void BFSM(MGraph * G, int k)
{
	//�ö��н��й�����ȱ����ڽӾ���MGraph
	//�ӵ�k�����㿪ʼ
	CirQueue * queue = initQueue();
	printf("visit vertex:V%c\n", G->vexs[k]);
	int visited[MaxVertexNum] = {0};
	visited[k] = 1;
	enQueue(queue, k);
	while (!isEmpty(queue))
	{
		//���ӷ���ͬʱ�������������
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
	//�ö��н��й�����ȱ���MGraph
	//�ӵ�k�����㿪ʼ,����k��Զ�Ķ���,������Զ�Ķ�������
	int furthest = k;
	CirQueue * queue = initQueue();
	printf("visit vertex:V%c\n", G->vexs[k]);
	int visited[MaxVertexNum] = {0};
	visited[k] = 1;
	enQueue(queue, k);
	while (!isEmpty(queue))
	{
		//���ӷ���ͬʱ�������������
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
	/*Prim�㷨��С������
	˼��:
	��ĳһ�����������ͨ��ͼ,�������U
	1.��¼�õ�����������ıߵ�Ȩֵ(��closedge���鱣�������)
	2.ѡȡȨֵ��С�������ߵĶ�����뼯��U
	3.����и�С��Ȩֵ,���±��ص�1.
	*/
	printf("��%c��ʼ(��ֵΪa):\n", G->vexs[v]);
	int k = 0;//������ӵĶ����index
	int j;
	int i;
	int minCost;
	//�����һ��U
	closedge[v].lowcost = -1;
	//��ʼ��closedge����
	for (j = 0; j < G->n; j++)
	{
		if(j != v)
		{
			closedge[j].adjvex = v;
			closedge[j].lowcost = G->edges[v][j];
		}
	} 
	
	//���ΰѺ����������U
	for  (i = 1; i < G->n; i++)
	{
		//�ҵ���һ������U�е�
		for (j = 0; j < G->n; j++)
		{
			if (closedge[j].lowcost != -1)
			{
				k = j;
				break;
			}
		}
		minCost = closedge[k].lowcost;
		//��λ����U��Ȩֵ��С��
		for (j = 0; j < G->n; j++)
		{
			if (closedge[j].lowcost < minCost && closedge[j].lowcost != -1)
			{
				minCost = closedge[j].lowcost;
				k = j;
			}
		}
		printf("��:(%c, %c)\n", closedge[k].adjvex, G->vexs[k]);

		//����U
		closedge[k].lowcost = -1;
		//����¼���Ķ���������ߵ�Ȩֵ��ԭ��closedge[j].lowcostȨֵС
		//����closedge
		for (j = 0; j < G->n; j++)
		{
			//kΪ�¼���Ķ����index
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
	//���ڲ���Prim�㷨�Ĵ�Ȩ�ڽӾ���
	G->n = 4;//������
	G->e = 5;//����
	VertexType * vexs = "abcd";//���Զ���
	//���Զ�Ӧ����ߵ�Ȩ
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
	//��ʼ��ȨֵΪMax
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			G->edges[i][j] = 99;
			G->edges[j][i] = 99;
		}
	}
	//��ʼ��
	for (int k = 0 ; k < G->e; k++)
	{
		int i = xyweight[k][0];
		int j = xyweight[k][1];
		G->edges[i][j] = xyweight[k][2];
		G->edges[j][i] = xyweight[k][2]; //���� �Գ�
	}
	printf("����Prim�Ĵ�Ȩ�ڽӾ���:\n");
	DisplayMGraph(G);
}

void unitInitMGraph(MGraph * G)
{
	//���ڲ���BFSMFindFurthestVex�Ĳ���Ȩ�ڽӾ���
	G->n = 5;//������
	G->e = 5;//����
	VertexType * vexs = "abcde";//���Զ���
	//���Զ�Ӧ����ߵ�Ȩ
	int xyweight[5][2] = {
		{1, 2},
		{0, 1},
		{2, 3},
		{0, 3},
		{2, 4},
	};
	for (int i = 0; i < G->n; i++)
	{
		G->vexs[i] = vexs[i];
	}
	//��ʼ��ȨֵΪMax
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			G->edges[i][j] = 0;
			G->edges[j][i] = 0;
		}
	}
	//��ʼ��
	for (int k = 0 ; k < G->e; k++)
	{
		int i = xyweight[k][0];
		int j = xyweight[k][1];
		G->edges[i][j] = 1;
		G->edges[j][i] = 1; //���� �Գ�
	}
	printf("�����ڽӾ���:\n");
	DisplayMGraph(G);
}

