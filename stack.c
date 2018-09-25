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
	printf("内存分配失败..已退出程序...\n");
	exit(1);
}

int stackEmpty(SequenStack * stack)
{
	if (stack->top == -1)
	{
		printf("栈为空..\n");
		return 1;
	}
	else
	{
		printf("栈不为空..\n");
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
	printf("栈长：%d", stack->top + 1);
	return stack->top + 1;
}

int pushStack(SequenStack * stack)
{
	int value = 0;
	if (stackFull(stack))
	{
		printf("栈溢出...压栈失败...\n");
		return 1;
	}
	printf("请输入需要入栈的值(int):\n");
	scanf("%d", &value);
	stack->top++;
	stack->data[stack->top] = value;
	printf("值%d成功入栈...top:%d...\n", value, stack->top-1);

	return 0;
}

int popStack(SequenStack * stack)
{
	if (stackEmpty(stack))
	{
		printf("栈为空...无法出栈...\n");
		return 1;
	}
	printf("top:%d出栈 值:%d\n", stack->top, stack->data[stack->top]);
	stack->top--;

	return 0;
}

void getStackPop(SequenStack * stack)
{
	if(stackEmpty(stack))
	{
		return ;
	}
	printf("栈顶值:%d  top: %d", stack->data[stack->top], stack->top);
}

void menu(SequenStack * stack)
{
	printf("=====================\n");
	printf("1.入栈\n");
	printf("2.出栈\n");
	printf("3.栈为空?\n");
	printf("4.取栈顶值\n");
	printf("5.取栈长度\n");
	printf("6.展示全栈\n");
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
		printf("栈为空..\n");
		return ;
	}
	for (; i <= stack->top; i++)
	{
		printf("top:%d  value:%d\n", i, stack->data[i]);
	}
}

