//构造哈夫曼树，求出哈夫曼编码，压缩，解压，(思考题)
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

HTree HuffmanTree(int * w, int n);//构造哈夫曼树 w:权数组首地址, n:权值个数
char ** HuffmanCoding(HTree ht, int n);//生成哈夫曼编码,返回哈夫曼编码二维字符数组首地址 ht:HTree类型指针, n: 权个数
char * compress(char ** hfmCode, int n);//用哈夫曼编码压缩, hfmCode:哈夫曼编码串首地址, n:权值个数
char * deCompress(HTree ht, char * compCode, int len);//解压哈夫曼编码, ht:用来解压的树, compCode:压缩串, len:长度

int main() {
	int w[MAXSIZE], len = 0;
	printf("请输入权值个数x(x > 1):\n");
	scanf("%d", &len);
	
	for (int i = 0; i < len; i++){
		printf("请输入node:%d的权值:", i);
		scanf("%d", &w[i]);
	}

	int mlen = 2 * len - 1;//哈夫曼树节点数量2m - 1
	HTree rt = HuffmanTree(w, len);
	printf("哈夫曼树:\n");
	for (int i = 0; i < mlen; i++) {
		printf("node:%3d  weight:%3d  parent:%3d  lchild:%3d  rchild:%3d\n", i, rt[i].weight, rt[i].parent, rt[i].lchild, rt[i].rchild);
	}
	printf("哈夫曼编码:\n");
	char ** hfmCode = HuffmanCoding(rt, len);
	for (int i = 0; i < len; i ++) {
		printf("node.weight:%-3d huffmanCode:%s len:%d\n", w[i], hfmCode[i], strlen(hfmCode[i]));
	}

	char * compCode = compress(hfmCode, len);
	printf("压缩后:%s\n", compCode);
	char * decode = deCompress(rt, compCode, len);
	printf("解压后:%s\n", decode);
	
	
	return 0;
}

HTree HuffmanTree(int * w, int n) {
	int m, m1, m2, x1, x2, i, j;
	HTree ht;
	HNode * p;
	if (n <= 1) {
		return NULL;
	}
	m = 2 * n - 1;  //全部节点个数2m - 1
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
	char * cd; //当前码串
	int start, i, c, f; //f:节点序号, c:记录当前节点序号, start:开始叶子
	HC = (char **)malloc(n * sizeof(char *));//给指向码串的二级指针分配空间
	cd = (char *)malloc(n * sizeof(char));//给码串指针分配空间
	cd[n - 1 ] = '\0';
	for (i = 0; i < n; i++) {
		start = n - 1;
		//从叶子往根判断左右子树
		for (c = i, f = ht[i].parent; f != -1; c = f, f = ht[f].parent) {
			if (ht[f].lchild == c){
				cd[--start] = '0';
			}
			else {
				cd[--start] = '1';
			}
		}
		//逆向遍历回到根节点后, 从cd复制码串
		HC[i] = (char *)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
		//printf("%s\n", HC[i]);
	}
	free(cd);
	return HC;
}

char * compress(char ** hfmCode, int n){
	char * compressCode;//压缩字符串
	compressCode = (char *)malloc(n * sizeof(char));
	compressCode[n - 1 ] = '\0';

	for (int i = 0, offset = 0; i < n; i ++) {
		//拼接压缩字符串:
		strcpy(&compressCode[offset], hfmCode[i]);
		offset += strlen(hfmCode[i]);
	}
	
	return compressCode;
}

char * deCompress(HTree ht, char * compCode, int len){
	int mlen = 2 * len - 1, offset = 8, cx = 0;
	int a = 65;
	char * deCompCode = (char *)malloc(sizeof(char) * len);//解压串
	deCompCode[len] = '\0';
	//从根遍历压缩串 0左1右深入, 无左右就回溯
	for (int j = 0; j < strlen(compCode);) {
		//深入哈夫曼树
		for (int i = 0; i < len; i++){
			//深入左
			if (compCode[j] == '0') {
				//判断继续深入
				if (ht[offset].lchild != -1) {
					offset = ht[offset].lchild;//记录深入节点位置
					j++;
				}
				//找到对应编码叶子回溯
				if (ht[offset].lchild == -1){
					deCompCode[cx] = (char)(ht[offset].weight + 48);
					cx++;
					offset = 8;
					break;
				}
			}
			//深入右
			else if (compCode[j] == '1') {
				//判断继续深入
				if (ht[offset].rchild != -1) {
					offset = ht[offset].rchild;//记录深入节点位置
					j++;
				}
				//找到对应编码叶子回溯
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