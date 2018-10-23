#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INSERT 1
#define UPDATE 2
#define DELETE 3
#define UPDATES 4
#define LIST 5
#define ADDUP 6
#define LISTTABLE 7
#define MAXSIZE 1000
#define QUIT 0

typedef struct student
{
	char stuNo[10];  //学号
	char name[20];  //姓名
	int  age;       //年龄
	float math;     //数学
	float English;  //英语
	float physics;  //物理

	struct student * next;
}studentRecord;

struct
{
	studentRecord record;
	float total;
}Stu[MAXSIZE];

studentRecord * createHead();
void doListAll(studentRecord * pHead);
void doFree(studentRecord * pHead);
void doDelete(studentRecord * pHead);
void doInsert(studentRecord * pHead);
void doUpdata(studentRecord * pHead);
void doChoice(int choice, studentRecord * pHead);
void showMenu();
void save(studentRecord * pHead);
void initData(studentRecord * pHead);
void autoRandomInit(studentRecord * pHead);
void showScoreTable(int len);
void bubleSort();
void selectSort();
void insertSort();
int doAddup(studentRecord * pHead);
int getLength(studentRecord * pHead);
int isEmpty(studentRecord * pHead);
int getChoice();
int init(studentRecord * pHead);

int main()
{
	int choice;
    studentRecord * pHead = createHead();
	init(pHead);
	while (1)
	{
		showMenu();
		choice = getChoice();
		doChoice(choice, pHead);
		system("pause > nul");
	}

    return 0;
}

studentRecord * createHead()
{
    studentRecord * pHead = (studentRecord *)malloc(sizeof(studentRecord));
	if(pHead == NULL)
	{
		printf("[!] 头结点建立失败...已退出程序...");
		exit(0);
	}
	else
	{
		pHead->next = NULL;
		return pHead;
	}
}

void doListAll(studentRecord * pHead)
{
	pHead = pHead->next;//跳过头结点
	int item = 0;
    while(pHead)
    {
		item++;
        printf("name : %-10s  ", pHead->name);
		printf("id : %-10s  ", pHead->stuNo);
		printf("age : %-5d  ", pHead->age);
		printf("English : %-5.2f  ", pHead->English);
		printf("Math : %-5.2f  ", pHead->math);
		printf("Physics : %-5.2f\n", pHead->physics);
        pHead = pHead->next;
		if(item % 10 == 0)
		{
			system("pause");
			system("cls");//清屏
			printf("[*] 按任意键翻页...\n");
		}
    }
    printf("\n");
}

void doFree(studentRecord * pHead)
{
    studentRecord * pTail = NULL;
    while(pHead)
    {
        pTail = pHead;
        pHead = pHead->next;
        free(pTail);
    }
    printf("[*] 成功释放链表...已退出程序...;\n");
	exit(0);
}

