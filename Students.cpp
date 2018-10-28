//��ʮһ�ε�����ֻ��Ҫ�����������û������Ϳ��������Զ�����ͬѧ¼�ļ�����ȡ�򴢴�����
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

char fileNameBefore[100] = {"C:/Users/"};//�ļ�ǰ·��
char fileNameAfter[100] = {"/Desktop/txl.txt"};//�ļ���·��
char usersName[100];//�û���
char wholeName[100];//�ļ�����·��

struct Node
{
	char name[100];
	char addr[100];
	char phone[100];
	char workfor[100];
	struct Node * pnext;
};

void showMenu();	//�˵�ģ��
void init(struct Node ** pphead, struct Node ** pptail, int * ptr_last);		//��ȡ�ļ�ģ��
void doListAll(struct Node ** pphead, struct Node ** pptail, int * ptr_last);	//չʾģ��
void doInsert(struct Node ** pphead, struct Node ** pptail, int * ptr_last);	//����ģ��
int getChoice();	//������Ӧģ��
void doDelete(struct Node ** pphead, struct Node ** pptail, int * ptr_last);	//ɾ��ģ��
void doQuit();		//�˳�ģ��
void doQuery(struct Node ** pphead, struct Node ** pptail, int * ptr_last);		//��ѯģ��
void doUpdate(struct Node ** pphead, struct Node ** pptail, int * ptr_last);	//�޸�ģ��
void doChoice(int choice, struct Node ** pphead, struct Node ** pptail, int * ptr_last);    //ѡ��ģ��
void save(struct Node ** pphead, struct Node ** pptail, int * ptr_last);		//����ģ��

int main()
{
	int choice;//�û�����ѡ��1, 2, 3, 4
	int last = 0;
	struct Node * phead = NULL;//�׽ڵ�
	struct Node * ptail = NULL;//��Զָ�����һ���ڵ�
	int * ptr_last = NULL;//����

	ptr_last = &last;
	init(&phead, &ptail, ptr_last);//��ȡ�ļ�

	while (1)
	{
		//1.��ʾ���˵�
		showMenu();
		//2.��ȡ�û�����ѡ��
		choice = getChoice();
		//3.����ѡ��ִ����Ӧ����
		doChoice(choice, &phead, &ptail, ptr_last);

		//��ͣ
		system("pause > nul");
	}

	return 0;
}

