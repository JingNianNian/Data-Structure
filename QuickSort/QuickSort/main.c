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

void quickSort(int* arr, int L, int R) {
	if (L < R) {
		int num = arr[(R + L) / 2];
		int ledge = L - 1;
		int redge = R + 1;
		int i = L;
		while (i < redge)
		{
			if (arr[i] < num) {
				int temp = arr[i];
				arr[i] = arr[ledge + 1];
				arr[ledge + 1] = temp;
				ledge++;
				i++;
			}
			else if (arr[i] == num)
			{
				i++;
			}
			else {
				int temp = arr[i];
				arr[i] = arr[redge - 1];
				arr[redge - 1] = temp;
				redge--;
			}
			for (int j = L; j <= R; j++)
			{
				printf("%d ", arr[j]);
			}
			printf("\n");
		}
		quickSort(arr, L, ledge);
		quickSort(arr, redge, R);
	}
}

int main(){
	int n = 0;
	scanf("%d", &n);
	int* a = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	quickSort(a, 0, n - 1);
	return 0; 
} 
