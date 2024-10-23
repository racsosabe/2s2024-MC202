#include<stdio.h>

#include "treap.h"

int main() {
    char op[3];
    treap *T = alloc_treap();
    rng *generator = alloc_generator();
    while(scanf("%s", op) == 1) {
        if(op[0] == 'c') {
            if(T != NULL) {
                free_treap(T);
            }
            T = alloc_treap();
        }
        else if(op[0] == 'i') {
            long p;
            double x;
            scanf("%ld %lf", &p, &x);
            insert(T, p, x, generator);
        }
        else if(op[0] == 'r') {
            long p;
            scanf("%ld", &p);
            if(0 <= p && p < size(T)) {
                erase(T, p);
            }
        }
        else if(op[0] == 'p') {
            print(T);
        }
        else if(op[0] == 'v') {
            long l, r;
            scanf("%ld %ld", &l, &r);
            if(0 <= l && l <= r && r < size(T)) {
                reverse(T, l, r);
            }
        }
        else if(op[0] == 'x') {
            long l, r, p;
            scanf("%ld %ld %ld", &l, &r, &p);
            if(0 <= l && l <= r && r < size(T)) {
                move_block(T, l, r, p);
            }
        }
        else {
            free_treap(T);
            break;
        }
        //printf("ENDED %s\n", op);
        //print(T);
    }
    return 0;
}