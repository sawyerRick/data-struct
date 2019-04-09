//��������
//1.ֱ�Ӳ�������
//2.ϣ�������������Ķ��ֱ�Ӳ�������) ������Ч�Ĳ�������
//3.ð������
//4.��������(�ں��ݹ黮�֣�ʹ����)
//5.ѡ������
//6.������(�ں������)
//7.�鲢����(�ں������ϲ�)
//8.��������(�ȼ��������õ��ڴ����)
//9.��������
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define INF 99999


void CountingSourt(int * data, int len);//��ͨ��������(ֻ��������)
void NegativeCountingSourt(int * data, int len, int offset);//�����Ÿ����ļ�������
int merge(int * arr, int s1, int e1, int s2, int e2, int * supArry); //������ϲ�
int mergeSort(int * arr, int start, int end, int * supArry);//�鲢����
void InsertionSort(int * data, int n);//ֱ�Ӳ�������
void ShellSort(int * data, int n, int delta); // delta:ϣ����������
void BubbleSort(int * data, int n);//��������::ð������
void SelectSort(int * data, int n);//ѡ������
int Partition(int * data, int i, int j);//���ֺ���: ��i��j �����м�index m
void QuickSort(int * data, int i, int j);
void Display(int * data, int len);//���
void BuildDown(int * data, int len, int rootIndex);//�Զ����¹���
void BuildBigRootHeap(int * data, int len);//��������
void HeapSort(int * data, int len);//������
int LeftChild(int index);//ȡ�������±�
int LastNode(int len);//ȡ��ȫ�����������һ����Ҷ�ӽڵ�
void RadixSort(int * data, int len);//��������
int MaxBit(int * data, int len);//��data�����ֵ����λ��
int Resolve(int key, int bit);//���key��λ��Ϊbit��ֵ
void TestUnit();//������ݲ���

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
	//����������� �Ե׵��� �� �Զ����� ���������

	//�Ե׵�������(���һ����Ҷ�ӵ���)
	for (int i = LastNode(len); i >= 0; i--)
	{
		//�Զ����׹���(ĳ�������������ĳҶ��)
		BuildDown(data, len, i);
	}
}

