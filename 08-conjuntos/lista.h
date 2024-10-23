
#pragma once

typedef struct ListNode {
    long val;
    struct ListNode* next;
    struct ListNode* prev;
} node;

node* create_node(long x);

void free_node(node* x);

typedef struct List {
    long name;
    long size;
    node* head;
} list;

list* alloc_list(long name);

void free_list(list* L);

void insert(list* L, long x);

void erase(list* L, long x);

void print(list* L);

void insert_union(list* a, list* b, list* c);

void insert_intersection(list* a, list* b, list* c);

void insert_difference(list* a, list* b, list* c);

int search_element(list* L, long x);