#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
typedef char VertexType;//��������
typedef int EdgeType;//�ߵ�Ȩ����
//�ڽӾ���MGraph
typedef struct
{
	VertexType vexs[MaxVertexNum];//�ڽӾ��󶥵��
	EdgeType edges[MaxVertexNum][MaxVertexNum];//�ڽӾ���(�߱�)
	int n, e;//������, ����
}MGraph;



//�ڽӱ�ALGraph
typedef struct node //�ڽӱ��С�ڵ���
{
	int adjvex;
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
	int visited[MaxVertexNum];//�����ʹ�
	int n, e;
}ALGraph;

void CreateMGraph(MGraph * G);//�����ڽӾ���
void DisplayMGraph(MGraph * G);//display�ڽӾ���
void CreateALGraph(ALGraph * G);//�����ڽӱ�
void DFSAL(ALGraph * G, int i);//������ȱ���--Depth First Search  ���ڽӱ�ALGraphʵ��
void BFSM(MGraph * G, int i);//������ȱ���--Breadth First Search  ���ڽӾ���MGraphʵ��

int main()
{
	//�ڽӾ���
	MGraph * G = (MGraph *)malloc(sizeof(MGraph));
	CreateMGraph(G);
	DisplayMGraph(G);

	//�ڽӱ�
	//ALGraph * ALG = (ALGraph *)malloc(sizeof(ALGraph));
	//CreateALGraph(ALG);
	//DFSAL(ALG, 0);

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
	//��ʼ���߱����
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
	printf("�����붥�����ͱ���:");
	scanf("%d %d", &(G->n), &(G->e));
	printf("�����붥�����\n");	//��ʼ����ͷ��������
	for (i = 0; i < G->n; i++)
	{
		getchar();
		printf("�������%3d:", i);
		scanf("%c", &(G->adjlist[i].vertex));
		G->adjlist[i].firstNode = NULL;
		G->visited[i] = 0;//��ʼ������
	}
	printf("������߶�Ӧ�������������:\n");
	//��ʼ���ڽӱ�
	for (k = 0; k < G->e; k++)
	{
		getchar();
		printf("��%d����:", k);
		scanf("%d %d", &i, &j);
		newNode = (EdgeNode *)malloc(sizeof(EdgeNode));
		newNode->adjvex = j;
		//ͷ��
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
		if (! G->visited[p->adjvex])//���p->adjvexδ����
		{
			DFSAL(G, p->adjvex);
		}
		p = p->next;
	}
}

void BFSM(MGraph * G, int i)
{
	CirQueue * Q;
}