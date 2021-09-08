#include <CAllHeaderFiles.h>
#define MAXN 100010
#pragma warning(disable:4996)
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5+10; 
inline int read() {
	int X=0;
	bool flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') flag=0;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		X=(X<<1)+(X<<3)+ch-'0';
		ch=getchar();
	}
	if(flag) return X;
	return ~(X-1);
}
inline void write(int x) {
	if (x < 0) x = ~x + 1, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

void merge(int* arr, int L, int M, int R) {
	int p1 = L, p2 = M + 1;
	int* t = (int*)calloc(R - L + 1, sizeof(int));
	int cnt = 0;
	while (p1<=M && p2 <= R)// 合并
	{
		t[cnt++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
	}
	while (p1 <= M)// if p1 余下
	{
		t[cnt++] = arr[p1++];
	}
	while (p2 <= R)// if p2 余下
	{
		t[cnt++] = arr[p2++];
	}
	for (int i = 0, j = L; i < cnt; i++, j++) // copy
	{
		arr[j] = t[i];
	}
}

void mergeSort(int* arr, int L, int R) {
	if (!(L == R)) {// 递归二分
		int mid = L + ((R - L) >> 1);
		mergeSort(arr, L, mid);
		mergeSort(arr, mid + 1, R);
		merge(arr, L, mid, R);
	}
}

int main(){
	int arr[5] = { 6,9,68,1,2 };
	mergeSort(arr, 0, 4);
	for (int i = 0; i < 5; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
} 
