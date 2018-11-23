//����1��ʼ����ת�þ���1���������ʼ��������1 + ����2
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int elemtype;
typedef struct
{
	int i, j;
	elemtype value;
}Triple;

typedef struct
{
	Triple data[MAXSIZE];
	int row, column, nonZero;
}TSMatrix;

//����ӷ����ø����õĴ��淽ʽ����
typedef struct
{
	elemtype v;
}TempMatrix;

TSMatrix * initMatrix();
void displayMatrix(TSMatrix * matrix);
void displayTripleTable(TSMatrix * matrix);
void newTranspose(TSMatrix * matrix);
TSMatrix * transpose(TSMatrix * matrix);
void addMatrix(TSMatrix * matrix1, TSMatrix * matrix2);

int main()
{
	printf("���ʼ������1...\n");
	TSMatrix * matrix1 = initMatrix();
	displayMatrix(matrix1);
	newTranspose(matrix1);
	displayMatrix(matrix1);
	/*
	printf("����1ת��ǰ:\n");
	displayMatrix(matrix1);
	printf("����1ת�ú�:\n");
	matrix1 = transpose(matrix1);
	displayMatrix(matrix1);
	displayTripleTable(matrix1);
	system("pause");
	system("CLS");

	printf("���ʼ������2...\n");
	TSMatrix * matrix2 = initMatrix();
	system("pause");
	system("CLS");
	printf("ת�ú�ľ���1 + ����2��\n");
	displayMatrix(matrix2);
	printf("    +\n");
	displayMatrix(matrix1);
	printf("    =\n");
	addMatrix(matrix1, matrix2);*/

	return 0;
}

TSMatrix * initMatrix()
{
	TSMatrix * matrix = (TSMatrix *)malloc(sizeof(TSMatrix));
	printf("[*] ���ڳ�ʼ��ϡ�����...\n");
	matrix->nonZero = 0;
	printf("[+] �������������:");
	scanf("%d", &matrix->row);
	printf("[+] �������������:");
	scanf("%d", &matrix->column);
	printf("[+] �������ָ���:");
	scanf("%d", &matrix->nonZero);
	printf("[*] ��������: ��: ֵ:  (��: 1 2 3 ==>һ�ж��е�ֵΪ3)\n");
	for(int i = 1; i <= matrix->nonZero; i++)
	{
		do
		{
			scanf("%d", &matrix->data[i].i);
			scanf("%d", &matrix->data[i].j);
			scanf("%d", &matrix->data[i].value);
			
			for (int k = 0; k < i; k++)
			{
				//�жϸ�λ���Ƿ�������
				if (matrix->data[k].i == matrix->data[i].i && matrix->data[k].j == matrix->data[i].j)
				{
					printf("��:%d ��:%d �ռ��ѱ�ռ...���˳�����...\n", matrix->data[i].i, matrix->data[i].j, matrix->data[i].value);
					exit(0);
				}
			}
			if(matrix->data[i].i <= 0 || matrix->data[i].i > matrix->row || matrix->data[i].j <= 0 || matrix->data[i].j > matrix->row)
			{
				printf("[!] ����Ƿ�...����������...\n");
				fflush(stdin);
			}
		}while (matrix->data[i].i <= 0 || matrix->data[i].i > matrix->row || matrix->data[i].j <= 0 || matrix->data[i].j > matrix->row);
		
		printf("[+] ��:%d ��:%d ֵ:%d �ɹ�����...���������...\n", matrix->data[i].i, matrix->data[i].j, matrix->data[i].value);
	}
	printf("[*] ϡ������ʼ�����...\n");
	return matrix;
}

void displayMatrix(TSMatrix * matrix)
{
	int isFound = 0;
	for(int i = 1; i <= matrix->row; i++)
	{
		for(int j = 1; j <= matrix->column; j++)
		{
			isFound = 0;
			for (int k = 0; k <= matrix->nonZero; k++)
			{
				if (matrix->data[k].i == i && matrix->data[k].j == j)
				{
					printf("%d  ", matrix->data[k].value);
					isFound = 1;
					break;
				}
			}
			if(!isFound)
			{
				printf("0  ");
			}
		}
		printf("\n");
	}
}

void displayTripleTable(TSMatrix * matrix)
{
	printf("��Ԫ���:\n");
	printf("  | i  j  v\n");
	for (int i = 1; i <= matrix->nonZero; i++)
	{
		printf("%d | %d  %d  %d\n", i, matrix->data[i].i, matrix->data[i].j, matrix->data[i].value);
	}
}

TSMatrix * transpose(TSMatrix * matrix)
{
	int j = 0, k = 0;
	TSMatrix * newMatrix = (TSMatrix *)malloc(sizeof(TSMatrix));
	int * num = (int *)malloc((matrix->column + 1) * sizeof(int));
	int * cpot = (int *)malloc((matrix->column + 1) * sizeof(int));
	newMatrix->column = matrix->column;
	newMatrix->row = matrix->column;
	newMatrix->nonZero = matrix->column;	

	if (newMatrix->nonZero > 0)
	{
		for (int i = 1; i <= matrix->column; i++)
		{
			num[i] = 0;
		}
		for (int i = 1; i <= matrix->nonZero; i++)
		{
			j = matrix->data[i].j;
			num[j]++;
		}
		cpot[1] = 1;
		for(int i = 2; i <= matrix->column; i++)
		{
			cpot[i] = cpot[i - 1] + num[i - 1];
		}
		for(int i = 1; i <= (matrix->nonZero); i++)
		{
			j = matrix->data[i].j;
			k = cpot[j];
			newMatrix->data[k].i = matrix->data[i].j;
			newMatrix->data[k].j = matrix->data[i].i;
			newMatrix->data[k].value = matrix->data[i].value;
			cpot[j]++;
		}
	}
	return newMatrix;
}

void addMatrix(TSMatrix * matrix1, TSMatrix * matrix2)
{
	if (matrix1->row != matrix2->row || matrix1->column != matrix2->column)
	{
		printf("������ӵľ�������, ����...");
		return ;
	}
	TempMatrix table1[MAXSIZE][MAXSIZE] = {0};
	TempMatrix table2[MAXSIZE][MAXSIZE] = {0};

	//������Ԫ����ʼ��TempMatrix,���ӶȺܵ�
	for (int i = 1; i <= matrix1->nonZero; i++)
	{
		table1[matrix1->data[i].i][matrix1->data[i].j].v = matrix1->data[i].value;
	}

	for (int i = 1; i <= matrix2->nonZero; i++)
	{
		table2[matrix2->data[i].i][matrix2->data[i].j].v = matrix2->data[i].value;
	}

	//����TempMatrix���Լ����
	for (int i = 1; i <= matrix1->row; i++)
	{
		for (int j = 1; j <= matrix1->column; j++)
		{
			if (table1[i][j].v || table2[i][j].v)
			{
				table1[i][j].v += table2[i][j].v;
				printf("%d  ", table1[i][j].v);
			}
			else
			{
				printf("0  ");
			}
		}
		printf("\n");
	}
}

void newTranspose(TSMatrix * matrix)
{
	int temp = 0;
	for (int i = 0; i <= matrix->nonZero; i++)
	{
		temp = matrix->data[i].i;
		matrix->data[i].i = matrix->data[i].j;
		matrix->data[i].j = temp;
	}
}