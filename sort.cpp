//插入排序
//1.直接插入排序
//2.希尔排序（有增量的多次直接插入排序) （更高效的插入排序）
//3.冒泡排序
//4.快速排序(内含递归划分，使有序)
//5.选择排序
//6.堆排序(内含构造堆)
//7.归并排序(内含有序表合并)
//8.基数排序(比计数排序用的内存更少)
//9.计数排序
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define INF 99999


void CountingSourt(int * data, int len);//普通计数排序(只能排正数)
void NegativeCountingSourt(int * data, int len, int offset);//可以排负数的计数排序
int merge(int * arr, int s1, int e1, int s2, int e2, int * supArry); //有序组合并
int mergeSort(int * arr, int start, int end, int * supArry);//归并排序
void InsertionSort(int * data, int n);//直接插入排序
void ShellSort(int * data, int n, int delta); // delta:希尔排序增量
void BubbleSort(int * data, int n);//交换排序::冒泡排序
void SelectSort(int * data, int n);//选择排序
int Partition(int * data, int i, int j);//划分函数: 从i到j 返回中间index m
void QuickSort(int * data, int i, int j);
void Display(int * data, int len);//输出
void BuildDown(int * data, int len, int rootIndex);//自顶向下过程
void BuildBigRootHeap(int * data, int len);//构造大根堆
void HeapSort(int * data, int len);//堆排序
int LeftChild(int index);//取出左孩子下标
int LastNode(int len);//取完全二叉树的最后一个非叶子节点
void RadixSort(int * data, int len);//基数排序
int MaxBit(int * data, int len);//求data里数字的最大位数
int Resolve(int key, int bit);//获得key的位数为bit的值
void TestUnit();//随机数据测试

int main()
{
	TestUnit();

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

	for (int i = 0; i < n - 1 ; i++)
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
		//Display(data, n);
	}
}

int Partition(int * data, int i, int j)
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
		k = Partition(data, i, j);
		QuickSort(data, k + 1, j);
		QuickSort(data, i, k - 1);
	}
}

void SelectSort(int * data, int n)
{
	int temp;
	int offset;
	int offsetIndex = 0;

	for (int i = 0; i < n; i++)
	{
		offset = data[i];
		for (int j = i; j < n; j++)
		{
			if (data[j] < offset)
			{
				offset = data[j];
				offsetIndex = j;
			}
		}
		temp = data[i];
		data[i] = data[offsetIndex];
		data[offsetIndex] = temp;
	}
}

void BuildBigRootHeap(int * data, int len)
{
	//构建大根堆由 自底到顶 和 自顶到底 两部分组成

	//自底到顶过程(最后一个非叶子到根)
	for (int i = LastNode(len); i >= 0; i--)
	{
		//自顶到底过程(某个根到调整后的某叶子)
		BuildDown(data, len, i);
	}
}

