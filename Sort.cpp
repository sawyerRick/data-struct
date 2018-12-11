//插入排序
//1.直接插入排序
//2.希尔排序（有增量的多次直接插入排序) （更高效的插入排序）
//3.冒泡排序
//4.快速排序(递归划分，使有序)
#include <iostream>

using namespace std;
void InsertionSort(int * data, int n);//直接插入排序
void ShellSort(int * data, int n, int delta); // delta:希尔排序增量
void BubbleSort(int * data, int n);//交换排序::冒泡排序
int partition(int * data, int i, int j);//划分函数: 从i到j 返回中间index m
void QuickSort(int * data, int i, int j);

int main()
{
	int array[5] = { 4, 1, 2, 5, 3 };
	int array2[8] = {4, 3, 7, 1, 2, 8, 6, 5};

	cout << "数组:" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	//增量为3开始的希尔排序
	
	cout << "希尔排序：" << endl;
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
	cout << "快速排序：" << endl;
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