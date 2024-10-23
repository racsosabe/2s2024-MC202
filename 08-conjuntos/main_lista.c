#include<stdio.h>
#include<assert.h>

#include "lista.h"

int search(list* L[], int n, long name) {
    for(int i = 0; i < n; i++) {
        if(L[i] -> name == name) return i;
    }
    return -1;
}

void clear_list(list* L[], int* n, long name) {
    int pos = search(L, *n, name);
    if(pos == -1) return;
    for(int i = pos; i + 1 < *n; i++) {
        list *carry = L[i];
        L[i] = L[i + 1];
        L[i + 1] = carry;
    }
    free_list(L[*n - 1]);
    *n -= 1;
}

int main() {
    char op[3];
    list *L[128];
    int cnt = 0;
    while(scanf("%s", op) == 1) {
        if(op[0] == 'c') {
            long A;
            scanf("%ld", &A);
            clear_list(L, &cnt, A);
            L[cnt++] = alloc_list(A);
        }
        else if(op[0] == 'i') {
            long A;
            int t;
            scanf("%ld %d", &A, &t);
            int pos = search(L, cnt, A);
            if(pos == -1) {
                printf("Error. Selected sets don't exist\nA: %d\n", pos);
                return 1;
            }
            for(int i = 0; i < t; i++) {
                long x;
                scanf("%ld", &x);
                insert(L[pos], x);
            }
        }
        else if(op[0] == 'r') {
            long A;
            int t;
            scanf("%ld %d", &A, &t);
            int pos = search(L, cnt, A);
            for(int i = 0; i < t; i++) {
                long x;
                scanf("%ld", &x);
                erase(L[pos], x);
            }
        }
        else if(op[0] == 'u') {
                long A, B, C;
                scanf("%ld %ld %ld", &A, &B, &C);
                clear_list(L, &cnt, A);
                int pos_b = search(L, cnt, B), pos_c = search(L, cnt, C);
                if(pos_b == -1 || pos_c == -1) {
                    printf("Error. Selected sets don't exist\nB: %d\nC: %d\n", pos_b, pos_c);
                    return 1;
                }
                L[cnt++] = alloc_list(A);
                insert_union(L[cnt - 1], L[pos_b], L[pos_c]);
        }
        else if(op[0] == 'n') {
            long A, B, C;
            scanf("%ld %ld %ld", &A, &B, &C);
            clear_list(L, &cnt, A);
            int pos_b = search(L, cnt, B), pos_c = search(L, cnt, C);
            if(pos_b == -1 || pos_c == -1) {
                printf("Error. Selected sets don't exist\nB: %d\nC: %d\n", pos_b, pos_c);
                return 1;
            }
            L[cnt++] = alloc_list(A);
            insert_intersection(L[cnt - 1], L[pos_b], L[pos_c]);
        }
        else if(op[0] == 'm') {
            long A, B, C;
            scanf("%ld %ld %ld", &A, &B, &C);
            clear_list(L, &cnt, A);
            int pos_b = search(L, cnt, B), pos_c = search(L, cnt, C);
            if(pos_b == -1 || pos_c == -1) {
                printf("Error. Selected sets don't exist\nB: %d\nC: %d\n", pos_b, pos_c);
                return 1;
            }
            L[cnt++] = alloc_list(A);
            insert_difference(L[cnt - 1], L[pos_b], L[pos_c]);
        }
        else if(op[0] == 'e') {
            long A, x;
            scanf("%ld %ld", &A, &x);
            int pos_a = search(L, cnt, A);
            if(pos_a == -1) {
                printf("Error. Selected sets don't exist\nA: %d\n", pos_a);
                return 1;
            }
            int found = search_element(L[pos_a], x);
            if(found) printf("%ld esta em C%ld\n", x, A);
            else printf("%ld nao esta em C%ld\n", x, A);
        }
        else if(op[0] == 'p') {
            long A;
            scanf("%ld", &A);
            int pos_a = search(L, cnt, A);
            if(pos_a == -1) {
                printf("Error. Selected sets don't exist\nA: %d\n", pos_a);
                return 1;
            }
            print(L[pos_a]);
        }
        else {
            for(int i = 0; i < cnt; i++) free_list(L[i]);
            break;
        }
    }
    return 0;
}