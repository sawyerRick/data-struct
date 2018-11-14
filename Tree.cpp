#include <stdio.h>
#include <stdlib.h>
#include<math.h>

typedef int elemtype;
#define MAXSIZE 100
typedef struct bitTree
{
	elemtype weight;
	struct bitTree * lchild, * rchild;
}Node;

void creatNode(elemtype * arry,int length, Node * treeNode, int nodeIndex);
Node * initBitTree(elemtype * arry, int length);
void preOrder(Node * node);
void inOrder(Node * node);
void postOrder(Node * node);
void levelOrder(Node * node);
elemtype maxDiff(Node * node);
int findDiffValuePreOrder(Node * node, int * max, int * min);

int main()
{
	elemtype weightArray[MAXSIZE];//初始化完全二叉树
	int len = 0;
	printf("请输入权值个数:");
	scanf("%d", &len);
	for (int i = 0; i < len; i++)
	{
		scanf("%d", &weightArray[i]);
	}
	
	int max = weightArray[0], min = weightArray[0];
	int dValue = 0, * ptrMax = &max, * ptrMin = &min;
	
	
	Node * root = initBitTree(weightArray, len - 1 );
	printf("先序遍历找最大差绝对值:");
	dValue = findDiffValuePreOrder(root, ptrMax, ptrMin);
	printf("\ndValue:%d\n", dValue);
	/*
	printf("递归遍历...\n");
	printf("[+] 先序遍历:");
	preOrder(root);
	printf("\n");
	printf("[+] 中序遍历:");
	inOrder(root);
	printf("\n");
	printf("[+] 后序遍历:");
	postOrder(root);
	printf("\n");
	printf("非递归遍历...\n");
	printf("[+] 层序遍历:");
	levelOrder(root);
	printf("\n");
	*/

	return 0;
}

void creatNode(elemtype * arry, int length, Node * treeNode, int nodeIndex)
{
	if (arry == NULL || treeNode == NULL || nodeIndex < 0)
	{
		return ;
	}

	//左子树:2 * nodeIndex + 1
	if (2 * nodeIndex + 1 <= length)
	{
		treeNode->lchild = (Node *)malloc(sizeof(Node));
		treeNode->lchild->weight = arry[2 * nodeIndex + 1];
	}
	else
	{
		treeNode->lchild = NULL;
	}
	//右子树:2 * nodeIndex + 1
	if (2 * nodeIndex + 2 <= length)
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
		printf("%d  ", node->weight);
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
		printf("%d  ", nodeQueue[front]->weight);
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

int findDiffValuePreOrder(Node * node, int * max, int * min)
{
	if (node != NULL)
	{
		printf("%d  ", node->weight);
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