void TestUnit()
{
	/*
	int data[12] = {0, 3, 8, 1, 4, 6, 9, 2, 5, 7, 3, 3};
	srand((unsigned)time(NULL));//插入排序
//1.直接插入排序
//2.希尔排序（有增量的多次直接插入排序) （更高效的插入排序）
//3.冒泡排序
//4.快速排序(内含递归划分，使有序)
//5.选择排序
//6.堆排序(内含构造堆)
//7.归并排序(内含有序表合并)
//8.基数排序(比计数排序用的内存更少)
//9.计数排序
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define INF 99999


void CountingSourt(int * data, int len);//普通计数排序(只能排正数)
void NegativeCountingSourt(int * data, int len, int offset);//可以排负数的计数排序
int merge(int * arr, int s1, int e1, int s2, int e2, int * supArry); //有序组合并
int mergeSort(int * arr, int start, int end, int * supArry);//归并排序
void InsertionSort(int * data, int n);//直接插入排序
void ShellSort(int * data, int n, int delta); // delta:希尔排序增量
void BubbleSort(int * data, int n);//交换排序::冒泡排序
void SelectSort(int * data, int n);//选择排序
int Partition(int * data, int i, int j);//划分函数: 从i到j 返回中间index m
void QuickSort(int * data, int i, int j);
void Display(int * data, int len);//输出
void BuildDown(int * data, int len, int rootIndex);//自顶向下过程
void BuildBigRootHeap(int * data, int len);//构造大根堆
void HeapSort(int * data, int len);//堆排序
int LeftChild(int index);//取出左孩子下标
int LastNode(int len);//取完全二叉树的最后一个非叶子节点
void RadixSort(int * data, int len);//基数排序
int MaxBit(int * data, int len);//求data里数字的最大位数
int Resolve(int key, int bit);//获得key的位数为bit的值
void AutoRandPositiveInteger(int * data, int len);//自动生成随机正数
void AutoRandInteger(int * data, int len, int min);//自动生成随机整数(有负数)
void TestUnit();//随机数据测试

int main()
{
	TestUnit();

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

	for (int i = 0; i < n - 1; i++)
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
		//Display(data, n);
	}
}

int Partition(int * data, int i, int j)
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
		k = Partition(data, i, j);
		QuickSort(data, k + 1, j);
		QuickSort(data, i, k - 1);
	}
}

void SelectSort(int * data, int n)
{
	int temp;
	int offset;
	int offsetIndex = 0;

	for (int i = 0; i < n; i++)
	{
		offset = data[i];
		for (int j = i; j < n; j++)
		{
			if (data[j] < offset)
			{
				offset = data[j];
				offsetIndex = j;
			}
		}
		temp = data[i];
		data[i] = data[offsetIndex];
		data[offsetIndex] = temp;
	}
}

void BuildBigRootHeap(int * data, int len)
{
	//构建大根堆由 自底到顶 和 自顶到底 两部分组成

	//自底到顶过程(最后一个非叶子到根)
	for (int i = LastNode(len); i >= 0; i--)
	{
		//自顶到底过程(某个根到调整后的某叶子)
		BuildDown(data, len, i);
	}
}

void AutoRandPositiveInteger(int * data, int len)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < len; i++)
	{
		data[i] = rand() % 100;
	}
}

void AutoRandInteger(int * data, int len, int min)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < len; i++)
	{
		data[i] = rand() % 100 + min;
	}
}

void TestUnit()
{
	int len = 10;
	int i = 0;
	int * data = new int[len];
	int min = -50;//测试数据最小值

	//有负数的计数排序
	AutoRandPositiveInteger(data, len);
	cout << "普通计数排序(只有正数)" << endl;
	Display(data, len);
	CountingSourt(data, len);
	cout << "排序后:" << endl;
	Display(data, len);

	//普通计数排序
	AutoRandInteger(data, len, min);
	cout << "有负数的计数排序: " << endl;
	Display(data, len);
	NegativeCountingSourt(data, len, min);
	cout << "排序后:" << endl;
	Display(data, len);

	//冒泡排序
	AutoRandInteger(data, len, min);
	cout << "有负数的计数排序: " << endl;
	Display(data, len);
	BubbleSort(data, len);
	cout << "排序后:" << endl;
	Display(data, len);

	//选择排序
	AutoRandInteger(data, len, min);
	cout << "选择排序: " << endl;
	Display(data, len);
	SelectSort(data, len);
	cout << "排序后:" << endl;
	Display(data, len);

	//堆排序
	AutoRandInteger(data, len, min);
	cout << "堆排序: " << endl;
	Display(data, len);
	HeapSort(data, len);
	cout << "排序后:" << endl;
	Display(data, len);

	//增量为3开始的希尔排序
	/*
	cout << "希尔排序：" << endl;
	for (int i = 3; i >= 0; i--)
	{
		//ShellSort(data, len, i);
	}
	for (int i = 0; i < 5; i++)
	*/
}

void BuildDown(int * data, int len, int rootIndex)
{
	int root = data[rootIndex];
	int childIndex = LeftChild(rootIndex);


	while (childIndex < len)
	{
		//使childIndex指向较大的孩子
		if (childIndex != len - 1 && data[childIndex + 1] > data[childIndex])
		{
			childIndex++;
		}
		//和父节点比较
		if (root < data[childIndex])
		{
			data[rootIndex] = data[childIndex];
			rootIndex = childIndex;
			childIndex = LeftChild(rootIndex);
		}
		else
		{
			break;
		}
	}
	data[rootIndex] = root;
}

int LeftChild(int index)
{
	return 2 * index + 1;
}

