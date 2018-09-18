#include <stdio.h>
#include <stdlib.h>

typedef struct link
{
	int data;
	struct link * next;
}Link;

void createLink(Link ** pHead, int n);
void showLink(Link * pHead);
void sort(Link * pHead);
void freeLink(Link * pHead);
void delete(Link ** pHead, int n);
void insert(Link * pHead, int n);
int length(Link * pHead);
void display_n(Link * pHead);
int find(Link * pHead, char * elem);
void is_NULL(Link * pHead);

int main()
{
	Link * pHead = NULL;
	createLink(&pHead, 5);
	is_NULL(pHead);
	showLink(pHead->next);
	display_n(pHead->next);
	printf("链表长度为:%d\n", length(pHead));
	delete(&pHead, 2);
	showLink(pHead->next);
	printf("链表长度为:%d\n", length(pHead));
	// sort(pHead);
	freeLink(pHead);

	return 0;
}

void createLink(Link ** pHead, int n)
{
	int i = 0;
	Link * pNow = NULL;
	Link * pTtail = NULL;
	printf("正在创建链表...\n");
	while(i < n)
	{
		if(i == 0)
		{
			pTtail = *pHead = pNow = (Link *)malloc(sizeof(Link));
			pNow->data = 0;
		}
		pNow = (Link *)malloc(sizeof(Link));
		printf("data%d:\n", i + 1);
		scanf("%d", &pNow->data);
		pTtail->next = pNow;
		pTtail = pNow;
		pNow->next = NULL;
		i++;
	}
	printf("链表创建完成...\n");
}

void showLink(Link * pHead)
{
	while(pHead)
	{
		printf("%d", pHead->data);
		pHead = pHead->next;
	}
	printf("\n");
}

void freeLink(Link * pHead)
{
	Link * pTail = NULL;
	while(pHead)
	{
		pTail = pHead;
		pHead = pHead->next;
		free(pTail);
	}
	printf("Link has been free;\n");
}

void sort(Link * pHead)
{
	Link * pre, * pNow, * pTail;
	pre = pHead;
	pNow = pHead->next->next;
	pHead->next->next = NULL;
	while(pNow)
	{
		pTail = pNow->next;
		pre = pHead;
		while(pre->next && pre->next->data < pNow->data)
		{
			pre = pre->next;
		}
		pNow->next = pre->next;
		pre->next = pNow;
		pNow = pTail;
		showLink(pHead->next);
	}
}

void is_NULL(Link * pHead)
{
	if(pHead)
	{
		printf("顺序表不为空\n");
	}
	else
	{
		printf("顺序表为空\n");
	}
}

void display_n(Link * pHead)
{
	int n = 0;
	int i = 0;
	printf("需要查找第几位元素:\n");
	scanf("%d", &n);
	while(pHead)
	{
		i++;
		if(i == n)
		{
			printf("第%d个元素为:%d\n", i, pHead->data);
		}
		pHead = pHead->next;
	}
}

void delete(Link ** pHead, int n)
{
	Link * prior = *pHead;
	Link * pMove = *pHead;
	int i = 1;
	while(pHead)
	{
		pMove = pMove->next;
		if(n == 1)
		{
			*pHead = (*pHead)->next;
			free(prior);
			printf("已删除第%d个元素\n", i);
			return ;
		}
		else if(i == n)
		{
			prior->next = pMove->next;
			free(pMove);
			printf("已删除第%d个元素\n", i);
			return ;
		}
		prior = pMove;
		i++;
	}
}

int length(Link * pHead)
{
	int i = 0;
	while(pHead->next)
	{
		pHead = pHead->next;
		i++;
	}
	return i;
}

void insert(Link * pHead, int n)
{
	
}