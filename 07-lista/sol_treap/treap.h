#pragma once

typedef struct TreapNode {
    double val;
    int cnt;
    unsigned int priority;
    int rev;
    struct TreapNode* left;
    struct TreapNode* right;
} node;

typedef struct Treap {
    node* root;
} treap;

typedef struct RNG {
    unsigned long long state;
} rng;

rng* alloc_generator();

unsigned int random(rng* generator, unsigned int range);

node* create_node(rng* generator, double x);

long cnt(node* T);

void update(node* t);

void push(node* t);

void split(node* t, node** l, node** r, long key, long add);

void merge(node** t, node* l, node* r);

void free_node(node* u);

treap* alloc_treap();

void free_treap(treap* T);

long size(treap* T);

void insert(treap* T, long p, double x, rng* generator);

void erase(treap* T, long p);

void inorder_traversal(node* root);

void print(treap* T);

void reverse(treap* T, long l, long r);

void move_block(treap* T, long l, long r, long p);