int merge(int * arr, int s1, int e1, int s2, int e2, int * supArr)
{
	int k = s1;
	int index = s1;

	while (s1 <= e1 && s2 <= e2)
	{
		if (arr[s1] <= arr[s2])
		{
			supArr[k++] = arr[s1++];
		}
		else
		{
			supArr[k++] = arr[s2++];
		}
	}

	while (s1 <= e1)
	{
		supArr[k++] = arr[s1++];
	}
	while (s2 <= e2)
	{
		supArr[k++] = arr[s2++];
	}

	k--;
	while (k >= index)
	{
		arr[k] = supArr[k];
		k--;
	}



	return 0;
}

int mergeSort(int * arr, int s1, int e1, int * supArr)
{
	if (s1 < e1)
	{
		int k = (s1 + e1) / 2;
		mergeSort(arr, s1, k, supArr);
		mergeSort(arr, k + 1, e1, supArr);
		merge(arr, s1, k, k + 1, e1, supArr);
	}

	return 0;
}

int LastNode(int len)
{
	return (len - 2) / 2;
}

void HeapSort(int * data, int len)
{
	int temp;
	BuildBigRootHeap(data, len);
	for (int i = len - 1; i >= 0; i--)
	{
		temp = data[0];
		data[0] = data[i];
		data[i] = temp;
		BuildDown(data, i, 0);
	}
}

void RadixSort(int * data, int len)
{
	int d = MaxBit(data, len);
	int * tmp = new int[len];
	int * count = new int[10]; //计数器
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //进行d次排序
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //每次分配前清空计数器
		//Display(count, 10);
		for (j = 0; j < len; j++)
		{
			k = (data[j] / radix) % 10; //统计每个桶中的记录数
			count[k]++;
		}
		//Display(count, 10);
		cout << "count1:";
		Display(count, 10);
		for (j = 1; j < 10; j++)
		{
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶(拓展一维数组)
			//Display(count, 10);
		}
		cout << "count2:";
		Display(count, 10);
		for (j = len - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
		{
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
			cout << "count[k]-1:" << count[k] - 1 << "    data:" << data[j] << "   k:" << k << endl;
		}
		for (j = 0; j < len; j++) //将临时数组的内容复制到data中
			data[j] = tmp[j];
		radix = radix * 10;
		Display(data, len);
	}
	delete[]tmp;
	delete[]count;
}

int Resolve(int key, int bit)
{
	switch (bit)
	{
	case 1:
		key = key % 10;
		break;
	case 2:
		key = key % 100 / 10;
		break;
	case 3:
		key = key % 1000 / 100;
		break;
	case 4:
		key = key % 10000 / 1000;
		break;
	}

	return key;
}

int MaxBit(int * data, int len)
{
	int bit = 1;
	int inc = 10;
	for (int i = 0; i < len; i++)
	{
		while (data[i] >= inc)
		{
			inc *= 10;
			bit++;
		}
	}


	return bit;
}

void NegativeCountingSourt(int * data, int len, int min)
{
	int offset = abs(min);//给负数排序需要添加偏移量
	int max = data[0];
	for (int i = 0; i < len; i++)
	{
		if (data[i] > max)
		{
			max = data[i];
		}
	}
	max = max + 1 + offset; //max由数字转成数组下标 + 1

	int * count = new int[max];
	int * supData = new int[len];

	//初始化count
	for (int i = 0; i < max; i++)
	{
		count[i] = 0;
	}
	//统计元素个数
	for (int i = 0; i < len; i++)
	{
		count[data[i] + 50] = count[data[i] + offset] + 1;
	}
	//分配位置
	for (int i = 1; i < max; i++)
	{
		count[i] = count[i - 1] + count[i];
	}

	for (int i = len - 1; i >= 0; i--)
	{
		supData[count[data[i] + offset] - 1] = data[i] + offset;
		count[data[i] + offset] = count[data[i] + offset] - 1;
	}

	for (int i = 0; i < len; i++)
	{
		data[i] = supData[i] - offset;
	}

	delete supData;
	delete count;
}

