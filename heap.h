#ifndef HEAP_H
#define HEAP_H

class MinHeap {
public:
    MinHeap(int capacity);
    ~MinHeap();
    void insert(int vertex, int key) {
        heapArray[size] = vertex;
        keyArray[vertex] = key;
        position[vertex] = size;
        size++;


    };

    int extractMin() {
        if (size == 0)
            return -1;

        int root = heapArray[0];

        heapArray[0] = heapArray[size - 1];
        position[heapArray[0]] = 0;
        size--;
        minHeapify(0);

        return root;
    };

    void decreaseKey(int vertex, int newKey) {
        keyArray[vertex] = newKey;
        int i = position[vertex];
    };
    bool isInMinHeap(int vertex) {
        return position[vertex] < size;
    };
    bool isEmpty() {
        return size == 0;
    };

private:
    int* heapArray;        // Heap of vertex indices
    int* keyArray;         // Corresponding key values
    int* position;         // Maps vertex to its position in heap
    int capacity;
    int size;

    void minHeapify(int idx) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && keyArray[heapArray[left]] < keyArray[heapArray[smallest]])
            smallest = left;

        if (right < size && keyArray[heapArray[right]] < keyArray[heapArray[smallest]])
            smallest = right;

        if (smallest != i) {
            std::swap(heapArray[i], heapArray[smallest]);
            position[heapArray[i]] = i;
            position[heapArray[smallest]] = smallest;
            minHeapify(smallest);
        }
    };
};

#endif