int isEmpty(studentRecord * pHead)
{
    if(pHead)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void doDelete(studentRecord * pHead)
{
    studentRecord * prior = pHead;
    studentRecord * pMove = pHead;
	int n;
    int i = 1;
	printf("需要删除第几个结点？\n");
	scanf("%d", &n);
	if(n <=0 || n > getLength(pHead))
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

int getLength(studentRecord * pHead)
{
    int i = 0;
    while(pHead->next)
    {
        pHead = pHead->next;
        i++;
    }
	return i;
}

void doInsert(studentRecord * pHead)
{
	printf("[+] 正在插入学生记录...\n");
	studentRecord * pNew = (studentRecord *)malloc(sizeof(studentRecord));
	while(pHead->next)
    {
        pHead = pHead->next;
    }
	initData(pNew);
	printf("[+] 请输入name:");
	scanf("%s", pNew->name);
	printf("[+] 请输入id:");
	scanf("%s", pNew->stuNo);
	printf("[+] 请输入age:");
	scanf("%d", &pNew->age);
	printf("[+] 请输入English成绩:");
	scanf("%f", &pNew->English);
	printf("[+] 请输入math成绩:");
	scanf("%f", &pNew->math);
	printf("[+] 请输入physics成绩:");
	scanf("%f", &pNew->physics);
	pHead->next = pNew;
}

void showMenu()
{
	system("cls");//清屏
	printf("======同学录管理信息系统======\n");
	printf("\t1.插入学生记录\n");
	printf("\t2.修改学生记录\n");
	printf("\t3.删除学生记录\n");
	printf("\t4.登记/修改成绩\n");
	printf("\t5.浏览学生记录\n");
	printf("\t6.查看总成绩\n");
	printf("\t7.查看成绩表\n");
	printf("\t0.退出系统\n");
	printf("==========================\n.");
	printf("请输入你的选择(0-7)：\n");
}

void doChoice(int choice, studentRecord * pHead)
{
	system("cls");//清屏
	printf("正在处理第%d个选择！\n", choice);
	if(choice < 0 || choice > 7)
	{
		printf("[!] 输入错误...请重新选择...\n");
		printf("[+] 按任意键继续...\n");
		return;
	}
	switch (choice)
	{
	case INSERT:
		doInsert(pHead);
		save(pHead);
		break;
	case UPDATE:
		doUpdata(pHead);
		save(pHead);
		break;
	case DELETE:
		doDelete(pHead);
		save(pHead);
		break;
	case UPDATES:
		break;
	case LIST:
		doListAll(pHead);
		break;
	case ADDUP:
		doAddup(pHead);
		break;
	case LISTTABLE:
		showScoreTable(doAddup(pHead));
		break;
	case QUIT:
		doFree(pHead);
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

int init(studentRecord * pHead)
{
	FILE * fp = fopen("txl.txt", "rb");
	studentRecord * pNew = NULL;
	int count = 0;
	if(fp == NULL)
	{
		printf("[!] 数据库暂无数据...正在自动随机初始化学生管理系统...\n请按任意键继续...\n");
		autoRandomInit(pHead);
		system("pause > nul");
		return 1;
	}
	else
	{
		printf("[+] 正在从数据库中读取数据...\n");
		while (!feof(fp))
		{
			if((pNew = (studentRecord *)malloc(sizeof(studentRecord))) == NULL)
			{
				printf("系统内存故障，已退出程序");
				exit(0);
			}
			if(fread(pNew, sizeof(studentRecord), 1, fp))
			{
				pHead->next = pNew;
				pHead = pNew;
				count++;
				printf("[+] 正在读取第%d条数据...\n", count);
			}
		}
		printf("[+] %d条数据全部载入到内存...\n", count);
		printf("[+]请按任意键继续...\n");
		system("pause > nul");
		return 0;
	}
}

void save(studentRecord * pHead)
{
	FILE * fp;
	pHead = pHead->next;//跳过头结点
	fp = fopen("txl.txt", "wb");
	if (fp == NULL)
	{
		printf("不能打开txl.txt...已退出程序...\n");
		exit(0);
	}
	while(pHead)
	{
		if(fwrite(pHead, sizeof(studentRecord), 1, fp) == 1)
		{
			pHead = pHead->next;
		}
	}
	printf("[+]保存中...\n");
	fclose(fp);
}

void doUpdata(studentRecord * pHead)
{
	char name[100];
	pHead = pHead->next;//跳过头结点
	int isFound = 0;
	
	printf("[+] 数据修改模块...\n");
	printf("[*] 请输入要修改的同学姓名: ");
	scanf("%s", name);
	getchar();

	while(pHead)
	{
		if(!strcmp(name,pHead->name))
		{
			isFound = 1;
			printf("[+] 同学信息如下:\n");
			printf("name : %s ", pHead->name);
			printf("id : %s ", pHead->stuNo);
			printf("age : %d ", pHead->age);
			printf("English : %f ", pHead->age);
			printf("Math : %f ", pHead->math);
			printf("Physics : %f\n", pHead->physics);
			printf("[-] 请修改...\n");
			printf("[-] 请修改name:");
			gets(pHead->name);
			printf("[-] 请修改id:");
			gets(pHead->stuNo);
			printf("[-] 请修改age:");
			scanf("%d", &pHead->age);
			printf("[-] 请修改English成绩:");
			scanf("%f", &pHead->English);
			printf("[-] 请修改math成绩:");
			scanf("%f", &pHead->math);
			printf("[-] 请修改physics成绩:");
			scanf("%f", &pHead->physics);
		}
		pHead = pHead->next;
	}

	if (!isFound)
	{
		printf("抱歉，姓名为%s的同学还没登入同学录中.\n", name);
	}
	else
	{
		printf("姓名为%s的同学的信息已经成功修改！\n", name);
	}
}

int doAddup(studentRecord * pHead)
{
	printf("[+] 正在统计成绩...\n");
	int i = 0;
	int item = 0;
	pHead = pHead->next;//跳过头结点
    while(pHead)
    {
		Stu[i].record = *pHead;
		Stu[i].total = Stu[i].record.English + Stu[i].record.math + Stu[i].record.physics;
		printf("[+]  name: %-10s total = %-5.2f + %-5.2f + %-5.2f = %-5.2f\n", Stu[i].record.name, Stu[i].record.English, Stu[i].record.math, Stu[i].record.physics, Stu[i].total);
        pHead = pHead->next;
		i++;
    }
	printf("[+] 成绩统计完成...\n");
	return i;
}

void initData(studentRecord * pHead)
{
	pHead->age = 0;
	pHead->English = 0;
	pHead->physics = 0;
	pHead->math = 0;
	strcpy(pHead->name,"nobody");
	strcpy(pHead->stuNo, "00000");
	pHead->next = NULL;
}

void autoRandomInit(studentRecord * pHead)
{
	int i = 0;
	int j = -1;
	char names[][10] = {"Wright", "Jackson", "White", "Harris", "Martin", "Thompson", "Clark", "Lee", "Green", "Turner"};
    studentRecord * pNew = NULL;
	printf("[+] 正在随机初始化学生信息...\n");
    while(i < 8)
    {
        pNew = (studentRecord *)malloc(sizeof(studentRecord));
		initData(pNew);
		pNew->age = rand() % 100;
		pNew->English = rand() % 150;
		pNew->physics = rand() % 60;
		pNew->math = rand() % 150;
		pNew->stuNo[0] = char(i + 48);
		pNew->stuNo[1] = '\0';
		j = -1;
		do
		{
			j++;
			pNew->name[j] = names[i][j];
		}while(names[i][j] != '\0');

		pHead->next = pNew;
		pHead = pNew;
        i++;
    }
    printf("[+] 自动随机初始化完成...\n");
}

void showScoreTable(int len)
{
	printf("[+] 成绩表查看模块...\n");
	int i = 0;
    while(i < len)
    {
		printf("[+]  name: %-10s total = %-5.2f\n", Stu[i].record.name, Stu[i].total);
		i++;
    }
}
