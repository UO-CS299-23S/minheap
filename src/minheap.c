//
// Priority queue implemented as a binary heap.
//

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

/* --------------------- */
/* API functions         */
/* --------------------- */

/* Create a new empty MinHeap with capacity of m elements */
MinHeap minHeap_create(int capacity) {
    return (MinHeap) 0;   // FIXME
}

/* Number of elements currently in MinHeap */
int minHeap_size(MinHeap h) {
    return 0;  // FIXME
}

/* Insert an element in MinHeap.
 * returns 1 for success, 0 for failure (out of storage)
 */
int minHeap_insert(int value, MinHeap h) {
    return 0;  // FIXME
}

/* Get minimum value currently in minheap.
 * Returns 0 if minheap is empty.
 */
int minHeap_min(MinHeap h) {
    return 0;  // FIXME
}

/* Get and delete minimum element from MinHeap.
 */
int minHeap_del(MinHeap h) {
    return 0;  // FIXME
}
