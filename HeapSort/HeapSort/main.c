#include <CAllHeaderFiles.h>
#define MAXN 100010
#pragma warning(disable:4996)
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 10;
inline int read() {
	int X = 0;
	bool flag = 1;
	char ch = getchar();
	while (ch < '0' || ch>'9') {
		if (ch == '-') flag = 0;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		X = (X << 1) + (X << 3) + ch - '0';
		ch = getchar();
	}
	if (flag) return X;
	return ~(X - 1);
}
inline void write(int x) {
	if (x < 0) x = ~x + 1, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

void swap(int* arr, int indexA, int indexB) {
	int temp = arr[indexA];
	arr[indexA] = arr[indexB];
	arr[indexB] = temp;
}

void heapinsert(int* arr, int val, int* heapsize) {
	int index = *heapsize;
	arr[index] = val;
	(*heapsize)++;
	while (arr[index] > arr[(index - 1) / 2])
	{
		swap(arr, index, (index - 1) / 2);
		index = (index - 1) / 2;
	}
}

void heapify(int* arr, int index, int heapsize) {
	if (index * 2 + 1 < heapsize)
	{
		int maxchild = index * 2 + 2 < heapsize ?
			arr[index * 2 + 1] < arr[index * 2 + 2] ?
			index * 2 + 2
			: index * 2 + 1
			: index * 2 + 1;
		while (index * 2 + 1 < heapsize && arr[index] < arr[maxchild])
		{
			swap(arr, index, maxchild);
			index = maxchild;
			maxchild = index * 2 + 2 < heapsize ?
				arr[index * 2 + 1] < arr[index * 2 + 2] ?
				index * 2 + 2
				: index * 2 + 1
				: index * 2 + 1;
		}
	}
}
/// <summary>
/// 堆排序（升序）
/// </summary>
/// <param name="arr">排序起始位置</param>
/// <param name="length">排序元素数量</param>
void heapSort(int* arr, int length) {
	if (length > 1) {
		int heapsize = 0;
		for (int i = 0; i < length; i++) {
			heapinsert(arr, arr[i], &heapsize);
		}
		swap(arr, 0, --heapsize);
		while (heapsize) {
			heapify(arr, 0, heapsize);
			swap(arr, 0, --heapsize);
		}
	}
}

int main() {
	int a[5] = { 9,6,2,8,4 };
	int* b = &a[2];
	heapSort(&a[2], 3); // 部分排序
	for (int i = 0; i < 5; i++)
	{
		printf("%d ", a[i]);
	}
	return 0;
}
