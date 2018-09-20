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
		printf("内存分配失败..已退出程序...\n");
		exit(1);
	}

	ptr_L->length = 0;
	return ptr_L;
}

void get_length(SqList * ptr_L)
{
	printf("顺序表长:%d\n", ptr_L->length);
}

void insert(SqList * ptr_L)
{
	int n = 0;
	int data = 0;
	int i = 0;
	printf("请选择插入位置(目前表长:%d):\n", ptr_L->length);
	scanf("%d", &n);

	if (ptr_L->length >= 100)
	{
		printf("顺序表已满...操作失败\n");
		return ;
	}
	if (n < 1 || n > ptr_L->length + 1)
	{
		printf("操作位置非法...\n");
		return ;
	}

	printf("请输入插入data(int类型):\n");
	scanf("%d", &data);

	for(i = ptr_L->length + 1; i >= n; i--)
	{
		ptr_L->data[i] = ptr_L->data[i - 1];
	}
	ptr_L->data[i] = data;
	ptr_L->length++;
	printf("完成插入结点%d, data:%d...\n", i + 1, data);
}

void show_sql(SqList * ptr_L)
{
	if(ptr_L)
	{
		int i = 1;
		printf("顺序表有%d个结点...\n", ptr_L->length);
		for(; i <= ptr_L->length; i++)
		{
			printf("结点:%d ,data:%d", i, ptr_L->data[i-1]);
			printf("\n");
		}
		return;
	}
	printf("未初始化顺序表...\n");
}

void delete_sql(SqList * ptr_L)
{
	int n = 0;
	int i = 0;
	printf("请选择删除位置:\n");
	scanf("%d", &n);

	if (n < 1 || n > ptr_L->length)
	{
		printf("操作位置非法...\n");
		return ;
	}
	for(i = n;i <= ptr_L->length; i++)
	{
		ptr_L->data[i - 1] = ptr_L->data[i];
	}
	ptr_L->length--;
	printf("已删除结点%d...\n", n);
}

void get_node_n(SqList * ptr_L)
{
	int n = 0;
	int i = 0;
	printf("请选择结点位置:\n");
	scanf("%d", &n);

	if (n < 1 || n > ptr_L->length)
	{
		printf("操作位置非法...\n");
		return ;
	}
	printf("结点%d的data:%d\n", n, ptr_L->data[n-1]);
}

void search_data(SqList * ptr_L)
{
	int data = 0;
	int i = 1;
	printf("请输入需要查找的data(int类型):\n");
	scanf("%d", &data);

	for(; i <= ptr_L->length; i++)
	{
		if(data==ptr_L->data[i-1])
		{
			printf("data:%d在结点:%d\n", ptr_L->data[i-1], i);	
			return;
		}
	}
	printf("未找到data:%d\n", data);
}

void if_empty(SqList * ptr_L)
{
	if(ptr_L)
	{
		if(ptr_L->length)
		{
			printf("顺序表不为空...\n");
			return ;
		}
		printf("顺序表为空...\n");
		return ;
	}
	printf("未初始化顺序表...\n");
	return ;
}

void free_sqlist(SqList ** ptr_L)
{
	free(*ptr_L);
	*ptr_L = NULL;
	printf("已释放顺序表...\n");
	exit(0);
}

void showMenu()
{
	system("cls");//清屏
	printf("====顺序表管理系统====\n");
	printf("\t1.插入\n");
	printf("\t2.按data查询\n");
	printf("\t3.查询第n个结点\n");
	printf("\t4.删除第n个结点\n");
	printf("\t5.列出整个顺序表\n");
	printf("\t6.顺序表是否为空\n");
	printf("\t7.获得顺序表长度\n");
	printf("\t0.释放顺序表并退出系统\n");
	printf("==========================\n.");
	printf("请输入你的选择(0/7)：\n");
}

void doChoice(int choice, SqList * ptr_L)
{
	if(choice < 0 || choice > 7)
	{
		printf("输入错误..\n");
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
	printf("按任意键继续...\n");
}

int getChoice()
{
	int choice;
	scanf("%d", &choice);
	return choice;
}