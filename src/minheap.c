//
// Priority queue implemented as a binary heap.
//
#define PY_SSIZE_T_CLEAN
//#include <Python.h>
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
    MinHeap heap = malloc(sizeof(MinHeap));
    heap->el = malloc(capacity * sizeof(int));
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

void _sift_down(MinHeap h, int i) {
    // Code provided by GPT-4
    /*Prompt:
     *Here is my code. I am trying to implement _sift_down for a minheap in C. Write the code for _sift_down and give explanations for your choices along the way.
     *GPT-4: Recursive Function
     * Can you write a non-recursive implementation of it?
     * Code Below
     */
    while (1) {
        int smallest = i;
        int left = left_child(i);
        int right = right_child(i);

        // If left child is smaller than root
        if (left < h->tail && h->el[left] < h->el[smallest])
            smallest = left;

        // If right child is smaller than smallest so far
        if (right < h->tail && h->el[right] < h->el[smallest])
            smallest = right;

        // If the smallest item is not the root (i), swap and continue the loop
        if (smallest != i) {
            swap(&h->el[i], &h->el[smallest]);
            i = smallest;
        }
            // Otherwise, the heap property has been restored and we can break the loop
        else {
            break;
        }
    }
}

void minHeap_resize(MinHeap h){
    h->el = realloc(h->el, h->capacity * (125/100));
    h->capacity = h->capacity * (125/100);
}

void minHeap_delete(MinHeap h){
    free(h->el);
    free(h);
}

/* Insert an element in MinHeap.
 * returns 1 for success, 0 for failure (out of storage)
 */
int minHeap_insert(int value, MinHeap h) {
    if(h->tail > h->capacity){
        minHeap_resize(h);
        printf("resize\n");
        //return 0;
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
    int temp;
    temp = h->el[0];
    h->el[0] = h->el[h->tail-1];
    h->tail--;
    _sift_down(h, 0); // call sift_down here
    return temp;
}


