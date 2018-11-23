//(����һ���ڴ�ռ��)(rearָ�����һ��ռ�)ѭ������CirQueue(��������)
//�����������͵Ķ���
//���ܷ��ַ���
#include <stdio.h>
#include <stdlib.h>

#define CirQueueMAXSIZE 1000
typedef int CirQueueElemtype;
typedef struct
{
	CirQueueElemtype data[CirQueueMAXSIZE];
	int front;
	int rear;
}CirQueue;

CirQueue * initQueue();
int isEmpty(CirQueue * queue);
int isFull(CirQueue * queue);
int getCirQueueLen(CirQueue * queue);
int enQueue(CirQueue * queue, CirQueueElemtype x);
int deQueue(CirQueue * queue, CirQueueElemtype * x);
int freeCirQueue(CirQueue * queue);
void printCirQueue(CirQueue * queue);

int main()
{
	int i = 0;
	CirQueueElemtype x = 0;
	CirQueue * queue = initQueue();
	enQueue(queue, 100);
	enQueue(queue, 99);
	printCirQueue(queue);
	deQueue(queue, &x);
	printCirQueue(queue);

	return 0;
}

CirQueue * initQueue()
{
	CirQueue * queue = (CirQueue *)malloc(sizeof(CirQueue));
	queue->rear = 0;
	queue->front = 0;

	return queue;
}

int isEmpty(CirQueue * queue)
{
	//�ж�ѭ������Ϊ��, ��ͷβ���
	if(queue->front == queue->rear)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isFull(CirQueue * queue)
{
	//�ж϶���Ϊ��
	if(queue->front == (queue->rear + 1) % CirQueueMAXSIZE)
	{
		return 1;
	}
	return 0;
}

int getCirQueueLen(CirQueue * queue)
{
	int len = (queue->rear - queue->front + CirQueueMAXSIZE) % CirQueueMAXSIZE;

	return len;
}

int enQueue(CirQueue * queue, CirQueueElemtype x)
{
	if(isFull(queue))
	{
		return 1;
	}
	else
	{
		queue->data[queue->rear] = x;
		queue->rear = (queue->rear + 1) % CirQueueMAXSIZE;
		return 0;
	}
}

int deQueue(CirQueue * queue, CirQueueElemtype * x)
{
	if(isEmpty(queue))
	{
		return 1;
	}
	else
	{
		*x = queue->data[queue->front];
		queue->front = (queue->front + 1) % CirQueueMAXSIZE;
		return 0;
	}
}

int freeCirQueue(CirQueue * queue)
{
	free(queue);

	return 0;
}

void printCirQueue(CirQueue * queue)
{
	int i = queue->front;
	printf("<CirQueue> max: %d front:%d rear:%d\n", CirQueueMAXSIZE, queue->front, queue->rear);
	if(isEmpty(queue))
	{
		printf("[!] ����Ϊ��...�������...\n");
	}
	else
	{
		for (; i < queue->rear; i++)
		{
			printf("%d\t", queue->data[i]);
		}
	}
	printf("\n");
}