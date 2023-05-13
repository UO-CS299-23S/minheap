//
// Priority queue implemented as a binary heap.
//

#include <stdio.h>
#include "minheap.h"

/* ---------------- */
/* Helper functions */
/* ---------------- */

/* Index of left child of node at index c */
static int left_child(int c) {
    return 1 + (2 * c);
}

/* Index of right child of node at index c */
static int right_child(int c) {
    return 2 + (2 * c);
}
/* Index of parent node at index c */

static int parent_node(int c) {
    return (c - 1) / 2;
}

/* --------------------- */
/* API functions         */
/* --------------------- */

/* Create a new empty MinHeap with capacity of m elements */
MinHeap minHeap_create(int capacity) {
    MinHeap heap = malloc(sizeof(MinHeap) + capacity * sizeof(int));
    heap->capacity = capacity;
    heap->tail = 0;

    return heap;
}
/* Prints the heap based on the size of tail */
void print_heap(MinHeap h){
    int i;
    printf("Heap is ");
    for(i = 0; i < h->tail; i++){
        printf("%d ", h->el[i]);
    }
    printf("\n");
}

void swap(int *a, int *b){
    //Swaps two variables
    int temp = *a;
    *a = *b;
    *b = temp;

}
/* Number of elements currently in MinHeap */
int minHeap_size(MinHeap h) {
    return h->tail;
}

void _sift_up(MinHeap h, int i){
    //printf("parent is %d, i is %d\n", h->el[parent_node(i)], i);
    while(i > 0 && h->el[i] < h->el[parent_node(i)]){

        swap(&h->el[i], &h->el[parent_node(i)]);

        i = parent_node(i);

    }
}

void _sift_down(MinHeap h, int i){ //FIXME
    /*Ended up not using it, probably performance gains for implementating instead of calling
    * sift_up on the whole tree
    */
}


/* Insert an element in MinHeap.
 * returns 1 for success, 0 for failure (out of storage)
 */
int minHeap_insert(int value, MinHeap h) {
    if(h->tail > h->capacity){
        printf("failed\n");
        return 0;
    }
    //printf("inserting %d at %d\n", value, h->tail);
    h->el[h->tail] = value;
    h->tail++;
    _sift_up(h, h->tail-1);
    //print_heap(h);
    return 1;
}

/* Get minimum value currently in minheap.
 * Returns 0 if minheap is empty.
 */
int minHeap_min(MinHeap h) {
    if(h->tail == 0){
        return 0;
    }
    return h->el[0];
}

/* Get and delete minimum element from MinHeap.
 */
int minHeap_extract(MinHeap h) {
    if(h->tail == 0){
        return 0;
    }
//    print_heap(h);
    int temp;
    temp = h->el[0];
    h->el[0] = h->el[h->tail-1];
//    printf("temp is %d\n", temp);
    h->tail--;
    //print_heap(h);
    _sift_up(h, h->tail-1);
    return temp;
}


