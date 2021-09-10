#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
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
/// <summary>
/// 获取数字num的第digitNum位数字，若digitNum == 0，则返回总位数
/// </summary>
/// <param name="num"> 所求数字</param>
/// <param name="digitNum"> 第 i 位数字的值</param>
/// <returns></returns>
int getDigit(int num, int digitNum) {
	if (digitNum)
	{
		int res = num;
		res /= (digitNum == 1 ? 1 : (int)pow(10, digitNum - 1));
		return res % 10;
	}
	else
	{
		char digits[15] = { 0 };
		sprintf(digits, "%d", num);
		//itoa(num, digits, 10);  // Unix 中的 stdlib.h 不存在 itoa() 函数
		return (int)strlen(digits);
	}
}

void radixSort(int* arr, int length) {
	int max = 0;
	int* bucket = (int*)calloc(length, sizeof(int));
	for (int i = 0; i < length; i++)
	{
		max = arr[i] > max ? arr[i] : max;
	}
	int maxdigit = getDigit(max, 0);
	for (int i = 1; i <= maxdigit; i++)
	{
		int radix[10] = { 0 };
		for (int j = 0; j < length; j++)
		{
			radix[getDigit(arr[j], i)]++;
		}
		for (int k = 1; k < 10; k++) {
			radix[k] += radix[k - 1];
		}
		for (int o = length - 1; o >= 0; o--)
		{
			int dig = getDigit(arr[o], i);
			bucket[--radix[dig]] = arr[o];
		}
		for (int z = 0; z < length; z++)
		{
			arr[z] = bucket[z];
		}
	}
}

int main() {

	return 0;
}