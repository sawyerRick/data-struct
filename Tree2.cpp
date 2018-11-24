// 二叉树的创建，先序，中序，后序，层次遍历，找出权值绝对值相差最大的两个节点
// 创建只适用于完全二叉树(输入#为空节点)

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
void preOrder(Node * node);//先序递归遍历
void inOrder(Node * node);//中序递归遍历
void postOrder(Node * node);//后序递归遍历
void levelOrder(Node * node);//层次遍历
elemtype findDiffValuePreOrder(Node * node, elemtype * max, elemtype * min);//找权值绝对值相差最大的两个节点的值

int main()
{
	elemtype weightArray[MAXSIZE];//初始化完全二叉树
	int len = 0;
	printf("请输入权值个数:");
	scanf("%d", &len);
	printf("请输入权值(完全二叉树形式按层遍历顺序输入，#为空值):");
	for (int i = 0; i < len; i++)
	{
		getchar();
		scanf("%c", &weightArray[i]);
	}
	
	elemtype max = weightArray[0], min = weightArray[0];
	elemtype dValue = 0, * ptrMax = &max, * ptrMin = &min;
	
	
	Node * root = initBitTree(weightArray, len - 1 );
	printf("先序遍历找最大差绝对值:");
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

	//左子树:2 * nodeIndex + 1
	if (2 * nodeIndex + 1 <= length && arry[2 * nodeIndex + 1] != '#')
	{
		treeNode->lchild = (Node *)malloc(sizeof(Node));
		treeNode->lchild->weight = arry[2 * nodeIndex + 1];
	}
	//左子树为空
	else
	{
		treeNode->lchild = NULL;
	}
	//右子树:2 * nodeIndex + 1
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