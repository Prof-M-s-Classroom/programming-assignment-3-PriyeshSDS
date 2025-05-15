#ifndef HEAP_H
#define HEAP_H

#include <climits>
#include <algorithm>

class MinHeap {
public:
    MinHeap(int capacity) {
        this->capacity = capacity;
        size = 0;
        heapArray = new int[capacity];
        keyArray = new int[capacity];
        position = new int[capacity];
    }

    ~MinHeap() {
        delete[] heapArray;
        delete[] keyArray;
        delete[] position;
    }

    void insert(int vertex, int key) {
        keyArray[vertex] = key;
        int i = size;
        heapArray[i] = vertex;
        position[vertex] = i;
        size++;

        while (i != 0 && keyArray[heapArray[i]] < keyArray[heapArray[(i - 1) / 2]]) {
            std::swap(heapArray[i], heapArray[(i - 1) / 2]);
            position[heapArray[i]] = i;
            position[heapArray[(i - 1) / 2]] = (i - 1) / 2;
            i = (i - 1) / 2;
        }
    }

    void decreaseKey(int vertex, int newKey) {
        int i = position[vertex];
        keyArray[vertex] = newKey;

        // Bubble up this vertex by comparing its new key directly
        while (i != 0 && newKey < keyArray[heapArray[(i - 1) / 2]]) {
            heapArray[i] = heapArray[(i - 1) / 2];
            position[heapArray[i]] = i;
            i = (i - 1) / 2;
        }

        heapArray[i] = vertex;
        position[vertex] = i;
    }

    int extractMin() {
        if (size == 0) return -1;

        int root = heapArray[0];
        heapArray[0] = heapArray[size - 1];
        position[heapArray[0]] = 0;
        size--;
        minHeapify(0);
        return root;
    }

    void minHeapify(int i) {
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
    }

    bool isInMinHeap(int vertex) {
        return position[vertex] < size;
    }

    bool isEmpty() {
        return size == 0;
    }
    int getKey(int vertex) {
        return keyArray[vertex];
    }


private:
    int* heapArray;
    int* keyArray;
    int* position;
    int capacity;
    int size;
};

#endif
