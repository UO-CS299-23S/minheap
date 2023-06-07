import minheap

# Create a MinHeap with capacity 10
heap = minheap.MinHeap(10)

# Insert elements into the MinHeap
heap.insert(5)
heap.insert(3)
heap.insert(8)
heap.insert(1)
heap.insert(7)

# Get the size of the MinHeap
size = heap.size()
print(f"Size of MinHeap: {size}")

# Get the minimum value in the MinHeap
min_value = heap.min()
print(f"Minimum value: {min_value}")

# Remove and return the minimum value from the MinHeap
removed_value = heap.delete()
print(f"Removed value: {removed_value}")

# Get the updated size of the MinHeap
size = heap.size()
print(f"Size of MinHeap after removal: {size}")
