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
	char stuNo[10];  //ѧ��
	char name[20];  //����
	int  age;       //����
	float math;     //��ѧ
	float English;  //Ӣ��
	float physics;  //����

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
		printf("[!] ͷ��㽨��ʧ��...���˳�����...");
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
	pHead = pHead->next;//����ͷ���
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
			system("cls");//����
			printf("[*] ���������ҳ...\n");
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
    printf("[*] �ɹ��ͷ�����...���˳�����...;\n");
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
	printf("��Ҫɾ���ڼ�����㣿\n");
	scanf("%d", &n);
	if(n <=0 || n > getLength(pHead))
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
	printf("[+] ���ڲ���ѧ����¼...\n");
	studentRecord * pNew = (studentRecord *)malloc(sizeof(studentRecord));
	while(pHead->next)
    {
        pHead = pHead->next;
    }
	initData(pNew);
	printf("[+] ������name:");
	scanf("%s", pNew->name);
	printf("[+] ������id:");
	scanf("%s", pNew->stuNo);
	printf("[+] ������age:");
	scanf("%d", &pNew->age);
	printf("[+] ������English�ɼ�:");
	scanf("%f", &pNew->English);
	printf("[+] ������math�ɼ�:");
	scanf("%f", &pNew->math);
	printf("[+] ������physics�ɼ�:");
	scanf("%f", &pNew->physics);
	pHead->next = pNew;
}

void showMenu()
{
	system("cls");//����
	printf("======ͬѧ¼������Ϣϵͳ======\n");
	printf("\t1.����ѧ����¼\n");
	printf("\t2.�޸�ѧ����¼\n");
	printf("\t3.ɾ��ѧ����¼\n");
	printf("\t4.�Ǽ�/�޸ĳɼ�\n");
	printf("\t5.���ѧ����¼\n");
	printf("\t6.�鿴�ܳɼ�\n");
	printf("\t7.�鿴�ɼ���\n");
	printf("\t0.�˳�ϵͳ\n");
	printf("==========================\n.");
	printf("���������ѡ��(0-7)��\n");
}

void doChoice(int choice, studentRecord * pHead)
{
	system("cls");//����
	printf("���ڴ�����%d��ѡ��\n", choice);
	if(choice < 0 || choice > 7)
	{
		printf("[!] �������...������ѡ��...\n");
		printf("[+] �����������...\n");
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
	printf("�����������...\n");
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
		printf("[!] ���ݿ���������...�����Զ������ʼ��ѧ������ϵͳ...\n�밴���������...\n");
		autoRandomInit(pHead);
		system("pause > nul");
		return 1;
	}
	else
	{
		printf("[+] ���ڴ����ݿ��ж�ȡ����...\n");
		while (!feof(fp))
		{
			if((pNew = (studentRecord *)malloc(sizeof(studentRecord))) == NULL)
			{
				printf("ϵͳ�ڴ���ϣ����˳�����");
				exit(0);
			}
			if(fread(pNew, sizeof(studentRecord), 1, fp))
			{
				pHead->next = pNew;
				pHead = pNew;
				count++;
				printf("[+] ���ڶ�ȡ��%d������...\n", count);
			}
		}
		printf("[+] %d������ȫ�����뵽�ڴ�...\n", count);
		printf("[+]�밴���������...\n");
		system("pause > nul");
		return 0;
	}
}

void save(studentRecord * pHead)
{
	FILE * fp;
	pHead = pHead->next;//����ͷ���
	fp = fopen("txl.txt", "wb");
	if (fp == NULL)
	{
		printf("���ܴ�txl.txt...���˳�����...\n");
		exit(0);
	}
	while(pHead)
	{
		if(fwrite(pHead, sizeof(studentRecord), 1, fp) == 1)
		{
			pHead = pHead->next;
		}
	}
	printf("[+]������...\n");
	fclose(fp);
}

void doUpdata(studentRecord * pHead)
{
	char name[100];
	pHead = pHead->next;//����ͷ���
	int isFound = 0;
	
	printf("[+] �����޸�ģ��...\n");
	printf("[*] ������Ҫ�޸ĵ�ͬѧ����: ");
	scanf("%s", name);
	getchar();

	while(pHead)
	{
		if(!strcmp(name,pHead->name))
		{
			isFound = 1;
			printf("[+] ͬѧ��Ϣ����:\n");
			printf("name : %s ", pHead->name);
			printf("id : %s ", pHead->stuNo);
			printf("age : %d ", pHead->age);
			printf("English : %f ", pHead->age);
			printf("Math : %f ", pHead->math);
			printf("Physics : %f\n", pHead->physics);
			printf("[-] ���޸�...\n");
			printf("[-] ���޸�name:");
			gets(pHead->name);
			printf("[-] ���޸�id:");
			gets(pHead->stuNo);
			printf("[-] ���޸�age:");
			scanf("%d", &pHead->age);
			printf("[-] ���޸�English�ɼ�:");
			scanf("%f", &pHead->English);
			printf("[-] ���޸�math�ɼ�:");
			scanf("%f", &pHead->math);
			printf("[-] ���޸�physics�ɼ�:");
			scanf("%f", &pHead->physics);
		}
		pHead = pHead->next;
	}

	if (!isFound)
	{
		printf("��Ǹ������Ϊ%s��ͬѧ��û����ͬѧ¼��.\n", name);
	}
	else
	{
		printf("����Ϊ%s��ͬѧ����Ϣ�Ѿ��ɹ��޸ģ�\n", name);
	}
}

int doAddup(studentRecord * pHead)
{
	printf("[+] ����ͳ�Ƴɼ�...\n");
	int i = 0;
	int item = 0;
	pHead = pHead->next;//����ͷ���
    while(pHead)
    {
		Stu[i].record = *pHead;
		Stu[i].total = Stu[i].record.English + Stu[i].record.math + Stu[i].record.physics;
		printf("[+]  name: %-10s total = %-5.2f + %-5.2f + %-5.2f = %-5.2f\n", Stu[i].record.name, Stu[i].record.English, Stu[i].record.math, Stu[i].record.physics, Stu[i].total);
        pHead = pHead->next;
		i++;
    }
	printf("[+] �ɼ�ͳ�����...\n");
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
	printf("[+] ���������ʼ��ѧ����Ϣ...\n");
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
    printf("[+] �Զ������ʼ�����...\n");
}

void showScoreTable(int len)
{
	printf("[+] �ɼ����鿴ģ��...\n");
	int i = 0;
    while(i < len)
    {
		printf("[+]  name: %-10s total = %-5.2f\n", Stu[i].record.name, Stu[i].total);
		i++;
    }
}