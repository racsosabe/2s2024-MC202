#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "treap.h"
#define MAX 4294967296

rng* alloc_generator() {
    rng *generator = (rng*)malloc(sizeof(rng));
    generator -> state = 0;
    return generator;
}

unsigned int random(rng* generator, unsigned int range) {
    generator -> state = (generator -> state * 1664525 + 1013904223) & (MAX - 1);
    return (generator -> state * range) / MAX;
}

node* create_node(rng* generator, double x) {
    node *cur = (node*)malloc(sizeof(node));
    cur -> val = x;
    cur -> cnt = 1;
    cur -> rev = 0;
    cur -> priority = random(generator, 1000000000);
    cur -> left = cur -> right = NULL;
    return cur;
}

long cnt(node* T) {
    return T ? T -> cnt : 0;
}

void update(node* t) {
    if(t) {
        t -> cnt = cnt(t -> left) + cnt(t -> right) + 1;
        if(t -> rev) {
            node* carry = t -> right;
            t -> right = t -> left;
            t -> left = carry;
            t -> left -> rev ^= 1;
            t -> right -> rev ^= 1;
            t -> rev = 0;
        }
    }
}

void push(node* t) {
    if(t && t -> rev) {
        node* carry = t -> right;
        t -> right = t -> left;
        t -> left = carry;
        if(t -> left) {
            t -> left -> rev ^= 1;
        }
        if(t -> right) {
            t -> right -> rev ^= 1;
        }
        t -> rev = 0;
    }
}

void split(node* t, node** l, node** r, long key, long add) {
    if(t == NULL) {
        *l = *r = NULL;
        return;
    }
    push(t);
    long cur = add + cnt(t -> left) + 1;
    if(cur <= key) {
        split(t -> right, &t -> right, r, key, cur);
        update(t);
        *l = t;
    }
    else {
        split(t -> left, l, &t -> left, key, add);
        update(t);
        *r = t;
    }
}

void print_node_info(node* cur) {
    if(cur == NULL) {
        puts("NODE IS NULL");
        return;
    }
    puts("NODE INFO:");
    printf("VALUE: %.2lf\n", cur -> val);
    printf("CNT: %d\n", cur -> cnt);
    printf("REV LAZY TAG: %d\n", cur -> rev);
    printf("PRIORITY: %u\n", cur -> priority);
    printf("LEFT: %p\n", (void*)cur -> left);
    printf("RIGHT: %p\n", (void*)cur -> right);
    printf("OWN DIRECTION: %p\n", (void*)cur);
}

void merge(node** t, node* l, node* r) {
    if(l == NULL) {
        *t = r;
        return;
    }
    if(r == NULL) {
        *t = l;
        return;
    }
    push(l);
    push(r);
    if(l -> priority > r -> priority) {
        merge(&l -> right, l -> right, r);
        update(l);
        *t = l;
    }
    else {
        merge(&r -> left, l, r -> left);
        update(r);
        *t = r;
    }
}

void free_node(node* u) {
    if(u == NULL) return;
    free_node(u -> left);
    free_node(u -> right);
    free(u);
}

treap* alloc_treap() {
    treap *res = (treap*)malloc(sizeof(treap));
    res -> root = NULL;
    return res;
}

void free_treap(treap* T) {
    free_node(T -> root);
    free(T);
}

long size(treap* T) {
    return cnt(T -> root);
}

void insert(treap* T, long p, double x, rng* generator) {
    node *l = NULL, *r = NULL;
    split(T -> root, &l, &r, p, 0);
    node *cur = create_node(generator, x);
    merge(&T -> root, l, cur);
    merge(&T -> root, T -> root, r);
}

void erase(treap* T, long p) {
    node *l = NULL, *m = NULL, *r = NULL;
    split(T -> root, &l, &m, p, 0);
    split(m, &m, &r, 1, 0);
    if(m != NULL) free_node(m);
    merge(&T -> root, l, r);
}

void inorder_traversal(node* root) {
    if(root == NULL) return;
    push(root);
    inorder_traversal(root -> left);
    printf("%.2lf ", root -> val);
    inorder_traversal(root -> right);
}

void print(treap* T) {
    inorder_traversal(T -> root);
    puts("");
}

void reverse(treap* T, long l, long r) {
    node *left_side, *middle_side, *right_side;
    split(T -> root, &middle_side, &right_side, r + 1, 0);
    split(middle_side, &left_side, &middle_side, l, 0);
    if(middle_side != NULL) middle_side -> rev ^= 1;
    merge(&T -> root, left_side, middle_side);
    merge(&T -> root, T -> root, right_side);
}

void move_block(treap* T, long l, long r, long p) {
    if(l <= p && p <= r) return;
    if(r + 1 == p) return;
    if(p < l) {
        node *left_side, *middle_side, *right_side, *prev_p, *p_block;
        split(T -> root, &middle_side, &right_side, r + 1, 0);
        split(middle_side, &left_side, &middle_side, l, 0);
        split(left_side, &prev_p, &p_block, p, 0);
        merge(&T -> root, prev_p, middle_side);
        merge(&T -> root, T -> root, p_block);
        merge(&T -> root, T -> root, right_side);
    }
    else {
        node *left_side, *middle_side, *right_side, *prev_p, *p_block;
        split(T -> root, &middle_side, &right_side, r + 1, 0);
        split(middle_side, &left_side, &middle_side, l, 0);
        split(right_side, &prev_p, &p_block, p - r - 1, 0);
        merge(&T -> root, left_side, prev_p);
        merge(&T -> root, T -> root, middle_side);
        merge(&T -> root, T -> root, p_block);
    }
}