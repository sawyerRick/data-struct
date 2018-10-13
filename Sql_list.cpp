#include <stdio.h>
#include <stdlib.h>

#define INSERT 1
#define DTQUERY 2
#define NQUERY 3
#define DELETE 4
#define LIST 5
#define IFNULL 6
#define GETLEN 7
#define QUIT 0
#define MaxSize 100
typedef int ElemType;

typedef struct
{
	ElemType data[MaxSize];
	int length;
}SqList;

SqList * init();
void get_length(SqList * ptr_L);
void insert(SqList * ptr_L);
void show_sql(SqList * ptr_L);
void delete_sql(SqList * ptr_L);
void get_node_n(SqList * ptr_L);
void search_data(SqList * ptr_L);
void if_empty(SqList * ptr_L);
void free_sqlist(SqList ** ptr_L);
void doChoice(int choice, SqList * ptr_L);
void showMenu();
int getChoice();


int main()
{
	int choice = 0;
	SqList * ptr_L = init();
	while (1)
	{
		showMenu();
		choice = getChoice();
		doChoice(choice, ptr_L);
		system("pause > nul");
	}

	return 0;
}

SqList * init()
{
	SqList * ptr_L;
	ptr_L = (SqList *)malloc(sizeof(SqList));

	if (ptr_L == NULL)
	{
		printf("�ڴ����ʧ��..���˳�����...\n");
		exit(1);
	}

	ptr_L->length = 0;
	return ptr_L;
}

void get_length(SqList * ptr_L)
{
	printf("˳���:%d\n", ptr_L->length);
}

void insert(SqList * ptr_L)
{
	int n = 0;
	int data = 0;
	int i = 0;
	printf("��ѡ�����λ��(Ŀǰ��:%d):\n", ptr_L->length);
	scanf("%d", &n);

	if (ptr_L->length >= 100)
	{
		printf("˳�������...����ʧ��\n");
		return ;
	}
	if (n < 1 || n > ptr_L->length + 1)
	{
		printf("����λ�÷Ƿ�...\n");
		return ;
	}

	printf("���������data(int����):\n");
	scanf("%d", &data);

	for(i = ptr_L->length + 1; i >= n; i--)
	{
		ptr_L->data[i] = ptr_L->data[i - 1];
	}
	ptr_L->data[i] = data;
	ptr_L->length++;
	printf("��ɲ�����%d, data:%d...\n", i + 1, data);
}

void show_sql(SqList * ptr_L)
{
	if(ptr_L)
	{
		int i = 1;
		printf("˳�����%d�����...\n", ptr_L->length);
		for(; i <= ptr_L->length; i++)
		{
			printf("���:%d ,data:%d", i, ptr_L->data[i-1]);
			printf("\n");
		}
		return;
	}
	printf("δ��ʼ��˳���...\n");
}

void delete_sql(SqList * ptr_L)
{
	int n = 0;
	int i = 0;
	printf("��ѡ��ɾ��λ��:\n");
	scanf("%d", &n);

	if (n < 1 || n > ptr_L->length)
	{
		printf("����λ�÷Ƿ�...\n");
		return ;
	}
	for(i = n;i <= ptr_L->length; i++)
	{
		ptr_L->data[i - 1] = ptr_L->data[i];
	}
	ptr_L->length--;
	printf("��ɾ�����%d...\n", n);
}

void get_node_n(SqList * ptr_L)
{
	int n = 0;
	int i = 0;
	printf("��ѡ����λ��:\n");
	scanf("%d", &n);

	if (n < 1 || n > ptr_L->length)
	{
		printf("����λ�÷Ƿ�...\n");
		return ;
	}
	printf("���%d��data:%d\n", n, ptr_L->data[n-1]);
}

void search_data(SqList * ptr_L)
{
	int data = 0;
	int i = 1;
	printf("��������Ҫ���ҵ�data(int����):\n");
	scanf("%d", &data);

	for(; i <= ptr_L->length; i++)
	{
		if(data==ptr_L->data[i-1])
		{
			printf("data:%d�ڽ��:%d\n", ptr_L->data[i-1], i);	
			return;
		}
	}
	printf("δ�ҵ�data:%d\n", data);
}

void if_empty(SqList * ptr_L)
{
	if(ptr_L)
	{
		if(ptr_L->length)
		{
			printf("˳���Ϊ��...\n");
			return ;
		}
		printf("˳���Ϊ��...\n");
		return ;
	}
	printf("δ��ʼ��˳���...\n");
	return ;
}

void free_sqlist(SqList ** ptr_L)
{
	free(*ptr_L);
	*ptr_L = NULL;
	printf("���ͷ�˳���...\n");
	exit(0);
}

void showMenu()
{
	system("cls");//����
	printf("====˳������ϵͳ====\n");
	printf("\t1.����\n");
	printf("\t2.��data��ѯ\n");
	printf("\t3.��ѯ��n�����\n");
	printf("\t4.ɾ����n�����\n");
	printf("\t5.�г�����˳���\n");
	printf("\t6.˳����Ƿ�Ϊ��\n");
	printf("\t7.���˳�����\n");
	printf("\t0.�ͷ�˳����˳�ϵͳ\n");
	printf("==========================\n.");
	printf("���������ѡ��(0/7)��\n");
}

void doChoice(int choice, SqList * ptr_L)
{
	if(choice < 0 || choice > 7)
	{
		printf("�������..\n");
	}
	switch (choice)
	{
	case INSERT:
		insert(ptr_L);
		break;
	case DTQUERY:
		search_data(ptr_L);
		break;
	case NQUERY:
		get_node_n(ptr_L);
		break;
	case DELETE:
		delete_sql(ptr_L);
		break;
	case LIST:
		show_sql(ptr_L);
		break;
	case IFNULL:
		if_empty(ptr_L);
		break;
	case GETLEN:
		get_length(ptr_L);
		break;
	case QUIT:
		free_sqlist(&ptr_L);
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