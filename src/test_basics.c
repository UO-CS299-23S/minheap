//
// Mainly a sample.  You can add tests to this file or create
// additional test programs.   If you know  better ways to write
// test cases for C programs and C libraries, please show how.
//

#include "minheap.c"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void test_basic_create() {
    MinHeap h = minHeap_create(5);
    assert(h != NULL);
    minHeap_insert(7, h);
    minHeap_insert(5, h);
    minHeap_insert(9, h);
    assert(minHeap_size(h) == 3);
    assert(minHeap_extract(h) == 5);
    assert(minHeap_extract(h) == 7);
    assert(minHeap_min(h) == 9);
    assert(minHeap_extract(h) == 9);
    assert (minHeap_size(h) == 0);
    minHeap_insert(9, h);
    minHeap_insert(5, h);
    minHeap_insert(5, h);
    minHeap_insert(5, h);
    minHeap_insert(10, h);
    minHeap_insert(10, h);
    minHeap_insert(10, h);
    minHeap_insert(10, h);
    minHeap_insert(10, h);
    minHeap_insert(10, h);
    minHeap_insert(10, h);
    minHeap_insert(10, h);
    minHeap_insert(10, h);
    minHeap_insert(10, h);
    minHeap_insert(10, h);
    minHeap_insert(10, h);
    assert(minHeap_size(h) == 11);
    assert(minHeap_extract(h) == 5);
    minHeap_delete(h);

}

int main(int argc, char **argv) {
    test_basic_create();
    printf("Tested\n");
}
