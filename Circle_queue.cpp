#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 4
typedef int elemtype;
typedef struct
{
	elemtype data[MAXSIZE];
	int front;
	int rear;
}CircleQueue;

CircleQueue * initQueue();
int isEmpty(CircleQueue * queue);
int isFull(CircleQueue * queue);
int getLength(CircleQueue * queue);
int enterQueue(CircleQueue * queue, elemtype x);
int deQueue(CircleQueue * queue, elemtype * x);
int freeQueue(CircleQueue * queue);
void showQueue(CircleQueue * queue);

int main()
{
	int i = 0;
	elemtype x = 0;
	CircleQueue * queue = initQueue();
	for(; i < 4; i++)
	{
		enterQueue(queue, i);
	}
	showQueue(queue);
	for(i = 0; i < 4; i++)
	{
		deQueue(queue, &x);
	}
	showQueue(queue);

	return 0;
}

CircleQueue * initQueue()
{
	CircleQueue * queue = (CircleQueue *)malloc(sizeof(CircleQueue));
	if(queue != NULL)
	{
		printf("[+] 初始化队列成功...\n");
		queue->rear = 0;
		queue->front = 0;
		return queue;
	}
	printf("[-] 初始化队列失败...\n");
	return 0;
}

int isEmpty(CircleQueue * queue)
{
	if(queue->front == queue->rear)
	{
		return 1;
	}
	return 0;
}

int isFull(CircleQueue * queue)
{
	if(queue->front == (queue->rear + 1) % MAXSIZE)
	{
		return 1;
	}
	return 0;
}

int getLength(CircleQueue * queue)
{
	int len = (queue->rear - queue->front + MAXSIZE) % MAXSIZE;
	printf("[+] 队列长度为: %d \n", len);
	return len;
}

int enterQueue(CircleQueue * queue, elemtype x)
{
	if(isFull(queue))
	{
		printf("[!] 队列为满...不能入队\n");
		return 0;
	}
	else
	{
		queue->data[queue->rear] = x;
		printf("[+] inde: %d data: %d 入队成功...\n", queue->rear, x);
		queue->rear = (queue->rear + 1) % MAXSIZE;
		return 0;
	}
}

int deQueue(CircleQueue * queue, elemtype * x)
{
	if(isEmpty(queue))
	{
		printf("[!] 队为空...出队失败...\n");
		return 0;
	}
	else
	{
		*x = queue->data[queue->front];
		printf("[+] index: %d data:%d 出队成功...\n", queue->front, *x);
		queue->front = (queue->front + 1) % MAXSIZE;
		return 0;
	}
}

int freeQueue(CircleQueue * queue)
{
	printf("[+] 释放队列...\n");
	free(queue);
	return 0;
}

void showQueue(CircleQueue * queue)
{
	int index = 0;
	int i = 0;
	if(isEmpty(queue))
	{
		printf("[!] 队列为空...不能输出...\n");
	}
	else
	{
		for (; i < queue->rear; i++)
		{
			printf("[+] index: %d data: %d\n", queue->front + i, queue->data[queue->front + i]);
		}
	}
}