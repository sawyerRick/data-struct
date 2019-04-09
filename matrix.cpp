#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;
typedef int elemtype;

void InitMatrix(elemtype **& Matrix, int n, int m);
void DisplayMatrix(elemtype **& Matrix, int n, int m);
void Transpose(elemtype **& Matrix, int n, int m, elemtype **& transposeMatrix);
void MatrixAdd(elemtype **& Matrix1, elemtype **& Matrix2, int n, int m);
void MatrixSub(elemtype **& Matrix1, elemtype **& Matrix2, int n, int m);
void MatrixMul(elemtype **& Matrix1, elemtype **& Matrix2, int n1, int m1, int n2, int m2);
void TestUnit();

int main()
{
	TestUnit();

	return 0;
}

void InitMatrix(elemtype **& Matrix, int n, int m)
{

	for (int i = 0; i < n; i++)
	{
		Matrix[i] = new int[m];
	}

	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < m; j++)
		{
			Matrix[i][j] = rand() % 5;
		}
	}
}

void DisplayMatrix(elemtype **& Matrix, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << setw(5) << Matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void Transpose(elemtype **& Matrix, int n, int m, elemtype **& transposeMatrix)
{
	transposeMatrix = new int *[m];
	for (int i = 0; i < m; i++)
	{
		transposeMatrix[i] = new int[n];
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			transposeMatrix[i][j] = Matrix[j][i];
		}
	}
}

void MatrixAdd(elemtype **& Matrix1, elemtype **& Matrix2, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Matrix1[i][j] += Matrix2[i][j];
		}
	}
}

void MatrixSub(elemtype **& Matrix1, elemtype **& Matrix2, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Matrix1[i][j] -= Matrix2[i][j];
		}
	}
}

void MatrixMul(elemtype **& Matrix1, elemtype **& Matrix2, int n1, int m1, int n2, int m2)
{
	//矩阵相乘条件:Matrix1的行数等于Matrix2的列数
	if (n1 != m2)
	{
		cout << "不符合乘法条件..." << endl;

		return;
	}

	//Matrix1 X Matrix2生成一个n1行m2列的矩阵Matrix3
	elemtype ** Matrix3 = new int *[n1];
	for (int i = 0; i < n1; i++)
	{
		Matrix3[i] = new int[m2];
	}
	int ACC = 0;

	// 遍历Matrix1
	for (int i = 0; i < n1; i++)
	{ 
		for (int j = 0; j < m1; j++)
		{
			ACC = 0;
			// 遍历Matrix2的第k行，i列
			for (int k = 0; k < m2; k++)
			{
				ACC += Matrix1[i][j] * Matrix2[k][i];
			}
			Matrix3[i][j] = ACC;
		}
	}

	delete []Matrix1;
	Matrix1 = Matrix3;
}

void TestUnit()
{
	int n1 = 0;
	int m1 = 0;
	int n2 = 0;
	int m2 = 0;
	cout << "请输入矩阵M1行数列数 n1 m1:" << endl;
	cin >> n1 >> m1;
	cout << "请输入矩阵M2行数列数 n2 m2:" << endl;
	cin >> n2 >> m2;
	
	if (n1 <= 0 || m1 <= 0)
	{
		cout << "非法输入...已退出..." << endl;

		return;
	}

	//初始化矩阵
	elemtype ** Matrix1 = new int *[n1];
	elemtype ** Matrix2 = new int *[n2];
	srand((unsigned)time(NULL));
	InitMatrix(Matrix1, n1, m1);
	InitMatrix(Matrix2, n2, m2);
	cout << "生成矩阵M1:" << endl;
	DisplayMatrix(Matrix1, n1, m1);
	cout << "生成矩阵M2:" << endl;
	DisplayMatrix(Matrix2, n2, m2);
	
	if (n1 == n2 && m1 == m2)
	{
		cout << "M1 + M2:" << endl;
		MatrixAdd(Matrix1, Matrix2, n1, m1);
		DisplayMatrix(Matrix1, n1, m1);

		cout << "M1 - M2:" << endl;
		MatrixSub(Matrix1, Matrix2, n1, m1);
		DisplayMatrix(Matrix1, n1, m1);
	}
	else
	{
		cout << "M1 M2 行列数不相等，不能做加减运算..." << endl;
	}
	
	if (n1 == m2)
	{
		cout << "M1 X M2:" << endl;
		MatrixMul(Matrix1, Matrix2, n1, m1, n2, m2);
		DisplayMatrix(Matrix1, n1, m1);
	}
	else
	{
		cout << "M1行数不等于M2列数，不能做乘法运算..." << endl;
	}

	//矩阵转置
	cout << "转置前:" << endl;
	DisplayMatrix(Matrix1, n1, m1);
	cout << "转置后:" << endl;
	elemtype ** transposeMatrix;
	Transpose(Matrix1, n1, m1, transposeMatrix);
	DisplayMatrix(transposeMatrix, m1, n1);

	delete[]Matrix1;
	delete[]Matrix2;
	delete []transposeMatrix;
}