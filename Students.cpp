//第十一次迭代，只需要输入计算机的用户名，就可以桌面自动建立同学录文件并读取或储存数据
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSERT 1
#define QUERY 2
#define UPDATE 3
#define DELETE 4
#define LIST 5
#define QUIT 0
FILE * fp;

char fileNameBefore[100] = {"C:/Users/"};//文件前路径
char fileNameAfter[100] = {"/Desktop/txl.txt"};//文件后路径
char usersName[100];//用户名
char wholeName[100];//文件绝对路径

struct Node
{
	char name[100];
	char addr[100];
	char phone[100];
	char workfor[100];
	struct Node * pnext;
};

void showMenu();	//菜单模块
void init(struct Node ** pphead, struct Node ** pptail, int * ptr_last);		//读取文件模块
void doListAll(struct Node ** pphead, struct Node ** pptail, int * ptr_last);	//展示模块
void doInsert(struct Node ** pphead, struct Node ** pptail, int * ptr_last);	//插入模块
int getChoice();	//做出反应模块
void doDelete(struct Node ** pphead, struct Node ** pptail, int * ptr_last);	//删除模块
void doQuit();		//退出模块
void doQuery(struct Node ** pphead, struct Node ** pptail, int * ptr_last);		//查询模块
void doUpdate(struct Node ** pphead, struct Node ** pptail, int * ptr_last);	//修改模块
void doChoice(int choice, struct Node ** pphead, struct Node ** pptail, int * ptr_last);    //选择模块
void save(struct Node ** pphead, struct Node ** pptail, int * ptr_last);		//保存模块

int main()
{
	int choice;//用户功能选择1, 2, 3, 4
	int last = 0;
	struct Node * phead = NULL;//首节点
	struct Node * ptail = NULL;//永远指向最后一个节点
	int * ptr_last = NULL;//人数

	ptr_last = &last;
	init(&phead, &ptail, ptr_last);//读取文件

	while (1)
	{
		//1.显示主菜单
		showMenu();
		//2.获取用户功能选择
		choice = getChoice();
		//3.根据选择执行相应功能
		doChoice(choice, &phead, &ptail, ptr_last);

		//暂停
		system("pause > nul");
	}

	return 0;
}

void doInsert(struct Node ** pphead, struct Node ** pptail, int * ptr_last) //pphead ==> 结构指针phead的指针 *pphead ==>结构指针pHead
{
	struct Node * ptail = *pptail;//ptail用来代替*pptail移动，并赋值给*pptail
	struct Node * phead = *pphead;//phead用来代替*pphead移动，并赋值给*pphead
	struct Node * pnew = NULL;//获得新的分配内存
	
	if ((pnew = (struct Node *)malloc(sizeof(struct Node))) == NULL)
	{
		printf("系统内存已满， 不能再添加同学信息！");
		return;
	}
	pnew -> pnext = NULL;//把最后一个节点的尾巴弄空
	printf("处理增加......\n");
	printf("姓名: ");
	scanf("%s", pnew -> name);
	printf("地址: ");
	scanf("%s", pnew -> addr);
	printf("电话: ");
	scanf("%s", pnew -> phone);
	printf("单位: ");
	scanf("%s", pnew -> workfor);
	*ptr_last = *ptr_last + 1; //增加一个人
	printf("增加同学成功！\n");
	if (*pptail != NULL)
	{
		ptail -> pnext = pnew; //将该同学信息加入txl尾部
		ptail = ptail -> pnext;//ptail永远指向最后一个同学
		*pptail = ptail;
	}
	else
	{
		*pphead = *pptail = pnew; //第一个同学 
	}
	save(pphead, pptail, ptr_last);
}

int getChoice()
{
	int choice;
	scanf("%d", &choice);

	return choice;
}

void doChoice(int choice, struct Node ** pphead, struct Node ** pptail, int * ptr_last)
{
	printf("正在处理第%d个选择！\n", choice);

	switch (choice)
	{
	case DELETE:
		doDelete(pphead, pptail, ptr_last);
		break;
	case INSERT:
		doInsert(pphead, pptail, ptr_last);
		break;
	case LIST:
		doListAll(pphead, pptail, ptr_last);
		break;
	case QUIT:
		doQuit();
		break;
	case UPDATE:
		doUpdate(pphead, pptail, ptr_last);
		break;
	case QUERY:
		doQuery(pphead, pptail, ptr_last);
		break;
	}
}

void showMenu()
{
	system("cls");//清屏
	printf("====同学录管理信息系统====\n");
	printf("\t1.增加同学信息\n");
	printf("\t2.查询同学信息\n");
	printf("\t3.修改同学信息\n");
	printf("\t4.删除同学信息\n");
	printf("\t5.列出所有同学\n");
	printf("\t.0退出系统\n");
	printf("==========================\n.");
	printf("请输入你的选择(1/5)：\n");
}

void doListAll(struct Node ** pphead, struct Node ** pptail, int * ptr_last)
{
	int i = 0;
	struct Node * pmove = *pphead;
	printf("同学录中共有%d个同学的信息：\n", *ptr_last);

	while (i < *ptr_last)
	{
		printf("\n==========================\n");
		printf("姓名：%s\t", pmove -> name);
		printf("地址：%s\t", pmove -> addr);
		printf("电话：%s\t", pmove -> phone);
		printf("单位：%s\t", pmove -> workfor);
		pmove = pmove -> pnext;
		i++;
	}
	printf("\n==========================\n");
}

void doQuit()
{
	printf("\n欢迎下次使用本系统，再见！");
	exit(0);
}