void CountingSourt(int * data, int len)
{
	int max = data[0];
	for (int i = 0; i < len; i++)
	{
		if (data[i] > max)
		{
			max = data[i];
		}
	}

	int * count = new int[max + 1];
	int * supData = new int[len];

	//初始化count
	for (int i = 0; i <= max; i++)
	{
		count[i] = 0;
	}
	//统计元素个数
	for (int i = 0; i < len; i++)
	{
		count[data[i]] = count[data[i]] + 1;
	}
	//分配位置
	for (int i = 1; i <= max; i++)
	{
		count[i] = count[i - 1] + count[i];
	}

	for (int i = len - 1; i >= 0; i--)
	{
		supData[count[data[i]] - 1] = data[i];
		count[data[i]] = count[data[i]] - 1;
	}

	for (int i = 0; i < len; i++)
	{
		data[i] = supData[i];
	}

	delete supData;
	delete count;
}

void Display(int * data, int len)
{
	/*
	cout << "======================" << endl << "index:";
	for (int i = 0; i < len; i++)
	{
		cout << setw(3) << i << " ";
	}*/
	cout << endl << "data :";
	for (int i = 0; i < len; i++)
	{
		cout << setw(3) << data[i] << " ";
	}
	cout << endl;
	cout << "========================================================================================" << endl;
}
	int len = 12;
	Display(data, len);
	for (int i = 0; i < 10; i++)
	{
		data[i] = rand() % 100 - 50;
	}
	
	//增量为3开始的希尔排序
	
	cout << "希尔排序：" << endl;
	for (int i = 3; i >= 0; i--)
	{
		//ShellSort(array, 5, i);
	}
	for (int i = 0; i < 5; i++)

	Display(data, 10);
	SelectSort(data, 10);
	Display(data, 10);
	

	Display(data, len);
	HeapSort(data, len);
	Display(data, len);
	
	RedixSort(data, len);
	RadixSort(data, len);
	Display(data, len);
	*/

	int len = 7;
	int i = 0;
	int * data = new int[len];
	int min = -50;//测试数据最小值
	//随机生成-50~50的数据
	srand((unsigned)time(NULL));
	for (i = 0; i < len; i++)
	{
		data[i] = rand() % 100;
	}
	/*
	cout << "普通计数排序(只有正数)" << endl;
	Display(data, len);
	CountingSourt(data, len);
	cout << "计数排序后:" << endl;
	Display(data, len);
	*/
	//随机生成-50~50的数据
	srand((unsigned)time(NULL));
	for (i = 0; i < len; i++)
	{
		data[i] = rand() % 100 + min;
	}
	Display(data, len);
	cout << "有负数的计数排序: " << endl;
	NegativeCountingSourt(data, len, min);
	cout << "计数排序后:" << endl;
	Display(data, len);
}

void BuildDown(int * data, int len, int rootIndex)
{
	int root = data[rootIndex];
	int childIndex = LeftChild(rootIndex);


	while (childIndex < len)
	{
		//使childIndex指向较大的孩子
		if (childIndex != len - 1 && data[childIndex + 1] > data[childIndex])
		{
			childIndex++;
		}
		//和父节点比较
		if (root < data[childIndex])
		{
			data[rootIndex] = data[childIndex];
			rootIndex = childIndex;
			childIndex = LeftChild(rootIndex);
		}
		else
		{
			break;
		}
	}
	data[rootIndex] = root;
}

int LeftChild(int index)
{
	return 2 * index + 1;
}

int merge(int * arr, int s1, int e1, int s2, int e2, int * supArr)
{
	int k = s1;
	int index = s1;

	while (s1 <= e1 && s2 <= e2)
	{
		if (arr[s1] <= arr[s2])
		{
			supArr[k++] = arr[s1++];
		}
		else
		{
			supArr[k++] = arr[s2++];
		}
	}

	while (s1 <= e1)
	{
		supArr[k++] = arr[s1++];
	}
	while (s2 <= e2)
	{
		supArr[k++] = arr[s2++];
	}

	k--;
	while (k >= index)
	{
		arr[k] = supArr[k];
		k--;
	}



	return 0;
}

int mergeSort(int * arr, int s1, int e1, int * supArr)
{
	if (s1 < e1)
	{
		int k = (s1 + e1) / 2;
		mergeSort(arr, s1, k, supArr);
		mergeSort(arr, k + 1, e1, supArr);
		merge(arr, s1, k, k + 1, e1, supArr);
	}

	return 0;
}

int LastNode(int len)
{
	return (len - 2) / 2;
}

