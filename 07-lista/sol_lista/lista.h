
#pragma once

typedef struct ListNode {
    double val;
    struct ListNode* next;
} node;

void free_node(node* u);

typedef struct List {
    long size;
    node* head;
} list;


list* alloc_list();

long size(list* L);

void free_list(list* L);

node* get_kth(node* head, long k);

void insert(list* L, long p, double x);

void erase(list* L, long p);

void print(list* L);

void recursive_reverse(node* l, node* r);

void reverse(list* L, long l, long r);

void move_block(list* L, long l, long r, long p);
