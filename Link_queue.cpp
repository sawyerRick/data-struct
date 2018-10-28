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
		printf("[+] �����г�ʼ���ɹ�...\n");
		LQ->front = head;
		LQ->rear = head;
		LQ->front->data = 0; //��һ���ڵ��ֵ0
		LQ->front->next = NULL;
		return LQ;
	}
	printf("[-] �����г�ʼ��ʧ��...n");

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
		printf("[+] data: %d �������...\n", x);
		node->data = x;
		node->next = NULL;
		LQ->rear->next = node;
		LQ->rear = node;
		return 1;
	}
	/*�㷨��:������β���β��(�ϸ���)
	QueueNode * tail = LQ->rear;
	if (node != NULL)
	{
		while(tail->next != NULL)
		{
			tail = tail->next;
		}
		printf("[+] data: %d �������...\n", x);
		node->data = x;
		node->next = NULL;
		tail->next = node;
		LQ->rear = node;
		return 1;
	}
	*/
	printf("[+] data: %d ���ʧ��...\n", x);
	return 0;
}

int deLinkQueue(LinkQueue * LQ, elemtype *x)
{
	QueueNode * node = LQ->front->next;
	if(isEmpty(LQ))
	{
		printf("[!] data: %d ���ܳ���...������Ϊ��...\n", node->data);
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
		printf("[-] data: %d ����...\n", *x);

		return 1;
	}
}

int getLength(LinkQueue * LQ)
{
	int len = 0;
	QueueNode * tail = LQ->front;
	if(isEmpty(LQ))
	{
		printf("[*] ����Ϊ��...\n");
		return 0;
	}
	while(tail->next != NULL)
	{
		tail = tail->next;
		len++;
	}
	printf("[*] ���ӳ���Ϊ: %d...\n", len);
	return len;
}

int freeLinkQueue(LinkQueue * LQ)
{
	QueueNode * node = LQ->front;
	QueueNode * tail = node;

	printf("[-] �����ͷ�������...\n");
	while(node != NULL)
	{
		tail = node;
		node = node->next;
		free(tail);
	}
	free(LQ);
	printf("[-] �ɹ��ͷ�������...\n\b");
	
	return 1;
}

int showLinkQueue(LinkQueue * LQ)
{
	QueueNode * node = LQ->front->next;
	printf("[*] չʾ������...\n");
	while(node != NULL)
	{
		printf("[*] data:%d ...\n", node->data);
		node = node->next;
	}
	return 0;
}