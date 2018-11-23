#include <stdio.h>
#include <stdlib.h>

#define StackMAXSIZE 100
typedef int elemtype;
typedef struct 
{
	elemtype data[StackMAXSIZE];
	int top;
}SequenStack;

SequenStack * initStack();
int isEmpty(SequenStack * stack);
int isFull(SequenStack * stack);
int getLen(SequenStack * stack);
int push(SequenStack * stack, elemtype value);
int pop(SequenStack * stack);
elemtype getValueTop(SequenStack * stack);
int printStack(SequenStack * stack);

int main()
{
	SequenStack * stack = initStack();
	for (int i = 1; i <= 4; i++)
	{
		push(stack, i);
	}
	printStack(stack);
	pop(stack);
	printStack(stack);
	

	return 0;
}

SequenStack * initStack()
{
	SequenStack * stack = (SequenStack *)malloc(sizeof(SequenStack));
	//ջ����-1��ʼ����
	if (stack)
	{
		stack->top = -1;
		return stack;
	}
	printf("�ڴ����ʧ��..���˳�����...\n");
	exit(1);
}

int isEmpty(SequenStack * stack)
{
	if (stack->top == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isFull(SequenStack * stack)
{
	if(stack->top + 1 == StackMAXSIZE)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int getLen(SequenStack * stack)
{
	return stack->top + 1;
}

int push(SequenStack * stack, elemtype value)
{
	if (isFull(stack))
	{
		return -1;
	}
	//���ƶ�ջ���ٸ�ֵ
	stack->top++;
	stack->data[stack->top] = value;

	return 0;
}

int pop(SequenStack * stack)
{
	if (isEmpty(stack))
	{
		return -1;
	}
	//ȡֵ�ٳ�ջ
	elemtype value = stack->data[stack->top];
	stack->top--;

	return value;
}

elemtype getValueTop(SequenStack * stack)
{
	if(!isEmpty(stack))
	{
		return stack->data[stack->top];
	}
	else
	{
		return -1;
	}
}

int printStack(SequenStack * stack)
{
	if (isEmpty(stack))
	{
		return -1;
	}
	printf("Stack top is at index:%d\n", stack->top);
	for (int i = 0; i <= stack->top; i++)
	{
		printf("%d  ", stack->data[i]);
	}
	printf("\n");

	return 0;
}