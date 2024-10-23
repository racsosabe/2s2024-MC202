#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "lista.h"

void free_node(node* x) {
    if(x == NULL) return;
    free_node(x -> next);
    free(x);
}

list* alloc_list() {
    list *res = (list*)malloc(sizeof(list));
    if(res == NULL) return NULL;
    res -> head = NULL;
    res -> size = 0;
    return res;
}

long size(list* L) {
    return L ? L -> size : 0;
}

void free_list(list* L) {
    if(L == NULL) return;
    free_node(L -> head);
    free(L);
}

node* get_kth(node* head, long k) {
    if(k < 0) return NULL;
    node* ptr = head;
    for(long i = 0; i < k; i++) {
        ptr = ptr -> next;
    }
    return ptr;
}

void insert(list* L, long p, double x) {
    if(L == NULL) return;
    if(p > size(L)) p = size(L);
    node *cur = (node*)malloc(sizeof(node));
    cur -> val = x;
    L -> size += 1;
    if(p == 0) {    
        cur -> next = L -> head;
        L -> head = cur;
        return;
    }
    node *ptr = get_kth(L -> head, p - 1);
    cur -> next = ptr -> next;
    ptr -> next = cur;
}

void erase(list* L, long p) {
    if(p == 0) {
        node *new_head = L -> head -> next;
        free(L -> head);
        L -> head = new_head;
        L -> size -= 1;
        return;
    }
    node *ptr = get_kth(L -> head, p - 1);
    node *cur_node = ptr -> next;
    ptr -> next = ptr -> next -> next;
    assert(cur_node != NULL);
    free(cur_node);
}

void print(list* L) {
    if(L == NULL || size(L) == 0) {
        puts("");
        return;
    }
    node *ptr = L -> head;
    while(ptr) {
        printf("%.2lf ", ptr -> val);
        ptr = ptr -> next;
    }
    puts("");
}

void recursive_reverse(node* l, node* r) {
	if(l == r) return;
	recursive_reverse(l -> next, r);
	l -> next -> next = l;
}

void reverse(list* L, long l, long r) {
    if(l == r) return;
    node* first = get_kth(L -> head, l);
    node* last = get_kth(L -> head, r);
	node* prev_first = get_kth(L -> head, l - 1);
	node* next_last = get_kth(L -> head, r + 1);
	recursive_reverse(first, last);
	if(l > 0) prev_first -> next = last;
    else L -> head = last;
	first -> next = next_last;
}

void move_block(list* L, long l, long r, long p) {
    if(p > size(L)) p = size(L);
    if(l <= p && p <= r) return;
    if(r + 1 == p) return;
    //if(r - l + 1 > p) return;
    node* prev_l = get_kth(L -> head, l - 1);
    node* pos_l = get_kth(L -> head, l);
    node* prev_p = get_kth(L -> head, p - 1);
    node* pos_p = get_kth(L -> head, p);
    node* pos_r = get_kth(L -> head, r);
    node* nxt_r = get_kth(L -> head, r + 1);
    if(p < l) {
        if(prev_p == NULL) {
            L -> head = pos_l;
        }
        else {
            prev_p -> next = pos_l;
        }
        pos_r -> next = pos_p;
        prev_l -> next = nxt_r;
    }
    else {
        if(prev_l == NULL) {
            L -> head = nxt_r;
        }
        else {
            prev_l -> next = nxt_r;
        }
        prev_p -> next = pos_l;
        pos_r -> next = pos_p;
    }
}

