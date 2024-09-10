#include<stdio.h>
#include<stdlib.h>

int main() {
    int n, m;
    int caso = 1;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0) break;
        int **a = (int**)malloc(n * sizeof(int*));
        for(int i = 0; i < n; i++) {
            a[i] = (int*)malloc(m * sizeof(int));
            for(int j = 0; j < m; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        int dx, dy;
        int X = 0, Y = 0;
        while(scanf("%d %d", &dy, &dx) == 2) {
            if(dx == 0 && dy == 0) break;
            X += (n - dx % n) % n;
            if(X >= n) X -= n;
            Y += (dy % m + m) % m;
            if(Y >= m) Y -= m;
        }
        printf("Teste %d\n", caso++);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                printf("%d%c", a[(i + n - X) % n][(j + m - Y) % m], " \n"[j + 1 == m]);
            }
        }
        puts("");
    }
    return 0;
}
