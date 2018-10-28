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

struct table
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
void doUdScore(studentRecord * pHead);
void doChoice(int choice, studentRecord * pHead);
void showMenu();
void save(studentRecord * pHead);
void initData(studentRecord * pHead);
void autoRandomInit(studentRecord * pHead);
void showScoreTable(int len);
void sortMenu(int len);
void bubleSort(int len);
void selectSort(int len);
void insertSort(int len);
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
	if(pHead->next == NULL)
	{
		printf("[!] 尚无学生信息录入系统!!!\n");
		autoRandomInit(pHead);
		return;
	}

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
        if(i == n)
        {
            printf("[*] 正在删除第%d个学生信息...\n", i);
			printf("[-] 已删除学生:");
			printf("name : %-10s  ", pMove->name);
			printf("id : %-10s  ", pMove->stuNo);
			printf("age : %-5d  ", pMove->age);
			printf("English : %-5.2f  ", pMove->English);
			printf("Math : %-5.2f  ", pMove->math);
			printf("Physics : %-5.2f\n", pMove->physics);
			prior->next = pMove->next;
            free(pMove);
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
	printf("[+] 请输入name(string):");
	scanf("%s", pNew->name);
	printf("[+] 请输入id(string):");
	scanf("%s", pNew->stuNo);
	printf("[+] 请输入age(int):");
	scanf("%d", &pNew->age);
	printf("[+] 请输入English成绩(float):");
	scanf("%f", &pNew->English);
	printf("[+] 请输入math成绩(float):");
	scanf("%f", &pNew->math);
	printf("[+] 请输入physics成绩(float):");
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
		doUdScore(pHead);
		save(pHead);
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
		printf("[!] 数据库暂无数据...\n[!] 正在自动随机初始化学生管理系统...\n");
		autoRandomInit(pHead);
		printf("[!] 请按任意键继续...\n");
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
	FILE * fp = fopen("txl.txt", "wb");;
	pHead = pHead->next;//跳过头结点
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
			printf("name : %-10s  ", pHead->name);
			printf("id : %-10s  ", pHead->stuNo);
			printf("age : %-5d  ", pHead->age);
			printf("English : %-5.2f  ", pHead->English);
			printf("Math : %-5.2f  ", pHead->math);
			printf("Physics : %-5.2f\n", pHead->physics);
			printf("[-] 请修改...\n");
			printf("[-] 请修改name(string):");
			gets_s(pHead->name);
			printf("[-] 请修改id(string):");
			gets_s(pHead->stuNo);
			printf("[-] 请修改age(int):");
			scanf("%d", &pHead->age);
			printf("[-] 请修改English成绩(float):");
			scanf("%f", &pHead->English);
			printf("[-] 请修改math成绩(float):");
			scanf("%f", &pHead->math);
			printf("[-] 请修改physics成绩(float):");
			scanf("%f", &pHead->physics);
			printf("姓名为%s的同学的信息已经成功修改！\n", name);
			return;
		}
		pHead = pHead->next;
	}

	if (!isFound)
	{
		printf("抱歉，姓名为%s的同学还没登入同学录中.\n", name);
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
	printf("[!] 成绩统计完成...\n");
	return i;
}

void initData(studentRecord * pHead)
{
	pHead->age = 0;
	pHead->English = 0;
	pHead->physics = 0;
	pHead->math = 0;
	strcpy_s(pHead->name,"nobody");
	strcpy_s(pHead->stuNo, "00000");
	pHead->next = NULL;
}

void autoRandomInit(studentRecord * pHead)
{
	int i = 0;
	int j = -1;
	char names[][10] = {"Wright", "Jackson", "White", "Harris", "Martin", "Thompson", "Clark", "Lee", "Green", "Turner"};
    studentRecord * pNew = NULL;
	printf("[+] 正在随机初始化一批学生信息...\n");
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
	printf("[*] 成绩表查看模块...\n");
	sortMenu(len);
	int i = 0;
    while(i < len)
    {
		printf("name : %-10s  ", Stu[i].record.name);
		printf("total : %-5.2f  ", Stu[i].total);
		printf("id : %-10s  ", Stu[i].record.stuNo);
		printf("age : %-5d  ", Stu[i].record.age);
		printf("English : %-5.2f  ", Stu[i].record.English);
		printf("Math : %-5.2f  ", Stu[i].record.math);
		printf("Physics : %-5.2f\n", Stu[i].record.physics);
		i++;
    }
}

void doUdScore(studentRecord * pHead)
{
	char name[100];
	pHead = pHead->next;//跳过头结点
	int isFound = 0;

	printf("[+] 成绩修改模块...\n");
	printf("[*] 请输入要修改的同学姓名(string): ");
	scanf("%s", name);
	getchar();

	while (pHead)
	{
		if (!strcmp(name, pHead->name))
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
			printf("[-] 请修改English成绩(float):");
			scanf("%f", &pHead->English);
			printf("[-] 请修改math成绩(float):");
			scanf("%f", &pHead->math);
			printf("[-] 请修改physics成绩(float):");
			scanf("%f", &pHead->physics);
			printf("姓名为%s的同学的信息已经成功修改！\n", name);
			return;
		}
		pHead = pHead->next;
	}

	if (!isFound)
	{
		printf("抱歉，姓名为%s的同学还没登入同学录中.\n", name);
	}
}

void sortMenu(int len)
{
	int choice = 0;
	printf("======请选择排序方法======\n");
	printf("\t1.选择排序\n");
	printf("\t2.插入排序\n");
	printf("\t3.冒泡排序\n");
	printf("==========================\n");
	printf("[*] 请输入你的选择(1-3)：");
	do
	{
		scanf("%d", &choice);
		if(choice < 1 || choice > 3)
		{
			printf("[!] 输入错误...请重新输入(1-3):");
		}
	}while(choice < 1 || choice > 3);

	switch (choice)
	{
	case 1:
		selectSort(len);
		break;
	case 2:
		insertSort(len);
		break;
	case 3:
		bubleSort(len);
		break;
	}
}

void bubleSort(int len)
{
	int i, j, temp;
	studentRecord tempTable;
	char tempName[10];

	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < len - 1 - i; j++)
		{
			if (Stu[j].total < Stu[j + 1].total)
			{
				temp = Stu[j].total;
				tempTable = Stu[j].record;

				Stu[j].total = Stu[j + 1].total;
				Stu[j].record = Stu[j + 1].record;

				Stu[j + 1].total = temp;
				Stu[j + 1].record = tempTable;
			}
		}
	}
}

void selectSort(int len)
{
	int i, j, temp;
	studentRecord tempTable;
	char tempName[10];

	for (i = 0; i < len; i++)
	{
		for (j = i + 1; j < len; j++)
		{
			if (Stu[i].total < Stu[j].total)
			{
				temp = Stu[i].total;
				tempTable = Stu[i].record;

				Stu[i].total = Stu[j].total;
				Stu[i].record = Stu[j].record;

				Stu[j].total = temp;
				Stu[j].record = tempTable;
			}
		}
	}
}	

void insertSort(int len)
{
	int i, j, temp;
	studentRecord tempTable;

	for(i = 1; i < len; i++)
	{
		temp = Stu[i].total;
		tempTable = Stu[i].record;
		j = i - 1;
		while(j >= 0 && temp > Stu[j].total)
		{
			Stu[j + 1].total = Stu[j].total;
			Stu[j + 1].record = Stu[j].record;
			j--;
		}
		Stu[j + 1].total = temp;
		Stu[j + 1].record = tempTable;
	}
}