void HeapSort(int * data, int len)
{
	int temp;
	BuildBigRootHeap(data, len);
	for (int i = len - 1; i >= 0; i--)
	{
		temp = data[0];
		data[0] = data[i];
		data[i] = temp;
		BuildDown(data, i, 0);
	}
}

void RadixSort(int * data, int len)
{
	int d = MaxBit(data, len);
	int * tmp = new int[len];
	int * count = new int[10]; //计数器
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //进行d次排序
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //每次分配前清空计数器
		//Display(count, 10);
		for (j = 0; j < len; j++)
		{
			k = (data[j] / radix) % 10; //统计每个桶中的记录数
			count[k]++;
		}
		//Display(count, 10);
		cout << "count1:";
		Display(count, 10);
		for (j = 1; j < 10; j++)
		{
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶(拓展一维数组)
			//Display(count, 10);
		}
		cout << "count2:";
		Display(count, 10);
		for (j = len - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
		{
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
			cout << "count[k]-1:" << count[k] - 1 << "    data:" << data[j] << "   k:" << k << endl;
		}
		for (j = 0; j < len; j++) //将临时数组的内容复制到data中
			data[j] = tmp[j];
		radix = radix * 10;
		Display(data, len);
	}
	delete[]tmp;
	delete[]count;
}

int Resolve(int key, int bit)
{
	switch (bit)
	{
	case 1: 
		key = key % 10;
		break;
	case 2:
		key = key % 100 / 10;
		break;
	case 3:
		key = key % 1000 / 100;
		break;
	case 4:
		key = key % 10000 / 1000;
		break;
	}

	return key;
}

int MaxBit(int * data, int len)
{
	int bit = 1;
	int inc = 10;
	for (int i = 0; i < len; i++)
	{
		while (data[i] >= inc)
		{
			inc *= 10;
			bit++;
		}
	}


	return bit;
}

void NegativeCountingSourt(int * data, int len, int min)
{
	int offset = abs(min);//给负数排序需要添加偏移量
	int max = data[0];
	for (int i = 0; i < len; i++)
	{
		if (data[i] > max)
		{
			max = data[i];
		}
	}
	max = max + 1 + offset; //max由数字转成数组下标 + 1

	int * count = new int[max];
	int * supData = new int[len];

	//初始化count
	for (int i = 0; i < max; i++)
	{
		count[i] = 0;
	}
	//统计元素个数
	for (int i = 0; i < len; i++)
	{
		count[data[i] + 50] = count[data[i] + offset] + 1;
	}
	//分配位置
	for (int i = 1; i < max; i++)
	{
		count[i] = count[i - 1] + count[i];
	}

	for (int i = len - 1; i >= 0; i--)
	{
		supData[count[data[i] + offset] - 1] = data[i] + offset;
		count[data[i] + offset] = count[data[i] + offset] - 1;
	}

	for (int i = 0; i < len; i++)
	{
		data[i] = supData[i] - offset;
	}

	delete supData;
	delete count;
}

void CountingSourt(int * data, int len)
{
	int max = data[0];
	for (int i = 0; i < len; i++)
	{
		if (data[i] > max)
		{
			max = data[i];
		}
	}

	int * count = new int[max + 1];
	int * supData = new int[len];

	//初始化count
	for (int i = 0; i <= max; i++)
	{
		count[i] = 0;
	}
	//统计元素个数
	for (int i = 0; i < len; i++)
	{
		count[data[i]] = count[data[i]] + 1;
	}
	//分配位置
	for (int i = 1; i <= max; i++)
	{
		count[i] = count[i - 1] + count[i];
	}

	for (int i = len - 1; i >= 0; i--)
	{
		supData[count[data[i]] - 1] = data[i];
		count[data[i]] = count[data[i]] - 1;
	}

	for (int i = 0; i < len; i++)
	{
		data[i] = supData[i];
	}

	delete supData;
	delete count;
}

void Display(int * data, int len)
{
	cout << "======================" << endl << "index:";
	for (int i = 0; i < len; i++)
	{
		cout << setw(3) << i << " ";
	}
	cout << endl << "data :";
	for (int i = 0; i < len; i++)
	{
		cout << setw(3) << data[i] << " ";
	}
	cout << endl;
	cout << "======================" << endl;
}