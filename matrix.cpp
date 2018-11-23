//矩阵1初始化，转置矩阵1，矩阵二初始化，矩阵1 + 矩阵2
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

//矩阵加法采用更好用的储存方式矩阵
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
	printf("请初始化矩阵1...\n");
	TSMatrix * matrix1 = initMatrix();
	displayMatrix(matrix1);
	newTranspose(matrix1);
	displayMatrix(matrix1);
	/*
	printf("矩阵1转置前:\n");
	displayMatrix(matrix1);
	printf("矩阵1转置后:\n");
	matrix1 = transpose(matrix1);
	displayMatrix(matrix1);
	displayTripleTable(matrix1);
	system("pause");
	system("CLS");

	printf("请初始化矩阵2...\n");
	TSMatrix * matrix2 = initMatrix();
	system("pause");
	system("CLS");
	printf("转置后的矩阵1 + 矩阵2：\n");
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
	printf("[*] 正在初始化稀疏矩阵...\n");
	matrix->nonZero = 0;
	printf("[+] 请输入最大行数:");
	scanf("%d", &matrix->row);
	printf("[+] 请输入最大列数:");
	scanf("%d", &matrix->column);
	printf("[+] 非零数字个数:");
	scanf("%d", &matrix->nonZero);
	printf("[*] 请输入行: 列: 值:  (如: 1 2 3 ==>一行二列的值为3)\n");
	for(int i = 1; i <= matrix->nonZero; i++)
	{
		do
		{
			scanf("%d", &matrix->data[i].i);
			scanf("%d", &matrix->data[i].j);
			scanf("%d", &matrix->data[i].value);
			
			for (int k = 0; k < i; k++)
			{
				//判断该位置是否有数字
				if (matrix->data[k].i == matrix->data[i].i && matrix->data[k].j == matrix->data[i].j)
				{
					printf("行:%d 列:%d 空间已被占...已退出程序...\n", matrix->data[i].i, matrix->data[i].j, matrix->data[i].value);
					exit(0);
				}
			}
			if(matrix->data[i].i <= 0 || matrix->data[i].i > matrix->row || matrix->data[i].j <= 0 || matrix->data[i].j > matrix->row)
			{
				printf("[!] 输入非法...请重新输入...\n");
				fflush(stdin);
			}
		}while (matrix->data[i].i <= 0 || matrix->data[i].i > matrix->row || matrix->data[i].j <= 0 || matrix->data[i].j > matrix->row);
		
		printf("[+] 行:%d 列:%d 值:%d 成功保存...请继续输入...\n", matrix->data[i].i, matrix->data[i].j, matrix->data[i].value);
	}
	printf("[*] 稀疏矩阵初始化完毕...\n");
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
	printf("三元组表:\n");
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
		printf("不能相加的矩阵类型, 请检查...");
		return ;
	}
	TempMatrix table1[MAXSIZE][MAXSIZE] = {0};
	TempMatrix table2[MAXSIZE][MAXSIZE] = {0};

	//遍历三元组表初始化TempMatrix,复杂度很低
	for (int i = 1; i <= matrix1->nonZero; i++)
	{
		table1[matrix1->data[i].i][matrix1->data[i].j].v = matrix1->data[i].value;
	}

	for (int i = 1; i <= matrix2->nonZero; i++)
	{
		table2[matrix2->data[i].i][matrix2->data[i].j].v = matrix2->data[i].value;
	}

	//遍历TempMatrix，自加输出
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