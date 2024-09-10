#include<stdio.h>

int main() {
	int n, i;
	scanf("%d", &n);
	int last;
	int cnt = 1;
	scanf("%d", &last);
	for(i = 1; i < n; i++) {
		int x;
		scanf("%d", &x);
		if(last != x) cnt += 1;
		last = x;
	}
	printf("%d\n", cnt);
	return 0;
}
