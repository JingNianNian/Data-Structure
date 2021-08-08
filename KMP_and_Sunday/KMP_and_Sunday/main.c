#include <stdio.h>
#include <string.h>

#define MAXSIZE 100000
#pragma warning (disable:4996)
#pragma warning (disable:6031)
#pragma warning (disable:6011)
//base
int A = 0, B = 0;
char S[MAXSIZE];
char P[MAXSIZE];

int next[MAXSIZE];// KMP
int shift[MAXSIZE];// Sunday

void BF() {
	// QAQ so easy
}

int Sunday() {// ����BM�㷨
	int n = strlen(S);
	int m = strlen(P);
	
	// Ĭ��ֵ���ƶ�m+1λ
	for (int i = 0; i < MAXSIZE; i++) {
		shift[i] = m + 1;
	}

	// ģʽ��P��ÿ����ĸ���ֵ������±�
	// ����Ӧ����������ƥ�����ĩλ�ַ�����һλ�ַ��ƶ�����λ������Ҫ���ƶ�λ��
	for (int i = 0; i < m; i++) {
		shift[P[i]] = m - i;
	}

	// ģʽ����ʼλ��������������
	int s = 0;
	// ģʽ���Ѿ�ƥ�䵽��λ��
	int j;
	while (s <= n - m) {
		j = 0;
		while (S[s + j] == P[j]) {
			j++;
		}
		// ƥ��ɹ�
		if (j >= m) {
			printf("%d ", 1 + s);
		}
		// �ҵ������е�ǰ��ģʽ��ƥ�����ĩ�ַ�����һ���ַ�
		// ��ģʽ���г�������λ��
		// ����Ҫ��(ģʽ��ĩβ+1)�ƶ�����λ�õĲ���
		s += shift[S[s + m]];
	}
	//��δ���֣�return -1
	return -1;
}


//  0 1 2 3 4 5 6 7 8 9 10 1   2 3 4 5 6 7
//                                                         i
//  a b a b a b a b a b  a  b   c a b a b c 
// -1 0 1 2 3 4 5 6 7 8  9 10  0 1 2 3 4 0
//          i    
// a a a b a b a b
//-1 1 2 0 1 0 1 0
//        j
//  j n n n j n n n
// 0 0 0 0 1 2 3 4
void set_next() {
	next[0] = -1;
	next[1] = 0;
	int i = 1, j = 0;
	while(i < A) {
		if (j == -1 || P[i] == P[j]) next[++i] = ++j;
		else
		{
			if (j == next[j]) j = next[0];
			j = next[j];
		}
	}
}
void KMP(/*char* s, char* p*/) {
	int i = 0, j = 0;
	while (i < B) {
		if (S[i] == P[j]) {
			i++;
			j++;
		}
		else {
			if (j) j = next[j];
			else i++;
		}
		if (j == A)
		{
			printf("%d\n", i - j + 1);
			j = next[j];
		}
	}
}

int main() {
	// LuoGu P3375
	scanf("%s",S);
	scanf("%s",P);
	A = strlen(P);
	B = strlen(S);
	set_next();
	KMP();
	for (int i = 1; i <= A; i++) {
		printf("%d ", next[i]);
	}

	//Sunday();
}