void doDelete(struct Node ** pphead, struct Node ** pptail, int * ptr_last)
{
	char tname[100];
	int i;
	int find = 0;
	struct Node * p = *pphead;//临时工作指针
	struct Node * pre = *pphead;//临时工作指针,比p走得慢一步

	printf("处理删除......\n");
	printf("请输入同学姓名: ");
	scanf("%s", &tname);

	while ((p != NULL) && (!find))
	{
		if (!strcmp(tname, p -> name))
		{
			find = 1;
			break;
		}
		pre = p;
		p = p -> pnext;
	}
	if (!find)
	{
		printf("抱歉， 姓名为%s的同学还没登录同学录中。", tname);
	}
	else
	{
		//执行删除操作
		//删除第一个(只有一个)
		if (*ptr_last == 1)
		{
			*pphead = NULL;
			*ptr_last = *ptr_last - 1; //删除后last减去一个人
			printf("姓名为%s的同学信息已经成功删除！", tname);
		}
		//删除第一个(多人)
		else if (p == pre)
		{
			*pphead = pre -> pnext;
			*ptr_last = *ptr_last - 1; //删除后last减去一个人
			printf("姓名为%s的同学信息已经成功删除！", tname);
		}
		else
		{
			pre -> pnext = p -> pnext;
			*ptr_last = *ptr_last - 1; //删除后last减去一个人
			printf("姓名为%s的同学信息已经成功删除！", tname);
		}
		if (*ptr_last == 0)
		{
			*pptail = NULL;
			*pphead = NULL;
		}
	}
	save(pphead, pptail, ptr_last);
}

void doUpdate(struct Node ** pphead, struct Node ** pptail, int * ptr_last)
{
	int i;
	int find = 0;
	char tname[100];//临时存放输入姓名
	struct Node * p = *pphead;//把phead的值赋给p

	printf("处理修改......");
	printf("请输入要修改的同学姓名: ");
	scanf("%s", &tname);

	while ((p != NULL) && (!find))
	{
		if (!strcmp(tname, p -> name))
		{
			find = 1;
			printf("你找的同学信息如下：\n");
			printf("姓名: %s\t", p -> name);
			printf("请修改：\n");
			printf("姓名: ");
			scanf("%s", p -> name);
			printf("地址: ");
			scanf("%s", p -> addr);
			printf("电话: ");
			scanf("%s", p -> phone);
			printf("单位: ");
			scanf("%s", p -> workfor);
		}
		p = p -> pnext;
	}
	if (!find)
	{
		printf("抱歉，姓名为%s的同学还没登入同学录中。", tname);
	}
	else
	{
		printf("姓名为%s的同学的信息已经成功修改！", tname);
	}
	save(pphead, pptail, ptr_last);
}

void doQuery(struct Node ** pphead, struct Node ** pptail, int * ptr_last)
{
	int i;
	int find = 0;
	char tname[100];
	struct Node * p = *pphead;//*pphead ==> phead

	printf("处理查询......\n");
	printf("请输入同学姓名：");
	scanf("%s", tname);

	while ((p != NULL) && (!find))
	{
		if (!strcmp(tname, p -> name))
		{
			find = 1;
			printf("你找的同学信息如下：\n");
			printf("姓名: %s\t", p -> name);
			printf("地址: %s\t", p -> addr);
			printf("电话: %s\t", p -> phone);
			printf("单位: %s\t", p -> workfor);
		}
		p = p -> pnext;
	}
	if (!find)
	{
		printf("抱歉，姓名为%s的同学还没登入同学录中。", tname);
	}
}

void init(struct Node ** pphead, struct Node ** pptail, int * ptr_last)//读取文件操作
{
	int i = 0;
	struct Node * phead = NULL;//代替*pphead移动
	struct Node * ptail = NULL;
	struct Node * p = NULL;//临时工作指针

	//把文件的绝对路径连接起来
	printf("请输入计算机用户名:\n");
	gets(usersName);
	strcat(fileNameBefore, usersName);
	printf("%s\n", fileNameBefore);
	strcat(fileNameBefore, fileNameAfter);
	printf("%s\n", fileNameBefore);
	strcpy(wholeName, fileNameBefore);
	printf("%s\n", wholeName);

	fp = fopen(wholeName, "rb");
	if (fp == NULL)
	{
		fp = fopen(wholeName, "wb");//如果没有txl.dat文件就建立一个
		fclose(fp);//关闭
		fp = fopen(wholeName, "rb");//以rb形式打开
	}

	if (fp == NULL)
	{
		printf("不能打开同学录文件 txl.txt,请检查!");
		exit(0);
		*ptr_last = 0;//不存在数据文件， 同学录为空
	}
	else
	{
		while (!feof(fp))
		{
			if ((p = (struct Node *)malloc(sizeof(struct Node))) == NULL)
			{
				printf("系统内存故障，已退出程序");
				exit(0);
			}
			if (fread(p, sizeof(struct Node), 1, fp) == 1)
			{
				//第一名同学
				if (i == 0)
				{
					phead = ptail = p;
					*pphead = p;
				}
				ptail -> pnext = p; //next指向新内存
				ptail = p;		  //tail移向新内存
				*pptail = ptail;
				i++;
				*ptr_last = i;
			}
		}
		//做了修改，如果列表里没有同学，ptail的值为空 不能有以下运算
		if (*ptr_last)
		{
			ptail -> pnext = NULL;
		}
	}
	fclose(fp);
}

void save(struct Node ** pphead, struct Node ** pptail, int * ptr_last) //保存同学录到文件txl.dat中
{
	struct Node * p = *pphead;

	if ((fp = fopen(wholeName, "wb")) == NULL)
	{
		printf("不能打开同学录信息文件 txl.txt, 请检查!");
		exit(0);
	}

	while (p != NULL)
	{
		if (fwrite(p, sizeof(struct Node), 1, fp) == 1)
		{
			p = p -> pnext;
		}
	}
	fclose(fp);
}