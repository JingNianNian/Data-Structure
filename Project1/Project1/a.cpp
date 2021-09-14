#include <C++AllHeaderFiles.h>
#define MAXN 100010
#pragma warning(disable:4996)
using namespace std;
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


int main(){
	
} 