void doInsert(struct Node ** pphead, struct Node ** pptail, int * ptr_last) //pphead ==> �ṹָ��phead��ָ�� *pphead ==>�ṹָ��pHead
{
	struct Node * ptail = *pptail;//ptail��������*pptail�ƶ�������ֵ��*pptail
	struct Node * phead = *pphead;//phead��������*pphead�ƶ�������ֵ��*pphead
	struct Node * pnew = NULL;//����µķ����ڴ�
	
	if ((pnew = (struct Node *)malloc(sizeof(struct Node))) == NULL)
	{
		printf("ϵͳ�ڴ������� ���������ͬѧ��Ϣ��");
		return;
	}
	pnew -> pnext = NULL;//�����һ���ڵ��β��Ū��
	printf("��������......\n");
	printf("����: ");
	scanf("%s", pnew -> name);
	printf("��ַ: ");
	scanf("%s", pnew -> addr);
	printf("�绰: ");
	scanf("%s", pnew -> phone);
	printf("��λ: ");
	scanf("%s", pnew -> workfor);
	*ptr_last = *ptr_last + 1; //����һ����
	printf("����ͬѧ�ɹ���\n");
	if (*pptail != NULL)
	{
		ptail -> pnext = pnew; //����ͬѧ��Ϣ����txlβ��
		ptail = ptail -> pnext;//ptail��Զָ�����һ��ͬѧ
		*pptail = ptail;
	}
	else
	{
		*pphead = *pptail = pnew; //��һ��ͬѧ 
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
	printf("���ڴ����%d��ѡ��\n", choice);

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
	system("cls");//����
	printf("====ͬѧ¼������Ϣϵͳ====\n");
	printf("\t1.����ͬѧ��Ϣ\n");
	printf("\t2.��ѯͬѧ��Ϣ\n");
	printf("\t3.�޸�ͬѧ��Ϣ\n");
	printf("\t4.ɾ��ͬѧ��Ϣ\n");
	printf("\t5.�г�����ͬѧ\n");
	printf("\t.0�˳�ϵͳ\n");
	printf("==========================\n.");
	printf("���������ѡ��(1/5)��\n");
}

void doListAll(struct Node ** pphead, struct Node ** pptail, int * ptr_last)
{
	int i = 0;
	struct Node * pmove = *pphead;
	printf("ͬѧ¼�й���%d��ͬѧ����Ϣ��\n", *ptr_last);

	while (i < *ptr_last)
	{
		printf("\n==========================\n");
		printf("������%s\t", pmove -> name);
		printf("��ַ��%s\t", pmove -> addr);
		printf("�绰��%s\t", pmove -> phone);
		printf("��λ��%s\t", pmove -> workfor);
		pmove = pmove -> pnext;
		i++;
	}
	printf("\n==========================\n");
}

void doQuit()
{
	printf("\n��ӭ�´�ʹ�ñ�ϵͳ���ټ���");
	exit(0);
}

void doDelete(struct Node ** pphead, struct Node ** pptail, int * ptr_last)
{
	char tname[100];
	int i;
	int find = 0;
	struct Node * p = *pphead;//��ʱ����ָ��
	struct Node * pre = *pphead;//��ʱ����ָ��,��p�ߵ���һ��

	printf("����ɾ��......\n");
	printf("������ͬѧ����: ");
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
		printf("��Ǹ�� ����Ϊ%s��ͬѧ��û��¼ͬѧ¼�С�", tname);
	}
	else
	{
		//ִ��ɾ������
		//ɾ����һ��(ֻ��һ��)
		if (*ptr_last == 1)
		{
			*pphead = NULL;
			*ptr_last = *ptr_last - 1; //ɾ����last��ȥһ����
			printf("����Ϊ%s��ͬѧ��Ϣ�Ѿ��ɹ�ɾ����", tname);
		}
		//ɾ����һ��(����)
		else if (p == pre)
		{
			*pphead = pre -> pnext;
			*ptr_last = *ptr_last - 1; //ɾ����last��ȥһ����
			printf("����Ϊ%s��ͬѧ��Ϣ�Ѿ��ɹ�ɾ����", tname);
		}
		else
		{
			pre -> pnext = p -> pnext;
			*ptr_last = *ptr_last - 1; //ɾ����last��ȥһ����
			printf("����Ϊ%s��ͬѧ��Ϣ�Ѿ��ɹ�ɾ����", tname);
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
	char tname[100];//��ʱ�����������
	struct Node * p = *pphead;//��phead��ֵ����p

	printf("�����޸�......");
	printf("������Ҫ�޸ĵ�ͬѧ����: ");
	scanf("%s", &tname);

	while ((p != NULL) && (!find))
	{
		if (!strcmp(tname, p -> name))
		{
			find = 1;
			printf("���ҵ�ͬѧ��Ϣ���£�\n");
			printf("����: %s\t", p -> name);
			printf("���޸ģ�\n");
			printf("����: ");
			scanf("%s", p -> name);
			printf("��ַ: ");
			scanf("%s", p -> addr);
			printf("�绰: ");
			scanf("%s", p -> phone);
			printf("��λ: ");
			scanf("%s", p -> workfor);
		}
		p = p -> pnext;
	}
	if (!find)
	{
		printf("��Ǹ������Ϊ%s��ͬѧ��û����ͬѧ¼�С�", tname);
	}
	else
	{
		printf("����Ϊ%s��ͬѧ����Ϣ�Ѿ��ɹ��޸ģ�", tname);
	}
	save(pphead, pptail, ptr_last);
}

void doQuery(struct Node ** pphead, struct Node ** pptail, int * ptr_last)
{
	int i;
	int find = 0;
	char tname[100];
	struct Node * p = *pphead;//*pphead ==> phead

	printf("�����ѯ......\n");
	printf("������ͬѧ������");
	scanf("%s", tname);

	while ((p != NULL) && (!find))
	{
		if (!strcmp(tname, p -> name))
		{
			find = 1;
			printf("���ҵ�ͬѧ��Ϣ���£�\n");
			printf("����: %s\t", p -> name);
			printf("��ַ: %s\t", p -> addr);
			printf("�绰: %s\t", p -> phone);
			printf("��λ: %s\t", p -> workfor);
		}
		p = p -> pnext;
	}
	if (!find)
	{
		printf("��Ǹ������Ϊ%s��ͬѧ��û����ͬѧ¼�С�", tname);
	}
}

void init(struct Node ** pphead, struct Node ** pptail, int * ptr_last)//��ȡ�ļ�����
{
	int i = 0;
	struct Node * phead = NULL;//����*pphead�ƶ�
	struct Node * ptail = NULL;
	struct Node * p = NULL;//��ʱ����ָ��

	//���ļ��ľ���·����������
	printf("�����������û���:\n");
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
		fp = fopen(wholeName, "wb");//���û��txl.dat�ļ��ͽ���һ��
		fclose(fp);//�ر�
		fp = fopen(wholeName, "rb");//��rb��ʽ��
	}

	if (fp == NULL)
	{
		printf("���ܴ�ͬѧ¼�ļ� txl.txt,����!");
		exit(0);
		*ptr_last = 0;//�����������ļ��� ͬѧ¼Ϊ��
	}
	else
	{
		while (!feof(fp))
		{
			if ((p = (struct Node *)malloc(sizeof(struct Node))) == NULL)
			{
				printf("ϵͳ�ڴ���ϣ����˳�����");
				exit(0);
			}
			if (fread(p, sizeof(struct Node), 1, fp) == 1)
			{
				//��һ��ͬѧ
				if (i == 0)
				{
					phead = ptail = p;
					*pphead = p;
				}
				ptail -> pnext = p; //nextָ�����ڴ�
				ptail = p;		  //tail�������ڴ�
				*pptail = ptail;
				i++;
				*ptr_last = i;
			}
		}
		//�����޸ģ�����б���û��ͬѧ��ptail��ֵΪ�� ��������������
		if (*ptr_last)
		{
			ptail -> pnext = NULL;
		}
	}
	fclose(fp);
}

void save(struct Node ** pphead, struct Node ** pptail, int * ptr_last) //����ͬѧ¼���ļ�txl.dat��
{
	struct Node * p = *pphead;

	if ((fp = fopen(wholeName, "wb")) == NULL)
	{
		printf("���ܴ�ͬѧ¼��Ϣ�ļ� txl.txt, ����!");
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