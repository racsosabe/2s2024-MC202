#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void build(int n, int bsize, int* a, int* blocks) {
	int i, id;
	for(id = 0; id * bsize < n; id++) {
		int l = id * bsize;
		int r = (l + bsize <= n ? l + bsize : n) - 1;
		blocks[id] = -1;
		for(i = l; i <= r; i++) {
			if(a[i] > blocks[id]) blocks[id] = a[i];
		}
	}
}

void update(int i, int x, int n, int bsize, int* blocks, int* a) {
	a[i] = x;
	int id = i / bsize;
	int l = id * bsize;
	int r = (l + bsize <= n ? l + bsize : n) - 1;
	blocks[id] = -1;
	for(i = l; i <= r; i++) {
		if(a[i] > blocks[id]) blocks[id] = a[i];
	}
}

int query(int l, int r, int bsize, int* a, int* blocks) {
	int res = -1;
	while(l <= r && l % bsize) {
		if(a[l] > res) res = a[l];
		l++;
	}
	while(l + bsize - 1 <= r) {
		if(blocks[l / bsize] > res) res = blocks[l / bsize];
		l += bsize;
	}
	while(l <= r) {
		if(a[l] > res) res = a[l];
		l++;
	}
	return res;
}

int main() {
	int n, i, j, k;
	scanf("%d", &n);
	int bsize = sqrt(n);
	int m = (n + bsize - 1) / bsize;
	int *a = (int*)malloc(n * sizeof(int));
	for(i = 0; i < n; i++) scanf("%d%*c", &a[i]);
	int *blocks = (int*)malloc(m * sizeof(int));
	build(n, bsize, a, blocks);
	char op;
	while(scanf("%c %d %d%*c", &op, &j, &k) == 3) {
		if(op == 'a') {
			update(j, k, n, bsize, blocks, a);
		}
		else {
			printf("%d\n", query(j, k, bsize, a, blocks));
		}
	}
	return 0;
}
