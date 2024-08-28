#include<stdio.h>

void swap(int *x, int *y) {
	int c = *x;
	*x = *y;
	*y = c;
}

int main() {
	int a, b, c, d;
	int caso = 1;
	while(scanf("%d %d %d %d", &a, &b, &c, &d) == 4) {
		if(a == 0 && b == 0 && c == 0 && d == 0) break;
		if(a > c) swap(&a, &c);
		if(b > d) swap(&b, &d);
		int n;
		scanf("%d", &n);
		int x, y, i, cnt = 0;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			if(a <= x && x <= c && b <= y && y <= d) cnt += 1;
		}
		printf("Teste %d\n%d\n\n", caso++, cnt);
	}
	return 0;
}
