#include <stdio.h>
#include <stdlib.h>

#define elemType int
elemType ** CreatTwoDimensional(int rowlen, int collen);//��malloc������ά���� return:����ָ��  rowlen:���� collen:����
elemType *** CreatThreeDimensional(int rowlen, int collen, int hight);//��malloc������ά���� return:����ָ�� rowlen:���� collen:���� hight:�߶�

int main()
{
	int * nums = (int *)malloc(4 * sizeof(int));
	elemType ** TwoDimensional = CreatTwoDimensional(3, 4);
	elemType *** ThreeDimensional = CreatThreeDimensional(5, 5, 5);
	
	return 0;
}

elemType ** CreatTwoDimensional(int rowlen, int collen)
{
	//����rowlen��
	elemType ** TwoDimensional = (elemType **)malloc(rowlen * sizeof(elemType));
	//����collen��
	for (int i = 0; i < rowlen; i++)
	{
		*(TwoDimensional + i) = (elemType *)malloc(collen * sizeof(elemType));
	}
	//��ʼ��0
	for (int i = 0; i < rowlen; i++)
	{
		for (int j = 0; j < collen; j++)
		{
			*(*(TwoDimensional + i) + j) = 0;
		}
	}
	//���
	for (int i = 0; i < rowlen; i++)
	{
		for (int j = 0; j < collen; j++)
		{
			printf("%d  ", *(*(TwoDimensional + i) + j));
		}
		printf("\n");
	}
	

	return TwoDimensional;
}

elemType *** CreatThreeDimensional(int rowlen, int collen, int hight)
{
	elemType *** ThreeDimensional;
	//�����߶�hight
	ThreeDimensional = (elemType ***)malloc(hight * sizeof(elemType **));
	//��������row
	for (int i = 0;i < rowlen; i++)
	{
		*(ThreeDimensional + i) = (elemType **)malloc(rowlen * sizeof(elemType *));
	}
	//��������collen
	for (int i = 0; i < rowlen; i++)
	{
		for (int j = 0; j < collen; j++)
		{
			*(*(ThreeDimensional + i) + j) = (elemType *)malloc(collen * sizeof(elemType));
		}
	}
	//��ʼ��0
	for (int i = 0; i < rowlen; i++) //hight
	{
		for (int j = 0; j < collen; j++) //rowlen
		{
			for (int k = 0; k < collen; k++) //collen
			{
				*(*(*(ThreeDimensional + i) + j) + k) = 0;
			}
		}
	}
	//���
	for (int i = 0; i < hight; i++) //hight
	{
		for (int j = 0; j < rowlen; j++) //rowlen
		{
			for (int k = 0; k < collen; k++) //collen
			{
				printf("%d  ", *(*(*(ThreeDimensional + i) + j) + k));
			}
			printf("\n");
		}
		printf("\n");
	}
	
	return ThreeDimensional;
}