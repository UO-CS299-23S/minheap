//  Interface for minheap, a binary heap implementation
//  of a priority queue.
//
// This .h file defines the interface to our minheap.
// Initial straw dog(*) by M Young, please improve.

#ifndef MINHEAP_MINHEAP_H
#define MINHEAP_MINHEAP_H

struct S_MinHeap {
    int capacity;  // How many elements allocated
    int tail;      // Where the next element would be inserted
    int el[];      // Element buffer
};

typedef struct S_MinHeap* MinHeap;

// Functional API

/* Create a new empty MinHeap with capacity of m elements */
MinHeap minHeap_create(int capacity);

/* Number of elements currently in MinHeap */
int minHeap_size(MinHeap h);

/* Insert an element in MinHeap.
 * returns 1 for success, 0 for failure (out of storage)
 */
int minHeap_insert(int value, MinHeap h);

/* Get minimum value currently in minheap.
 * Returns 0 if minheap is empty.
 */
int minHeap_min(MinHeap h);

/* Get and delete minimum element from MinHeap.
 */
int minHeap_del(MinHeap h);


#endif //MINHEAP_MINHEAP_H

//(*) straw dog:  The term "strawman" is sometimes used for
// an initial proposal to start a discussion, with the
// intention that it be replaced or radically revised.
// "strawperson" is too clumsy as an ungendered alternative,
// but Laozi mentions burning sacrificial straw dogs in the
// Tao Te Ching.  I propose "straw dog" as a good substitute
// term for "strawman".
