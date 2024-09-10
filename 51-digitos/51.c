#include<stdio.h>

int main() {
	int l, r;
	scanf("%d %d", &l, &r);
	int cnt = 0;
	for(int i = l; i <= r; i++) {
		int frec[10];
		for(int j = 0; j < 10; j++) frec[j] = 0;
		int x = i;
		int valid = 1;
		while(x > 0) {
			int d = x % 10;
			if(frec[d]) {
				valid = 0;
				break;
			}
			frec[d] = 1;
			x /= 10;
		}
		cnt += valid;
	}
	printf("%d\n", cnt);
	return 0;
}
