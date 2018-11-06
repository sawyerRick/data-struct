#include <stdio.h>
#include <stdlib.h>

//MAXSIZE太大处理较慢
//修改MAXSIZE可以处理任意个皇后问题
#define MAXSIZE 10
int check(int * q_ptr, int n);
void put(int * q_ptr, int n);
void display(int * q_ptr);

int sum = 0;

int main()
{
	printf("[+] %d皇后问题:\n", MAXSIZE);
	int queen[MAXSIZE];
	int i;
	put(queen, 0);
	printf("[+] %d个皇后一共有%d种方案...\n", MAXSIZE, sum);
}

void put(int * q_ptr, int n)
{
	int i = 0;
 	for (; i < MAXSIZE; i++)
	{
		q_ptr[n] = i;
		if (check(q_ptr, n)) //如果摆放合适n + 1  不合适 i + 1
		{
			if (n == MAXSIZE - 1) //如果全部摆好
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
		if (q_ptr[i] == q_ptr[n] || abs(q_ptr[i] - q_ptr[n]) == n - i)//判断位置冲突
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