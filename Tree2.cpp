// �������Ĵ������������򣬺��򣬲�α������ҳ�Ȩֵ����ֵ������������ڵ�
// ����ֻ��������ȫ������(����#Ϊ�սڵ�)

#include <stdio.h>
#include <stdlib.h>
#include<math.h>

typedef char elemtype;
#define MAXSIZE 100
typedef struct bitTree
{
	elemtype weight;
	struct bitTree * lchild, * rchild;
}Node;

void creatNode(elemtype * arry,int length, Node * treeNode, int nodeIndex);
Node * initBitTree(elemtype * arry, int length);
void preOrder(Node * node);//����ݹ����
void inOrder(Node * node);//����ݹ����
void postOrder(Node * node);//����ݹ����
void levelOrder(Node * node);//��α���
elemtype findDiffValuePreOrder(Node * node, elemtype * max, elemtype * min);//��Ȩֵ����ֵ������������ڵ��ֵ

int main()
{
	elemtype weightArray[MAXSIZE];//��ʼ����ȫ������
	int len = 0;
	printf("������Ȩֵ����:");
	scanf("%d", &len);
	printf("������Ȩֵ(��ȫ��������ʽ�������˳�����룬#Ϊ��ֵ):");
	for (int i = 0; i < len; i++)
	{
		getchar();
		scanf("%c", &weightArray[i]);
	}
	
	elemtype max = weightArray[0], min = weightArray[0];
	elemtype dValue = 0, * ptrMax = &max, * ptrMin = &min;
	
	
	Node * root = initBitTree(weightArray, len - 1 );
	printf("����������������ֵ:");
	dValue = findDiffValuePreOrder(root, ptrMax, ptrMin);
	printf("\ndValue:%d\n", dValue);

	return 0;
}

void creatNode(elemtype * arry, int length, Node * treeNode, int nodeIndex)
{
	if (arry == NULL || treeNode == NULL || nodeIndex > length)
	{
		return ;
	}

	//������:2 * nodeIndex + 1
	if (2 * nodeIndex + 1 <= length && arry[2 * nodeIndex + 1] != '#')
	{
		treeNode->lchild = (Node *)malloc(sizeof(Node));
		treeNode->lchild->weight = arry[2 * nodeIndex + 1];
	}
	//������Ϊ��
	else
	{
		treeNode->lchild = NULL;
	}
	//������:2 * nodeIndex + 1
	if (2 * nodeIndex + 2 <= length && arry[2 * nodeIndex + 2] != '#')
	{
		treeNode->rchild = (Node *)malloc(sizeof(Node));
		treeNode->rchild->weight = arry[2 * nodeIndex + 2];
	}
	else
	{
		treeNode->rchild = NULL;
	}

	creatNode(arry, length, treeNode->lchild, 2 * nodeIndex + 1);
	creatNode(arry, length, treeNode->rchild, 2 * nodeIndex + 2);
}

Node * initBitTree(elemtype * arry, int length)
{
	if (arry == NULL)
	{
		return NULL;
	}
	Node * root = (Node *)malloc(sizeof(Node));
	root->weight = arry[0];
	creatNode(arry, length, root, 0);

	return root;
}

void preOrder(Node * node)
{
	if (node != NULL)
	{
		printf("%d  ", node->weight);
		preOrder(node->lchild);
		preOrder(node->rchild);
	}
}

void inOrder(Node * node)
{
	if (node != NULL)
	{
		inOrder(node->lchild);
		printf("%d  ", node->weight);
		inOrder(node->rchild);
	}
}

void postOrder(Node * node)
{
	if (node != NULL)
	{
		postOrder(node->lchild);
		postOrder(node->rchild);
		printf("%c  ", node->weight);
	}
}

void levelOrder(Node * node)
{
	Node * nodeQueue[MAXSIZE];
	int front = -1, rear = -1;

	rear++; 
	nodeQueue[rear] = node;
	while (front != rear)
	{
		front++;
		printf("%c  ", nodeQueue[front]->weight);
		if (nodeQueue[front]->lchild != NULL)
		{
			rear++;
			nodeQueue[rear] = nodeQueue[front]->lchild;
		}
		if (nodeQueue[front]->rchild != NULL)
		{
			rear++;
			nodeQueue[rear] = nodeQueue[front]->rchild;
		}
	}
}

elemtype findDiffValuePreOrder(Node * node, elemtype * max, elemtype * min)
{
	if (node != NULL)
	{
		printf("%c  ", node->weight);
		if (node->weight >= *max) {
			*max = node->weight;
			//printf("max:%d\n", *max);
		}
		if (node->weight <= *min) {
			*min = node->weight;
			//printf("min:%d\n", *min);
		}
		findDiffValuePreOrder(node->lchild, max, min);
		findDiffValuePreOrder(node->rchild, max, min);
		return abs(*max - *min);
	}
}