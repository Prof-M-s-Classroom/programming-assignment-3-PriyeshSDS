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
        MinHeap minHeap(numVertices);

        // Set up the heap: everyone starts with infinite key, no parent
        for (int v = 0; v < numVertices; ++v) {
            parent[v] = -1;
            minHeap.insert(v, INT_MAX);
        }

        // Force vertex 0 to go first by setting its key to 0
        minHeap.decreaseKey(0, 0);

        // Keep grabbing the cheapest available node
        while (!minHeap.isEmpty()) {
            int u = minHeap.extractMin();

            // Check all its neighbors
            for (int v = 0; v < numVertices; ++v) {
                int weight = adjMatrix[u][v];

                // If there's a better edge to a node still in the heap, use it
                if (weight != INT_MAX && minHeap.isInMinHeap(v) && weight < minHeap.getKey(v)) {
                    parent[v] = u;
                    minHeap.decreaseKey(v, weight);
                }
            }
        }

        // Print the MST edges and total weight
        int totalCost = 0;
        for (int i = 1; i < numVertices; ++i) {
            if (parent[i] != -1) {
                int weight = adjMatrix[i][parent[i]];
                std::cout << parent[i] << " -- " << i << " (" << weight << ")\n";
                totalCost += weight;
            }
        }

        std::cout << "Total Cost: " << totalCost << std::endl;
        delete[] parent;
    }

private:
    int** adjMatrix;
    int numVertices;
};

#endif