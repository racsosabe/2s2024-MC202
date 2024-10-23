#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "dequef.h"


/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef* df_alloc(long capacity, double factor) {
   assert(capacity >= 1);
   assert(factor > 1.0);
   if(capacity < 1 || factor <= 1.0) return NULL; // Invalid parameters
   dequef *deque = (dequef*)malloc(sizeof(dequef));
   if(deque == NULL) return deque;
   deque -> cap = deque -> mincap = capacity;
   deque -> data = (float*)malloc(capacity * sizeof(float));
   if(deque -> data == NULL) return NULL;
   deque -> factor = factor;
   deque -> first = deque -> size = 0;
   return deque;
}



/**
  Release a dequef and its data.
**/
void df_free(dequef* D) {
   free(D -> data);
   free(D);
}



/**
   The size of the deque.
**/
long df_size(dequef* D) {
   return D ? D -> size : -1;
}

/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef* D, float x) {
   if(D -> size == D -> cap) {
      int new_cap = D -> size * D -> factor;
      if(new_cap == D -> size) return 0;
      float *new_data = (float*)malloc(new_cap * sizeof(float));
      for(int i = 0; i < D -> size; i++) new_data[i] = D -> data[(D -> first + i) % D -> size]; // Re-indexing to first = 0
      new_data[D -> size] = x;
      free(D -> data); // Releasing the original pointer
      D -> first = 0;
      D -> size += 1;
      D -> cap = new_cap;
      D -> data = new_data;
   }
   else {
      D -> data[(D -> first + D -> size) % D -> cap] = x;
      D -> size += 1;
   }
   return 1;
}



/**
   Remove a float from the end of D and return it.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   It returns the float removed from D.
   What happens if D is empty before the call?
**/
float df_pop(dequef* D) {
   if(D -> size == 0) {
      exit(1);
   }
   float res = D -> data[(D -> first + D -> size - 1) % D -> cap];
   D -> size -= 1;
   int bound = D -> cap / D -> factor / D -> factor;
   if(bound < D -> size) return res;
   int new_size = D -> cap / D -> factor;
   int new_capacity = D -> mincap >= new_size ? D -> mincap : new_size;
   float *new_data = (float*)malloc(new_capacity * sizeof(float));
   for(int i = 0; i < D -> size; i++) {
      new_data[i] = D -> data[(D -> first + i) % D -> cap];
   }
   D -> data = new_data;
   D -> first = 0;
   D -> cap = new_capacity;
   return res;
}



/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef* D, float x) {
   if(D -> size == D -> cap) {
      int new_cap = D -> cap * D -> factor;
      if(new_cap == D -> cap) return 0;
      float *new_data = (float*)malloc(new_cap * sizeof(float));
      new_data[0] = x;
      for(int i = 0; i < D -> size; i++) new_data[i + 1] = D -> data[(D -> first + i) % D -> size]; // Re-indexing to first = 0
      free(D -> data); // Releasing the original pointer
      D -> first = 0;
      D -> size += 1;
      D -> cap = new_cap;
      D -> data = new_data;
   }
   else {
      D -> first -= 1;
      if(D -> first == -1) D -> first = D -> cap - 1;
      D -> data[D -> first] = x;
      D -> size += 1;
   }
   return 1;
}



/**
   Remove a float from the beginning of D and return it.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   It returns the float removed from D.
   What happens if D is empty before the call?
**/
float df_eject(dequef* D) {
   if(D -> size == 0) {
      exit(1);
   }
   float res = D -> data[D -> first];
   D -> first += 1;
   if(D -> first == D -> cap) D -> first = 0;
   D -> size -= 1;
   int bound = D -> cap / D -> factor / D -> factor;
   if(bound < D -> size) return res;
   int new_size = D -> cap / D -> factor;
   int new_capacity = D -> mincap >= new_size ? D -> mincap : new_size;
   float *new_data = (float*)malloc(new_capacity * sizeof(float));
   for(int i = 0; i < D -> size; i++) {
      new_data[i] = D -> data[(D -> first + i) % D -> cap];
   }
   D -> data = new_data;
   D -> first = 0;
   D -> cap = new_capacity;
   return res;
}



/**
   Return D[i].

   If i is not in [0,|D|-1]] what happens then?
**/
float df_get(dequef* D, long i) {
   if(i < 0 || D -> size <= i) {
      exit(1);
   }
   return D -> data[(D -> first + i) % D -> cap];
}



/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] what happens then?
**/
void df_set(dequef* D, long i, float x) {
   if(i < 0 || D -> size <= i) {
      exit(1);
   }
   D -> data[(D -> first + i) % D -> cap] = x;
}



/**
   Print the elements of D in a single line.
**/
void df_print(dequef* D) {
   printf("deque (%ld):", D -> size);
   int at = D -> first;
   for(int i = 0; i < D -> size; i++) {
      printf(" %.1f", D -> data[at++]);
      if(at == D -> cap) at = 0;
   }
   puts("");
}
