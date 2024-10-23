#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "lista.h"

node* create_node(long x) {
    node* res = (node*)malloc(sizeof(node));
    res -> val = x;
    res -> prev = res -> next = NULL;
    return res;
}

void free_node(node* x) {
    if(x == NULL) return;
    free_node(x -> next);
    free(x);
}

list* alloc_list(long name) {
    list *res = (list*)malloc(sizeof(list));
    if(res == NULL) return NULL;
    res -> head = NULL;
    res -> size = 0;
    res -> name = name;
    return res;
}

void free_list(list* L) {
    if(L == NULL) return;
    free_node(L -> head);
    free(L);
}

void insert(list* L, long x) {
    if(L == NULL) return;
    if(L -> head == NULL) {
        node* cur = create_node(x);
        L -> head = cur;
        return;
    }
    node* ptr = L -> head;
    while(ptr && ptr -> val < x) {
        ptr = ptr -> next;
    }
    if(ptr != NULL && ptr -> val == x) return; // x already exists
    node* cur = create_node(x);
    if(ptr == NULL) { // There is no element >= x, so it must go to the end
        ptr = L -> head;
        while(ptr -> next) {
            ptr = ptr -> next;
        }
        ptr -> next = cur;
        cur -> prev = ptr;
        return;
    }
    if(ptr -> prev == NULL) { // All the elements are >= x, so it must go to the beginning
        cur -> next = ptr;
        ptr -> prev = cur;
        L -> head = cur;
        return;
    }
    // We have at least one element < x and one element >= x
    node* prev_x = ptr -> prev;
    prev_x -> next = cur;
    cur -> prev = prev_x;
    ptr -> prev = cur;
    cur -> next = ptr;
}

void erase(list* L, long x) {
    if(L == NULL) return;
    node* ptr = L -> head;
    while(ptr && ptr -> val < x) {
        ptr = ptr -> next;
    }
    if(ptr == NULL) return; // There is no element >= x
    if(ptr -> val != x) return; // There is no x
    if(L -> head == ptr) { // If x is the first position, head must go forward
        L -> head = L -> head -> next;
        if(L -> head != NULL) {
            L -> head -> prev = NULL;
        }
    }
    else {
        node* prev_x = ptr -> prev;
        node* next_x = ptr -> next;
        if(next_x != NULL) {
            prev_x -> next = next_x;
            next_x -> prev = prev_x;
        }
        else {
            prev_x -> next = NULL;
        }
    }
    free(ptr);
}

void print(list* L) {
    printf("C%ld = {", L -> name);
    node* ptr = L -> head;
    while(ptr) {
        printf("%ld", ptr -> val);
        ptr = ptr -> next;
        if(ptr) printf(", ");
    }
    puts("}");
}

void insert_union(list* a, list* b, list* c) {
    node* tail = NULL;
    node* ptr_c = c -> head;
    for(node* ptr_b = b -> head; ptr_b; ptr_b = ptr_b -> next) {
        while(ptr_c && ptr_c -> val < ptr_b -> val) {
            node* cur = create_node(ptr_c -> val);
            if(tail == NULL) {
                a -> head = tail = cur;
            }
            else {
                tail -> next = cur;
                cur -> prev = tail;
                tail = cur;
            }
            ptr_c = ptr_c -> next;
        }
        node* cur = create_node(ptr_b -> val);
        if(tail == NULL) {
            a -> head = tail = cur;
        }
        else {
            tail -> next = cur;
            cur -> prev = tail;
            tail = cur;
        }
        if(ptr_c && ptr_c -> val == ptr_b -> val) ptr_c = ptr_c -> next;
    }
    while(ptr_c) {
        node* cur = create_node(ptr_c -> val);
        if(tail == NULL) {
            a -> head = tail = cur;
        }
        else {
            tail -> next = cur;
            cur -> prev = tail;
            tail = cur;
        }
        ptr_c = ptr_c -> next;
    }
}

void insert_intersection(list* a, list* b, list* c) {
    node* tail = NULL;
    node* ptr_c = c -> head;
    for(node* ptr_b = b -> head; ptr_b; ptr_b = ptr_b -> next) {
        while(ptr_c && ptr_c -> val < ptr_b -> val) {
            ptr_c = ptr_c -> next;
        }
        if(ptr_c == NULL) return;
        if(ptr_b -> val != ptr_c -> val) continue;
        node* cur = create_node(ptr_b -> val);
        if(tail == NULL) {
            a -> head = tail = cur;
        }
        else {
            tail -> next = cur;
            cur -> prev = tail;
            tail = cur;
        }
    }
}

void insert_difference(list* a, list* b, list* c) {
    node* tail = NULL;
    node* ptr_c = c -> head;
    for(node* ptr_b = b -> head; ptr_b; ptr_b = ptr_b -> next) {
        while(ptr_c && ptr_c -> val < ptr_b -> val) {
            ptr_c = ptr_c -> next;
        }
        if(ptr_c && ptr_c -> val == ptr_b -> val) continue;
        node* cur = create_node(ptr_b -> val);
        if(tail == NULL) {
            a -> head = tail = cur;
        }
        else {
            tail -> next = cur;
            cur -> prev = tail;
            tail = cur;
        }
    }
}

int search_element(list* L, long x) {
    if(L == NULL) return 0;
    node* ptr = L -> head;
    while(ptr && ptr -> val < x) {
        ptr = ptr -> next;
    }
    return ptr && ptr -> val == x ? 1 : 0;
}