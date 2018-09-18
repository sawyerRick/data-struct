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

int main()
{
	Link * pHead = NULL;
	createLink(&pHead, 5);
	showLink(pHead->next);
	sort(pHead);
	freeLink(pHead);

	return 0;
}

void createLink(Link ** pHead, int n)
{
	int i = 0;
	Link * pNow = NULL;
	Link * pTtail = NULL;
	while(i < n)
	{
		//首链data为空，只用来储存地址
		if(i == 0)
		{
			pTtail = *pHead = pNow = (Link *)malloc(sizeof(Link));
			pNow->data = 0;
		}
		pNow = (Link *)malloc(sizeof(Link));
		printf("请输入data%d:\n", i + 1);
		scanf("%d", &pNow->data);
		pTtail->next = pNow;
		pTtail = pNow;
		pNow->next = NULL;
		i++;
	}
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
	//从第二个开始断开
	pHead->next->next = NULL;
	while(pNow)
	{
		pTail = pNow->next;//保存pNow的值
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