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
	printf("���ڴ�������...\n");
	printf("������������:");
	scanf("%d", &length);
    while(i < length)
    {
        if(i == 0)
        {
            pTtail = *pHead = pNow = (Link *)malloc(sizeof(Link));
            pNow->id = 0;
        }
        pNow = (Link *)malloc(sizeof(Link));
		printf("��������%d��id:\n", i + 1);
        scanf("%d", &pNow->id);
		getchar();
		printf("��������%d��data:\n", i + 1);
        gets(pNow->data);
        pTtail->next = pNow;
        pTtail = pNow;
        pNow->next = NULL;
        i++;
    }
    printf("���������...\n");
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
        printf("˳���Ϊ��\n");
    }
    else
    {
        printf("˳���Ϊ��\n");
    }
}

void query_n(Link * pHead)
{
    int n = 0;
    int i = 0;
    printf("��Ҫ���ҵڼ�λԪ��:\n");
    scanf("%d", &n);
    while(pHead)
    {
        i++;
        if(i == n)
        {
            printf("��%d��Ԫ��:\n", i);
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
	printf("��Ҫɾ���ڼ�����㣿\n");
	scanf("%d", &n);
	if(n <=0 || n > length(pHead))
	{
		printf("�������..");
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
            printf("��ɾ����%d��Ԫ��\n", i);
			system("pause > nul");
			system("cls");//����
            return ;
        }
        else if(i == n)
        {
            prior->next = pMove->next;
            free(pMove);
            printf("��ɾ����%d��Ԫ��\n", i);
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
    printf("������Ϊ:%d\n", i);
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
	printf("������id:\n");
	scanf("%d", &pNow->id);
	getchar();
	printf("������data:\n");
	gets(pNow->data);
	pNow->next = NULL;
}

void query_by_data(Link * pHead)
{
	char data[100];
	int n = 0;
    int i = 0;
    printf("����data:\n");
	getchar();
    gets(data);
	printf("���ڰ�data����...\n");
    while(pHead)
    {
        i++;
        if(strcmp(data, pHead->data) == 0)
        {
            printf("��%d��Ԫ��:\n", i);
			printf("id : %d\n", pHead->id);
			printf("data : %s\n", pHead->data);
			return;
        }
        pHead = pHead->next;
    }
	printf("δ�ҵ�data:%s...\n", data);
}

void showMenu()
{
	system("cls");//����
	printf("====�������ϵͳ====\n");
	printf("\t1.����(β��)\n");
	printf("\t2.��data��ѯ\n");
	printf("\t3.��ѯ��n�����\n");
	printf("\t4.ɾ����n�����\n");
	printf("\t5.�г���������\n");
	printf("\t6.�����id����\n");
	printf("\t7.�����Ƿ�Ϊ��\n");
	printf("\t8.���������\n");
	printf("\t0.�ͷ������˳�ϵͳ\n");
	printf("==========================\n.");
	printf("���������ѡ��(0/8)��\n");
}

void doChoice(int choice, Link * pHead)
{
	printf("���ڴ����%d��ѡ��\n", choice);
	if(choice <0 || choice > 8)
	{
		printf("�������..\n");
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
	printf("�����������...\n");
}

int getChoice()
{
	int choice;
	scanf("%d", &choice);
	return choice;
}