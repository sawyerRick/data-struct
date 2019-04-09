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
	//�����������:Matrix1����������Matrix2������
	if (n1 != m2)
	{
		cout << "�����ϳ˷�����..." << endl;

		return;
	}

	//Matrix1 X Matrix2����һ��n1��m2�еľ���Matrix3
	elemtype ** Matrix3 = new int *[n1];
	for (int i = 0; i < n1; i++)
	{
		Matrix3[i] = new int[m2];
	}
	int ACC = 0;

	// ����Matrix1
	for (int i = 0; i < n1; i++)
	{ 
		for (int j = 0; j < m1; j++)
		{
			ACC = 0;
			// ����Matrix2�ĵ�k�У�i��
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
	cout << "���������M1�������� n1 m1:" << endl;
	cin >> n1 >> m1;
	cout << "���������M2�������� n2 m2:" << endl;
	cin >> n2 >> m2;
	
	if (n1 <= 0 || m1 <= 0)
	{
		cout << "�Ƿ�����...���˳�..." << endl;

		return;
	}

	//��ʼ������
	elemtype ** Matrix1 = new int *[n1];
	elemtype ** Matrix2 = new int *[n2];
	srand((unsigned)time(NULL));
	InitMatrix(Matrix1, n1, m1);
	InitMatrix(Matrix2, n2, m2);
	cout << "���ɾ���M1:" << endl;
	DisplayMatrix(Matrix1, n1, m1);
	cout << "���ɾ���M2:" << endl;
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
		cout << "M1 M2 ����������ȣ��������Ӽ�����..." << endl;
	}
	
	if (n1 == m2)
	{
		cout << "M1 X M2:" << endl;
		MatrixMul(Matrix1, Matrix2, n1, m1, n2, m2);
		DisplayMatrix(Matrix1, n1, m1);
	}
	else
	{
		cout << "M1����������M2�������������˷�����..." << endl;
	}

	//����ת��
	cout << "ת��ǰ:" << endl;
	DisplayMatrix(Matrix1, n1, m1);
	cout << "ת�ú�:" << endl;
	elemtype ** transposeMatrix;
	Transpose(Matrix1, n1, m1, transposeMatrix);
	DisplayMatrix(transposeMatrix, m1, n1);

	delete[]Matrix1;
	delete[]Matrix2;
	delete []transposeMatrix;
}