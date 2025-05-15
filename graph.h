#ifndef GRAPH_H
#define GRAPH_H

#include <climits>
#include <iostream>
#include "heap.h"

class Graph {
public:
    Graph(int vertices) {
        numVertices = vertices;
        adjMatrix = new int*[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            adjMatrix[i] = new int[numVertices];
            for (int j = 0; j < numVertices; ++j) {
                adjMatrix[i][j] = (i == j) ? 0 : INT_MAX;
            }
        }
    }

    ~Graph() {
        for (int i = 0; i < numVertices; ++i) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }

    void addEdge(int u, int v, int weight) {
        if (u >= 0 && v >= 0 && u < numVertices && v < numVertices) {
            adjMatrix[u][v] = weight;
            adjMatrix[v][u] = weight;
        }
    }

    void primMST() {
        int* parent = new int[numVertices];
        int* key = new int[numVertices];
        MinHeap minHeap(numVertices);

        key[0] = 0;

        for (int v = 0; v < numVertices; ++v) {
            parent[v] = -1;
            minHeap.insert(v, key[v]);
        }


        while (!minHeap.isEmpty()) {
            int u = minHeap.extractMin();

            for (int v = 0; v < numVertices; ++v) {
                if (adjMatrix[u][v] != INT_MAX && minHeap.isInMinHeap(v) && adjMatrix[u][v] < key[v]) {
                    key[v] = adjMatrix[u][v];
                    parent[v] = u;
                    minHeap.decreaseKey(v, key[v]);
                }
            }
        }

        int totalCost = 0;
        for (int i = 1; i < numVertices; ++i) {
            if (parent[i] != -1) {
                std::cout << parent[i] << " -- " << i << " (" << adjMatrix[i][parent[i]] << ")\n";
                totalCost += adjMatrix[i][parent[i]];
            }
        }

        std::cout << "Total Cost: " << totalCost << std::endl;

        delete[] parent;
        delete[] key;
    }

private:
    int** adjMatrix;
    int numVertices;
};

#endif