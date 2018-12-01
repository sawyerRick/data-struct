//�������������������������룬ѹ������ѹ��(˼����)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVALUE 100
#define MAXSIZE 100
typedef struct {
	int weight;
	int parent, lchild, rchild;
}HNode, * HTree;

typedef struct {
	char vertex;
	int weight;
}Table;

HTree HuffmanTree(int * w, int n);//����������� w:Ȩ�����׵�ַ, n:Ȩֵ����
char ** HuffmanCoding(HTree ht, int n);//���ɹ���������,���ع����������ά�ַ������׵�ַ ht:HTree����ָ��, n: Ȩ����
char * compress(char ** hfmCode, int n);//�ù���������ѹ��, hfmCode:���������봮�׵�ַ, n:Ȩֵ����
char * deCompress(HTree ht, char * compCode, int len);//��ѹ����������, ht:������ѹ����, compCode:ѹ����, len:����

int main() {
	int w[MAXSIZE], len = 0;
	printf("������Ȩֵ����x(x > 1):\n");
	scanf("%d", &len);
	
	for (int i = 0; i < len; i++){
		printf("������node:%d��Ȩֵ:", i);
		scanf("%d", &w[i]);
	}

	int mlen = 2 * len - 1;//���������ڵ�����2m - 1
	HTree rt = HuffmanTree(w, len);
	printf("��������:\n");
	for (int i = 0; i < mlen; i++) {
		printf("node:%3d  weight:%3d  parent:%3d  lchild:%3d  rchild:%3d\n", i, rt[i].weight, rt[i].parent, rt[i].lchild, rt[i].rchild);
	}
	printf("����������:\n");
	char ** hfmCode = HuffmanCoding(rt, len);
	for (int i = 0; i < len; i ++) {
		printf("node.weight:%-3d huffmanCode:%s len:%d\n", w[i], hfmCode[i], strlen(hfmCode[i]));
	}

	char * compCode = compress(hfmCode, len);
	printf("ѹ����:%s\n", compCode);
	char * decode = deCompress(rt, compCode, len);
	printf("��ѹ��:%s\n", decode);
	
	
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

char * compress(char ** hfmCode, int n){
	char * compressCode;//ѹ���ַ���
	compressCode = (char *)malloc(n * sizeof(char));
	compressCode[n - 1 ] = '\0';

	for (int i = 0, offset = 0; i < n; i ++) {
		//ƴ��ѹ���ַ���:
		strcpy(&compressCode[offset], hfmCode[i]);
		offset += strlen(hfmCode[i]);
	}
	
	return compressCode;
}

char * deCompress(HTree ht, char * compCode, int len){
	int mlen = 2 * len - 1, offset = 8, cx = 0;
	int a = 65;
	char * deCompCode = (char *)malloc(sizeof(char) * len);//��ѹ��
	deCompCode[len] = '\0';
	//�Ӹ�����ѹ���� 0��1������, �����Ҿͻ���
	for (int j = 0; j < strlen(compCode);) {
		//�����������
		for (int i = 0; i < len; i++){
			//������
			if (compCode[j] == '0') {
				//�жϼ�������
				if (ht[offset].lchild != -1) {
					offset = ht[offset].lchild;//��¼����ڵ�λ��
					j++;
				}
				//�ҵ���Ӧ����Ҷ�ӻ���
				if (ht[offset].lchild == -1){
					deCompCode[cx] = (char)(ht[offset].weight + 48);
					cx++;
					offset = 8;
					break;
				}
			}
			//������
			else if (compCode[j] == '1') {
				//�жϼ�������
				if (ht[offset].rchild != -1) {
					offset = ht[offset].rchild;//��¼����ڵ�λ��
					j++;
				}
				//�ҵ���Ӧ����Ҷ�ӻ���
				if (ht[offset].rchild == -1){
					deCompCode[cx] = (char)(ht[offset].weight + 48);
					cx++;
					offset = 8;
					break;
				}
			}
		}
	}

	return deCompCode;
}