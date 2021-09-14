#include <stdio.h>
int main()
{
	int a[100100] = { 0 };
	int acnt = 0;
	int b[100100] = { 0 };
	int bcnt = 0;
	do
	{
		scanf("%d", &a[acnt]);
		acnt++;
	} while (a[acnt - 1] != -1);
	acnt--;
	do
	{
		scanf("%d", &b[bcnt]);
		bcnt++;
	} while (b[bcnt - 1] != -1);
	bcnt--;
	int i = 0;
	int j = 0;
	int res[10010] = { 0 };
	int cnt = 0;
	while (i < acnt && j < bcnt)//相同一起走，小值向前走
	{
		if (a[i] - b[j] == 0) {
			res[cnt++] = a[i];
			i++;
			j++;
		}
		else if (a[i] - b[j] > 0) {
			j++;
		}
		else
		{
			i++;
		}
	}
	if (cnt == 0) {
		printf("NULL");
		return 0;
	}
	for (int i = 0; i < cnt; i++)
	{
		printf("%d", res[i]);
		if (i != cnt - 1)
		{
			printf(" ");
		}
	}
	return 0;
}