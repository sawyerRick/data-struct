#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSERT 1
#define DTQUERY 2
#define NQUERY 3
#define DELETE 4
#define LIST 5
#define SORT 6
#define IFNULL 7
#define GETLEN 8
#define maxnum 100
#define MaxSize 100
#define QUIT 0

typedef char ElemType;
typedef struct link
{
    int id;
	ElemType data[MaxSize];
    struct link * next;
}Link;

void createLink(Link ** pHead);
void showLink(Link * pHead);
void sort(Link * pHead);
void freeLink(Link * pHead);
void deleteLink(Link ** pHead);
void insert(Link * pHead);
int length(Link * pHead);
void query_n(Link * pHead);
void query_by_data(Link * pHead);
void if_empty(Link * pHead);
void doChoice(int choice, Link * pHead);
void showMenu();
int getChoice();

int main()
{
	int choice;
    Link * pHead = NULL;
    createLink(&pHead);
	while (1)
	{
		showMenu();
		choice = getChoice();
		doChoice(choice, pHead);
		system("pause > nul");
	}

    return 0;
}

void createLink(Link ** pHead)
{
    int i = 0;
	int length = 0;
    Link * pNow = NULL;
    Link * pTtail = NULL;
	printf("正在创建链表...\n");
	printf("请输入链表长度:");
	scanf("%d", &length);
    while(i < length)
    {
        if(i == 0)
        {
            pTtail = *pHead = pNow = (Link *)malloc(sizeof(Link));
            pNow->id = 0;
        }
        pNow = (Link *)malloc(sizeof(Link));
		printf("请输入结点%d的id:\n", i + 1);
        scanf("%d", &pNow->id);
		getchar();
		printf("请输入结点%d的data:\n", i + 1);
        gets(pNow->data);
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
        printf("id : %d\n", pHead->id);
		printf("data : %s\n", pHead->data);
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
	exit(0);
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
        while(pre->next && pre->next->id < pNow->id)
        {
            pre = pre->next;
        }
        pNow->next = pre->next;
        pre->next = pNow;
        pNow = pTail;
    }
	showLink(pHead->next);
}

void if_empty(Link * pHead)
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

void query_n(Link * pHead)
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
            printf("第%d个元素:\n", i);
			printf("id : %d\n", pHead->id);
			printf("data : %s\n", pHead->data);
        }
        pHead = pHead->next;
    }
}

void deleteLink(Link * pHead)
{
    Link * prior = pHead;
    Link * pMove = pHead;
	int n;
    int i = 1;
	printf("需要删除第几个结点？\n");
	scanf("%d", &n);
	if(n <=0 || n > length(pHead))
	{
		printf("输入错误..");
		return;
	}
    while(pHead)
    {
        pMove = pMove->next;
        if(n == 1)
        {
            prior = pHead->next;
			pHead->next = pHead->next->next;
            free(prior);
            printf("已删除第%d个元素\n", i);
			system("pause > nul");
			system("cls");//清屏
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
    printf("链表长度为:%d\n", i);
	return i;
}

void insert(Link * pHead)
{
	Link * pNow = (Link *)malloc(sizeof(Link));
	while(pHead->next)
    {
        pHead = pHead->next;
    }
	pHead->next = pNow;
	printf("请输入id:\n");
	scanf("%d", &pNow->id);
	getchar();
	printf("请输入data:\n");
	gets(pNow->data);
	pNow->next = NULL;
}

void query_by_data(Link * pHead)
{
	char data[100];
	int n = 0;
    int i = 0;
    printf("输入data:\n");
	getchar();
    gets(data);
	printf("正在按data查找...\n");
    while(pHead)
    {
        i++;
        if(strcmp(data, pHead->data) == 0)
        {
            printf("第%d个元素:\n", i);
			printf("id : %d\n", pHead->id);
			printf("data : %s\n", pHead->data);
			return;
        }
        pHead = pHead->next;
    }
	printf("未找到data:%s...\n", data);
}

void showMenu()
{
	system("cls");//清屏
	printf("====链表管理系统====\n");
	printf("\t1.增加(尾插)\n");
	printf("\t2.按data查询\n");
	printf("\t3.查询第n个结点\n");
	printf("\t4.删除第n个结点\n");
	printf("\t5.列出整个链表\n");
	printf("\t6.按编号id排序\n");
	printf("\t7.链表是否为空\n");
	printf("\t8.获得链表长度\n");
	printf("\t0.释放链表并退出系统\n");
	printf("==========================\n.");
	printf("请输入你的选择(0/8)：\n");
}

void doChoice(int choice, Link * pHead)
{
	printf("正在处理第%d个选择！\n", choice);
	if(choice <0 || choice > 8)
	{
		printf("输入错误..\n");
	}
	switch (choice)
	{
	case INSERT:
		insert(pHead);
		break;
	case DTQUERY:
		query_by_data(pHead->next);
		break;
	case NQUERY:
		query_n(pHead->next);
		break;
	case DELETE:
		deleteLink(pHead);
		break;
	case LIST:
		showLink(pHead->next);
		break;
	case SORT:
		sort(pHead);
		break;
	case IFNULL:
		if_empty(pHead);
		break;
	case GETLEN:
		length(pHead);
		break;
	case QUIT:
		freeLink(pHead);
		break;
	}
	printf("按任意键继续...\n");
}

int getChoice()
{
	int choice;
	scanf("%d", &choice);
	return choice;
}