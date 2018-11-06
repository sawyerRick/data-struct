#include <stdio.h>
#include <stdlib.h>
#include<math.h>

typedef int elemtype;
#define MAXSIZE 100
typedef struct bitTree
{
	elemtype data;
	struct bitTree * lchild, * rchild;
}Node;

void creatNode(elemtype * arry,int length, Node * treeNode, int nodeIndex);
Node * initBitTree(elemtype * arry, int length);
void preOrder(Node * node);
void inOrder(Node * node);
void postOrder(Node * node);
void levelOrder(Node * node);

int main()
{
	elemtype bitTree[] = {0, 1, 2, 3, 4, 5, 6, 7};//初始化完全二叉树
	Node * root = initBitTree(bitTree, sizeof(bitTree) / sizeof(elemtype) - 1);
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
	printf("[+] 层序遍历:");
	levelOrder(root);
	printf("\n");

	return 0;
}

void creatNode(elemtype * arry, int length, Node * treeNode, int nodeIndex)
{
	if (arry == NULL || treeNode == NULL || nodeIndex < 0)
	{
		return ;
	}

	//左子树
	if (2 * nodeIndex + 1 <= length)
	{
		treeNode->lchild = (Node *)malloc(sizeof(Node));
		treeNode->lchild->data = arry[2 * nodeIndex + 1];
	}
	else
	{
		treeNode->lchild = NULL;
	}
	//右子树
	if (2 * nodeIndex + 2 <= length)
	{
		treeNode->rchild = (Node *)malloc(sizeof(Node));
		treeNode->rchild->data = arry[2 * nodeIndex + 2];
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
	root->data = arry[0];
	creatNode(arry, length, root, 0);

	return root;
}

void preOrder(Node * node)
{
	if (node != NULL)
	{
		printf("%d  ", node->data);
		preOrder(node->lchild);
		preOrder(node->rchild);
	}
}

void inOrder(Node * node)
{
	if (node != NULL)
	{
		inOrder(node->lchild);
		printf("%d  ", node->data);
		inOrder(node->rchild);
	}
}

void postOrder(Node * node)
{
	if (node != NULL)
	{
		postOrder(node->lchild);
		postOrder(node->rchild);
		printf("%d  ", node->data);
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
		printf("%d  ", nodeQueue[front]->data);
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