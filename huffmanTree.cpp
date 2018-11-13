#include <stdio.h>
#include <stdlib.h>


#define MAXBIT 10
#define MAXVALUE 100
typedef struct {
	int weight;
	int parent, lchild, rchild;
}HNode, * HTree;

HTree HuffmanTree(int * w, int n) {
	int m, m1, m2, x1, x2, i, j;
	HTree ht;
	HNode * p;
	if (n <= 1) {
		return NULL;
	}
	m = 2 * n - 1;  //m???
	ht = (HNode *)malloc(m * sizeof(HNode));
	if (ht == NULL) {
		return ht;
	}
	for (p = ht, i = 0; i < n; ++i, ++p, ++w) {
		p->weight = *w;
		p->lchild = -1;
		p->lchild = -1;
	}
	for (; i < m; ++i, ++p) {
		p->weight = 0;
		p->lchild = -1;
		p->rchild = -1;
		p->parent = -1;
	}
	for (i = n; i < m; ++i) {
		m1 = m2 = MAXVALUE;
		x1 = x1 = 0;
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

int main() {
	
	if (1) {
		printf("1");
	}
	else if (1) {
		printf("2");
	}

	return 0;
}