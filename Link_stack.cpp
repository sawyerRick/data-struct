#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
typedef struct stack
{
	elemtype data;
	stack * next;
}LinkStack;

LinkStack * initStack();//头结点为空(方便头插)
int isEmpty(LinkStack * top);
int pushStack(LinkStack * top, elemtype x);
int popStack(LinkStack ** top, elemtype * xPtr);
int getLength(LinkStack * top);
int freeStack(LinkStack * top);
void showStack(LinkStack * top);

int main()
{
	int i = 0;
	elemtype x;
	LinkStack * top;
	top = initStack();
	getLength(top);
	isEmpty(top);
	for (;i < 5; i++)
	{
		pushStack(top, i);
	}
	isEmpty(top);
	i = 0;
	showStack(top);
	getLength(top);
	for (;i < 3; i++)
	{
		popStack(&top, &x);
	}
	freeStack(top);

	return 0;
}

LinkStack * initStack()
{
	LinkStack * top = (LinkStack * )malloc(sizeof(LinkStack));
	if(top != NULL)
	{
		top->data = 0;
		top->next = NULL;
		return top;
	}
	else
	{
		printf("[-]内存分配失败...已退出程序...\n");
		return 0;
	}
}

int isEmpty(LinkStack * top)
{
	if(top->next == NULL)
	{
		printf("[-] 栈为空..\n");
		return 1;
	}
	else
	{
		printf("[+] 栈不为空..\n");
		return 0;
	}
}

int pushStack(LinkStack * top, elemtype x)
{
	LinkStack * node = (LinkStack *)malloc(sizeof(LinkStack));
	if (node != NULL)
	{
		//头插法
		node->data = x;
		node->next = top->next;
		top->next = node;
		printf("[+] data:%d 入栈成功...\n", x);
		return 0;
	}
	printf("[-] data:%d 入栈失败...\n", x);
	return 1;
}

int popStack(LinkStack ** top, elemtype * xPtr)
{
	LinkStack * stackPtr = (*top)->next;
	if(stackPtr != NULL)
	{
		*xPtr = (*top)->next->data;
		(*top)->next = (*top)->next->next;
		free(stackPtr);
		printf("[+] data:%d 出栈成功...\n", *xPtr);
		return 0;
	}
	printf("[-] data:%d 出栈失败...\n", *xPtr);
	return 1;
}

int getLength(LinkStack * top)
{
	int len = 0;
	LinkStack * node = top->next;
	for(;node != NULL; len++)
	{
		node = node->next;
	}
	printf("[*] 链栈长度:%d\n", len);
	return len;
}

void showStack(LinkStack * top)
{
	printf("[+] 输出全栈...\n");
	LinkStack * node = top->next;
	int index = 0;
	while(node != NULL)
	{
		printf("[*] index:%d  data:%d\n", index, node->data);
		node = node->next;
		index++;
	}
}

int freeStack(LinkStack * top)
{
	LinkStack * node = top->next;
	while(node != NULL)
	{
		printf("[-] Deleting:data:%d...\n",node->data);
		top = node->next;
		free(node);
		node = top;
	}
	return 1;
}