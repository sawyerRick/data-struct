//��������
//1.ֱ�Ӳ�������
//2.ϣ�������������Ķ��ֱ�Ӳ�������) ������Ч�Ĳ�������
//3.ð������
//4.��������(�ݹ黮�֣�ʹ����)
#include <iostream>

using namespace std;
void InsertionSort(int * data, int n);//ֱ�Ӳ�������
void ShellSort(int * data, int n, int delta); // delta:ϣ����������
void BubbleSort(int * data, int n);//��������::ð������
int partition(int * data, int i, int j);//���ֺ���: ��i��j �����м�index m
void QuickSort(int * data, int i, int j);

int main()
{
	int array[5] = { 4, 1, 2, 5, 3 };
	int array2[8] = {4, 3, 7, 1, 2, 8, 6, 5};

	cout << "����:" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	//����Ϊ3��ʼ��ϣ������
	
	cout << "ϣ������" << endl;
	for (int i = 3; i >= 0; i--)
	{
		ShellSort(array, 5, i);
	}
	for (int i = 0; i < 5; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	//BubbleSort(array, 5);
	//partition(array, 0, 4);
	cout << "��������" << endl;
	QuickSort(array, 0, 4);
	for (int i = 0; i < 5; i++)
	{
		cout << array[i] << " ";
	}
	/*
	InsertionSort(array, 5);
	for (int i = 0; i < 5; i++)
	{
		cout << array[i] << endl;
	}
	*/

	return 0;
}

void InsertionSort(int * data, int n)
{
	int temp;
	int j = 0;

	for (int i = 1; i < n; i++)
	{
		temp = data[i];
		for (j = i - 1; j >= 0 && temp < data[j]; j--)
		{
			data[j + 1] = data[j];
		}
		data[j + 1] = temp;
	}

}

void ShellSort(int * data, int n, int delta)
{
	int temp;
	int j = 0;

	for (int i = delta; i < n; i++)
	{
		temp = data[i];
		for (j = i - delta; j >= 0 && temp < data[j]; j = j - delta)
		{
			data[j + delta] = data[j];
		}
		data[j + delta] = temp;
	}

}

void BubbleSort(int * data, int n)
{
	int temp;

	for (int i = 1; i <= n - 1; i++)
	{
		for (int j = 1; j <= n - 1; j++)
		{
			if (data[j - 1] > data[j])
			{
				temp = data[j];
				data[j] = data[j - 1];
				data[j - 1] = temp;
			}
		}
	}
}

int partition(int * data, int i, int j)
{
	int temp = data[i];

	while (i < j)
	{
		while (data[j] >= temp && i < j)
		{
			j--;
		}
		if (i < j)
		{
			data[i++] = data[j];
		}
		while (data[i] <= temp && i < j)
		{
			i++;
		}
		if (i < j)
		{
			data[j--] = data[i];
		}
		data[i] = temp;
	}
	
	return i;
}

void QuickSort(int * data, int i, int j)
{
	int k;
	if (i < j)
	{
		k = partition(data, i, j);
		QuickSort(data, k + 1, j);
		QuickSort(data, i, k - 1);
	}
}