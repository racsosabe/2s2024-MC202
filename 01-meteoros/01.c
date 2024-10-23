#include<stdio.h>

int main() {
	int a, b, c, d;
	int caso = 1;
	while(scanf("%d %d %d %d", &a, &b, &c, &d) == 4) {
		if(a == 0 && b == 0 && c == 0 && d == 0) break;
		int n;
		scanf("%d", &n);
		int x, y, i, cnt = 0;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			if(a <= x && x <= c && d <= y && y <= b) cnt += 1;
		}
		printf("Teste %d\n%d\n\n", caso++, cnt);
	}
	return 0;
}
