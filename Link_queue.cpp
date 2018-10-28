#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
typedef struct queueNode
{
	elemtype data;
	queueNode * next;
}QueueNode;

typedef struct linkQueue
{
	QueueNode * front, * rear;
}LinkQueue;

LinkQueue * initQueue();
int isEmpty(LinkQueue * LQ);
int enLinkQueue(LinkQueue * LQ, elemtype x);
int deLinkQueue(LinkQueue * LQ, elemtype *x);
int getLength(LinkQueue * LQ);
int freeLinkQueue(LinkQueue * LQ);
int showLinkQueue(LinkQueue * LQ);

int main()
{
	LinkQueue * LQ = initQueue();
	elemtype x = 0;
	int i;
	for(i = 0; i < 4; i++)
	{
		enLinkQueue(LQ, i);
	}
	getLength(LQ);
	
	for(i = 0; i < 2; i++)
	{
 		deLinkQueue(LQ, &x);
	}
	getLength(LQ);
	showLinkQueue(LQ);
	freeLinkQueue(LQ);

	return 0;                                                                          
}

LinkQueue * initQueue()
{
	LinkQueue * LQ = (LinkQueue *)malloc(sizeof(LinkQueue));
	QueueNode * head = (QueueNode *)malloc(sizeof(QueueNode));
	if (LQ != NULL && head != NULL)
	{
		printf("[+] 链队列初始化成功...\n");
		LQ->front = head;
		LQ->rear = head;
		LQ->front->data = 0; //第一个节点空值0
		LQ->front->next = NULL;
		return LQ;
	}
	printf("[-] 链队列初始化失败...n");

	return 0;
}

int isEmpty(LinkQueue * LQ)
{
	if (LQ->front == LQ->rear)
	{
		return 1;
	}
	return 0;
}

int enLinkQueue(LinkQueue * LQ, elemtype x)
{
	QueueNode * node = (QueueNode *)malloc(sizeof(QueueNode));
	if (node != NULL)
	{
		printf("[+] data: %d 正在入队...\n", x);
		node->data = x;
		node->next = NULL;
		LQ->rear->next = node;
		LQ->rear = node;
		return 1;
	}
	/*算法二:遍历到尾结点尾插(较复杂)
	QueueNode * tail = LQ->rear;
	if (node != NULL)
	{
		while(tail->next != NULL)
		{
			tail = tail->next;
		}
		printf("[+] data: %d 正在入队...\n", x);
		node->data = x;
		node->next = NULL;
		tail->next = node;
		LQ->rear = node;
		return 1;
	}
	*/
	printf("[+] data: %d 入队失败...\n", x);
	return 0;
}

int deLinkQueue(LinkQueue * LQ, elemtype *x)
{
	QueueNode * node = LQ->front->next;
	if(isEmpty(LQ))
	{
		printf("[!] data: %d 不能出队...链队列为空...\n", node->data);
		return 0;
	}
	else
	{
		*x = node->data;
		LQ->front->next = node->next;
		if(node == LQ->rear)
		{
			LQ->front = LQ->rear;
		}
		free(node);
		printf("[-] data: %d 出队...\n", *x);

		return 1;
	}
}

int getLength(LinkQueue * LQ)
{
	int len = 0;
	QueueNode * tail = LQ->front;
	if(isEmpty(LQ))
	{
		printf("[*] 链队为空...\n");
		return 0;
	}
	while(tail->next != NULL)
	{
		tail = tail->next;
		len++;
	}
	printf("[*] 链队长度为: %d...\n", len);
	return len;
}

int freeLinkQueue(LinkQueue * LQ)
{
	QueueNode * node = LQ->front;
	QueueNode * tail = node;

	printf("[-] 正在释放链队列...\n");
	while(node != NULL)
	{
		tail = node;
		node = node->next;
		free(tail);
	}
	free(LQ);
	printf("[-] 成功释放链队列...\n\b");
	
	return 1;
}

int showLinkQueue(LinkQueue * LQ)
{
	QueueNode * node = LQ->front->next;
	printf("[*] 展示链队列...\n");
	while(node != NULL)
	{
		printf("[*] data:%d ...\n", node->data);
		node = node->next;
	}
	return 0;
}