#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 100
int initString(char ** S, char ** T);
int bruteForceMatch(char * S, char * T);

int main()
{
	char * S = NULL;
	char * T = NULL;
	while(!initString(&S, &T))
	{
		initString(&S, &T);
	}
	bruteForceMatch(S, T);
	free(S);
	free(T);

	return 0;
}

int initString(char ** S, char ** T)
{
	*S = (char *)malloc(MAXSIZE * sizeof(char));
	*T = (char *)malloc(MAXSIZE * sizeof(char));
	printf("[+] 请输入主串:");
	gets(*S);
	printf("[+] 请输入模式串:");
	gets(*T);
	if(strlen(*S) > strlen(*T))
	{
		printf("[*] 输入成功...\n");
		return 1;
	}
	else
	{
		printf("[!] 输入失败...请检查串长度...\n");
		return 0;
	}
}

int bruteForceMatch(char * S, char * T)
{
	int i, j, temp;

	for(i = 0; i < strlen(S); i++)
	{
		temp = i;
		for(j = 0; j < strlen(T);)
		{
			if(S[i] == T[j])
			{
				j++;
				i++;
				if(j == strlen(T))
				{
					printf("[!] 成功匹配模式串!!!\n");
					return 1;
				}
			}
			else
			{
				break;
			}
			
		}
		i = temp;
	}
	printf("[!] 匹配模式串失败!!!\n");
	return 0;
}
