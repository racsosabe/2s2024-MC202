#include<stdio.h>
#include<math.h>

int main() {
	int n, i;
	double EPS = 1e-9;
	double x_coelho, y_coelho, x_raposa, y_raposa, x, y;
	while(scanf("%d", &n) == 1) {
		scanf("%lf %lf %lf %lf", &x_coelho, &y_coelho, &x_raposa, &y_raposa);
		int found = 0;
		for(i = 0; i < n; i++) {
			scanf("%lf %lf", &x, &y);
			double d_coelho = 2 * hypot(x - x_coelho, y - y_coelho);
			double d_raposa = hypot(x - x_raposa, y - y_raposa);
			if(d_coelho <= d_raposa + EPS && !found) {
				printf("O coelho pode escapar pelo buraco (%.3lf,%.3lf).\n", x, y);
				found = 1;
			}
		}
		if(!found) {
			puts("O coelho nao pode escapar.");
		}
	}
	return 0;
}
