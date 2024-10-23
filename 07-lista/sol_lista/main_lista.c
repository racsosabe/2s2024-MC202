#include<stdio.h>

#include "lista.h"

int main() {
    char op[3];
    list *L = alloc_list();
    while(scanf("%s", op) == 1) {
        if(op[0] == 'c') {
            if(L != NULL) {
                free_list(L);
            }
            L = alloc_list();
        }
        else if(op[0] == 'i') {
            long p;
            double x;
            scanf("%ld %lf", &p, &x);
            insert(L, p, x);
        }
        else if(op[0] == 'r') {
            long p;
            scanf("%ld", &p);
            if(0 <= p && p < size(L)) {
                erase(L, p);
            }
        }
        else if(op[0] == 'p') {
            print(L);
        }
        else if(op[0] == 'v') {
            long l, r;
            scanf("%ld %ld", &l, &r);
            if(0 <= l && l <= r && r < size(L)) {
                reverse(L, l, r);
            }
        }
        else if(op[0] == 'x') {
            long l, r, p;
            scanf("%ld %ld %ld", &l, &r, &p);
            if(0 <= l && l <= r && r < size(L)) {
                move_block(L, l, r, p);
            }
        }
        else {
            free_list(L);
            break;
        }
    }
    return 0;
}