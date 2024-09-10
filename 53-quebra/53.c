#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_A 200001

int main() {
    int n, i;
    scanf("%d", &n);
    int L[MAX_A];
    int R[MAX_A];
    memset(L, -1, sizeof L);
    memset(R, -1, sizeof R);
    char *letter = (char*)malloc((n + 1) * sizeof(int));
    int *l = (int*)malloc(n * sizeof(int));
    int *r = (int*)malloc(n * sizeof(int));
    for(i = 0; i < n; i++) {
        scanf("%d %c %d", &l[i], &letter[i], &r[i]);
        L[l[i]] = i;
        R[r[i]] = i;
    }
    int start = -1;
    for(i = 0; i < n; i++) {
        if(R[l[i]] == -1) {
            if(start != -1) {
                printf("Error. There are at least two possible starts.\n");
                return 1;
            }
            start = i;
        }
    }
    if(start == -1) {
        printf("Error. There is no possible start.\n");
        return 1;
    }
    while(start != -1) {
        putchar(letter[start]);
        start = L[r[start]];
    }
    puts("");
    return 0;
}