void TestUnit()
{
	/*
	int data[12] = {0, 3, 8, 1, 4, 6, 9, 2, 5, 7, 3, 3};
	srand((unsigned)time(NULL));//��������
//1.ֱ�Ӳ�������
//2.ϣ�������������Ķ��ֱ�Ӳ�������) ������Ч�Ĳ�������
//3.ð������
//4.��������(�ں��ݹ黮�֣�ʹ����)
//5.ѡ������
//6.������(�ں������)
//7.�鲢����(�ں������ϲ�)
//8.��������(�ȼ��������õ��ڴ����)
//9.��������
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define INF 99999


void CountingSourt(int * data, int len);//��ͨ��������(ֻ��������)
void NegativeCountingSourt(int * data, int len, int offset);//�����Ÿ����ļ�������
int merge(int * arr, int s1, int e1, int s2, int e2, int * supArry); //������ϲ�
int mergeSort(int * arr, int start, int end, int * supArry);//�鲢����
void InsertionSort(int * data, int n);//ֱ�Ӳ�������
void ShellSort(int * data, int n, int delta); // delta:ϣ����������
void BubbleSort(int * data, int n);//��������::ð������
void SelectSort(int * data, int n);//ѡ������
int Partition(int * data, int i, int j);//���ֺ���: ��i��j �����м�index m
void QuickSort(int * data, int i, int j);
void Display(int * data, int len);//���
void BuildDown(int * data, int len, int rootIndex);//�Զ����¹���
void BuildBigRootHeap(int * data, int len);//��������
void HeapSort(int * data, int len);//������
int LeftChild(int index);//ȡ�������±�
int LastNode(int len);//ȡ��ȫ�����������һ����Ҷ�ӽڵ�
void RadixSort(int * data, int len);//��������
int MaxBit(int * data, int len);//��data�����ֵ����λ��
int Resolve(int key, int bit);//���key��λ��Ϊbit��ֵ
void AutoRandPositiveInteger(int * data, int len);//�Զ������������
void AutoRandInteger(int * data, int len, int min);//�Զ������������(�и���)
void TestUnit();//������ݲ���

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
	//����������� �Ե׵��� �� �Զ����� ���������

	//�Ե׵�������(���һ����Ҷ�ӵ���)
	for (int i = LastNode(len); i >= 0; i--)
	{
		//�Զ����׹���(ĳ�������������ĳҶ��)
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
	int min = -50;//����������Сֵ

	//�и����ļ�������
	AutoRandPositiveInteger(data, len);
	cout << "��ͨ��������(ֻ������)" << endl;
	Display(data, len);
	CountingSourt(data, len);
	cout << "�����:" << endl;
	Display(data, len);

	//��ͨ��������
	AutoRandInteger(data, len, min);
	cout << "�и����ļ�������: " << endl;
	Display(data, len);
	NegativeCountingSourt(data, len, min);
	cout << "�����:" << endl;
	Display(data, len);

	//ð������
	AutoRandInteger(data, len, min);
	cout << "�и����ļ�������: " << endl;
	Display(data, len);
	BubbleSort(data, len);
	cout << "�����:" << endl;
	Display(data, len);

	//ѡ������
	AutoRandInteger(data, len, min);
	cout << "ѡ������: " << endl;
	Display(data, len);
	SelectSort(data, len);
	cout << "�����:" << endl;
	Display(data, len);

	//������
	AutoRandInteger(data, len, min);
	cout << "������: " << endl;
	Display(data, len);
	HeapSort(data, len);
	cout << "�����:" << endl;
	Display(data, len);

	//����Ϊ3��ʼ��ϣ������
	/*
	cout << "ϣ������" << endl;
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
		//ʹchildIndexָ��ϴ�ĺ���
		if (childIndex != len - 1 && data[childIndex + 1] > data[childIndex])
		{
			childIndex++;
		}
		//�͸��ڵ�Ƚ�
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
	int * count = new int[10]; //������
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //����d������
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //ÿ�η���ǰ��ռ�����
		//Display(count, 10);
		for (j = 0; j < len; j++)
		{
			k = (data[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
			count[k]++;
		}
		//Display(count, 10);
		cout << "count1:";
		Display(count, 10);
		for (j = 1; j < 10; j++)
		{
			count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ(��չһά����)
			//Display(count, 10);
		}
		cout << "count2:";
		Display(count, 10);
		for (j = len - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
		{
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
			cout << "count[k]-1:" << count[k] - 1 << "    data:" << data[j] << "   k:" << k << endl;
		}
		for (j = 0; j < len; j++) //����ʱ��������ݸ��Ƶ�data��
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
	int offset = abs(min);//������������Ҫ���ƫ����
	int max = data[0];
	for (int i = 0; i < len; i++)
	{
		if (data[i] > max)
		{
			max = data[i];
		}
	}
	max = max + 1 + offset; //max������ת�������±� + 1

	int * count = new int[max];
	int * supData = new int[len];

	//��ʼ��count
	for (int i = 0; i < max; i++)
	{
		count[i] = 0;
	}
	//ͳ��Ԫ�ظ���
	for (int i = 0; i < len; i++)
	{
		count[data[i] + 50] = count[data[i] + offset] + 1;
	}
	//����λ��
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

	//��ʼ��count
	for (int i = 0; i <= max; i++)
	{
		count[i] = 0;
	}
	//ͳ��Ԫ�ظ���
	for (int i = 0; i < len; i++)
	{
		count[data[i]] = count[data[i]] + 1;
	}
	//����λ��
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
	
	//����Ϊ3��ʼ��ϣ������
	
	cout << "ϣ������" << endl;
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
	int min = -50;//����������Сֵ
	//�������-50~50������
	srand((unsigned)time(NULL));
	for (i = 0; i < len; i++)
	{
		data[i] = rand() % 100;
	}
	/*
	cout << "��ͨ��������(ֻ������)" << endl;
	Display(data, len);
	CountingSourt(data, len);
	cout << "���������:" << endl;
	Display(data, len);
	*/
	//�������-50~50������
	srand((unsigned)time(NULL));
	for (i = 0; i < len; i++)
	{
		data[i] = rand() % 100 + min;
	}
	Display(data, len);
	cout << "�и����ļ�������: " << endl;
	NegativeCountingSourt(data, len, min);
	cout << "���������:" << endl;
	Display(data, len);
}

void BuildDown(int * data, int len, int rootIndex)
{
	int root = data[rootIndex];
	int childIndex = LeftChild(rootIndex);


	while (childIndex < len)
	{
		//ʹchildIndexָ��ϴ�ĺ���
		if (childIndex != len - 1 && data[childIndex + 1] > data[childIndex])
		{
			childIndex++;
		}
		//�͸��ڵ�Ƚ�
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
	int * count = new int[10]; //������
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //����d������
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //ÿ�η���ǰ��ռ�����
		//Display(count, 10);
		for (j = 0; j < len; j++)
		{
			k = (data[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
			count[k]++;
		}
		//Display(count, 10);
		cout << "count1:";
		Display(count, 10);
		for (j = 1; j < 10; j++)
		{
			count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ(��չһά����)
			//Display(count, 10);
		}
		cout << "count2:";
		Display(count, 10);
		for (j = len - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
		{
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
			cout << "count[k]-1:" << count[k] - 1 << "    data:" << data[j] << "   k:" << k << endl;
		}
		for (j = 0; j < len; j++) //����ʱ��������ݸ��Ƶ�data��
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
	int offset = abs(min);//������������Ҫ���ƫ����
	int max = data[0];
	for (int i = 0; i < len; i++)
	{
		if (data[i] > max)
		{
			max = data[i];
		}
	}
	max = max + 1 + offset; //max������ת�������±� + 1

	int * count = new int[max];
	int * supData = new int[len];

	//��ʼ��count
	for (int i = 0; i < max; i++)
	{
		count[i] = 0;
	}
	//ͳ��Ԫ�ظ���
	for (int i = 0; i < len; i++)
	{
		count[data[i] + 50] = count[data[i] + offset] + 1;
	}
	//����λ��
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

	//��ʼ��count
	for (int i = 0; i <= max; i++)
	{
		count[i] = 0;
	}
	//ͳ��Ԫ�ظ���
	for (int i = 0; i < len; i++)
	{
		count[data[i]] = count[data[i]] + 1;
	}
	//����λ��
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