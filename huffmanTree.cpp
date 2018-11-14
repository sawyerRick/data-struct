#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXBIT 10
#define MAXVALUE 100
#define MAXSIZE 100
typedef struct {
	int weight;
	int parent, lchild, rchild;
}HNode, * HTree;

HTree HuffmanTree(int * w, int n);
char ** HuffmanCoding(HTree ht, int n);

int main() {
	
	int w[MAXSIZE];
	int len = 0;
	
	printf("������Ȩֵ����:\n");
	scanf("%d", &len);
	for (int i = 0; i < len; i++){
		printf("������node:%d��Ȩֵ:", i);
		scanf("%d", &w[i]);
	}
	
	int mlen = 2 * len - 1;//���������ڵ�����2m - 1 ;
	HTree rt = HuffmanTree(w, len);
	printf("��������:\n");
	for (int i = 0; i < mlen; i++) {
		printf("node:%3d  weight:%3d  parent:%3d  lchild:%3d  rchild:%3d\n", i, rt[i].weight, rt[i].parent, rt[i].lchild, rt[i].rchild);
	}
	printf("����������:\n");
	char ** hfmCode = HuffmanCoding(rt, len);
	for (int i = 0; i < len; i ++) {
		printf("node.weight:%-3d huffmanCode:%s\n", w[i], hfmCode[i]);
	}
	
	return 0;
}

HTree HuffmanTree(int * w, int n) {
	int m, m1, m2, x1, x2, i, j;
	HTree ht;
	HNode * p;
	if (n <= 1) {
		return NULL;
	}
	m = 2 * n - 1;  //ȫ���ڵ����2m - 1
	ht = (HNode *)malloc(m * sizeof(HNode));
	if (ht == NULL) {
		return ht;
	}
	for (p = ht, i = 0; i < n; ++i, ++p, ++w) {
		p->weight = *w;
		p->lchild = -1;
		p->rchild = -1;
		p->parent = -1;
	}
	for (; i < m; ++i, ++p) {
		p->weight = 0;
		p->lchild = -1;
		p->rchild = -1;
		p->parent = -1;
	}
	for (i = n; i < m; ++i) {
		m1 = m2 = MAXVALUE;
		x1 = x2 = 0;
		for (j = 0; j < i; ++j) {
			if (ht[j].parent == -1 && ht[j].weight < m1) {
				m2 = m1;
				x2 = x1;
				m1 = ht[j].weight;
				x1 = j;
			}
			else if (ht[j].parent == -1 && ht[j].weight < m2) {
				m2 = ht[j].weight;
				x2 = j;
			}
		}
		ht[x1].parent = i; 
		ht[x2].parent = i;
		ht[i].lchild = x1;
		ht[i].rchild = x2;
		ht[i].weight = m1 + m2;
	}
	return ht;
}

char ** HuffmanCoding(HTree ht, int n) {
	char ** HC;
	char * cd; //��ǰ�봮
	int start, i, c, f; //f:�ڵ����, c:��¼��ǰ�ڵ����, start:��ʼҶ��
	HC = (char **)malloc(n * sizeof(char *));//��ָ���봮�Ķ���ָ�����ռ�
	cd = (char *)malloc(n * sizeof(char));//���봮ָ�����ռ�
	cd[n - 1 ] = '\0';
	for (i = 0; i < n; i++) {
		start = n - 1;
		//��Ҷ�������ж���������
		for (c = i, f = ht[i].parent; f != -1; c = f, f = ht[f].parent) {
			if (ht[f].lchild == c){
				cd[--start] = '0';
			}
			else {
				cd[--start] = '1';
			}
		}
		//��������ص����ڵ��, ��cd�����봮
		HC[i] = (char *)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
		//printf("%s\n", HC[i]);
	}
	free(cd);
	return HC;
}