OB#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main() {
    int n;
    scanf("%d", &n);
    int m = n * (n + 1) / 2;
    double **a = (double**)malloc(n * sizeof(double**));
    double mean = 0;
    for(int i = 0; i < n; i++) {
        a[i] = (double*)malloc((i + 1) * sizeof(double));
        for(int j = 0; j <= i; j++) {
            scanf("%lf", &a[i][j]);
            mean += a[i][j];
        }
    }
    mean /= m;
    double stddev = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            stddev += 1.0L * (a[i][j] - mean) * (a[i][j] - mean);
        }
    }
    stddev = sqrt(stddev / m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            double z = (a[i][j] - mean) / stddev;
            printf("%.4lf%c", z, " \n"[j == i]);
        }
    }
    puts("");
    printf("%.4lf %.4lf\n", mean, stddev);
    for(int i = 0; i < n; i++) {
	free(a[i]);
    }
    free(a);
    return 0;
}
