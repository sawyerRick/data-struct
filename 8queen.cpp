#include <stdio.h>
#include <stdlib.h>

//MAXSIZE̫�������
//�޸�MAXSIZE���Դ���������ʺ�����
#define MAXSIZE 10
int check(int * q_ptr, int n);
void put(int * q_ptr, int n);
void display(int * q_ptr);

int sum = 0;

int main()
{
	printf("[+] %d�ʺ�����:\n", MAXSIZE);
	int queen[MAXSIZE];
	int i;
	put(queen, 0);
	printf("[+] %d���ʺ�һ����%d�ַ���...\n", MAXSIZE, sum);
}

void put(int * q_ptr, int n)
{
	int i = 0;
 	for (; i < MAXSIZE; i++)
	{
		q_ptr[n] = i;
		if (check(q_ptr, n)) //����ڷź���n + 1  ������ i + 1
		{
			if (n == MAXSIZE - 1) //���ȫ���ں�
			{
				display(q_ptr);
				return;
			}
			put(q_ptr, n + 1);
		}
	}
	return;
}

int check(int * q_ptr, int n)
{
	int i = 0;
	for (; i < n; i++)
	{
		if (q_ptr[i] == q_ptr[n] || abs(q_ptr[i] - q_ptr[n]) == n - i)//�ж�λ�ó�ͻ
		{
			return 0;
		}
	}
	return 1;
}

void display(int * q_ptr) 
{
	int i;
	for (i = 0; i < MAXSIZE; i++)
	{
		printf("(%d,%d) ", i, q_ptr[i]);
	}
	sum++;
	printf("\n");
}