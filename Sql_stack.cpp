#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define PUSH 1
#define POP 2
#define EMPTY 3
#define GETPOP 4
#define LENGTH 5
#define SHOW 6
typedef int elemtype;
typedef struct 
{
	elemtype data[MAXSIZE];
	int top;
}SequenStack;

void initStack(SequenStack **stack);
int stackEmpty(SequenStack * stack);
int stackFull(SequenStack * stack);
int stackLength(SequenStack * stack);
int pushStack(SequenStack * stack);
int popStack(SequenStack * stack);
void getStackPop(SequenStack * stack);
void menu(SequenStack * stack);
void doChoice(int choice, SequenStack * stack);
void showStack(SequenStack * stack);

int main()
{
	SequenStack * stack = NULL;
	int choice = 0;
	initStack(&stack);
	while(1)
	{
		menu(stack);
		scanf("%d", &choice);
		doChoice(choice, stack);
		getchar();
	}


	return 0;
}

void initStack(SequenStack **stack)
{
	*stack = (SequenStack *)malloc(sizeof(SequenStack));
	if (stack)
	{
		(*stack)->top = -1;
		return ;
	}
	printf("�ڴ����ʧ��..���˳�����...\n");
	exit(1);
}

int stackEmpty(SequenStack * stack)
{
	if (stack->top == -1)
	{
		printf("ջΪ��..\n");
		return 1;
	}
	else
	{
		printf("ջ��Ϊ��..\n");
		return 0;
	}
}
int stackFull(SequenStack * stack)
{
	if(stack->top + 1 == MAXSIZE)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int stackLength(SequenStack * stack)
{
	printf("ջ����%d", stack->top + 1);
	return stack->top + 1;
}

int pushStack(SequenStack * stack)
{
	int value = 0;
	if (stackFull(stack))
	{
		printf("ջ���...ѹջʧ��...\n");
		return 1;
	}
	printf("��������Ҫ��ջ��ֵ(int):\n");
	scanf("%d", &value);
	stack->top++;
	stack->data[stack->top] = value;
	printf("ֵ%d�ɹ���ջ...top:%d...\n", value, stack->top-1);

	return 0;
}

int popStack(SequenStack * stack)
{
	if (stackEmpty(stack))
	{
		printf("ջΪ��...�޷���ջ...\n");
		return 1;
	}
	printf("top:%d��ջ ֵ:%d\n", stack->top, stack->data[stack->top]);
	stack->top--;

	return 0;
}

void getStackPop(SequenStack * stack)
{
	if(stackEmpty(stack))
	{
		return ;
	}
	printf("ջ��ֵ:%d  top: %d", stack->data[stack->top], stack->top);
}

void menu(SequenStack * stack)
{
	printf("=====================\n");
	printf("1.��ջ\n");
	printf("2.��ջ\n");
	printf("3.ջΪ��?\n");
	printf("4.ȡջ��ֵ\n");
	printf("5.ȡջ����\n");
	printf("6.չʾȫջ\n");
	printf("=====================\n");
}

void doChoice(int choice, SequenStack * stack)
{
	switch (choice)
	{
	case PUSH:
		pushStack(stack);
		break;
	case POP:
		popStack(stack);
		break;
	case EMPTY:
		stackEmpty(stack);
		break;
	case GETPOP:
		getStackPop(stack);
		break;
	case LENGTH:
		stackLength(stack);
		break;
	case SHOW:
		showStack(stack);
		break;
	}
}

void showStack(SequenStack * stack)
{
	int i = 0;
	if (stackEmpty(stack))
	{
		printf("ջΪ��..\n");
		return ;
	}
	for (; i <= stack->top; i++)
	{
		printf("top:%d  value:%d\n", i, stack->data[i]);
	}
}