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
        int* parent = new int[numVertices];   // parent[i] = the vertex that connects i to the MST
        int* key = new int[numVertices];      // key[i] = weight of the cheapest edge to i
        MinHeap minHeap(numVertices);         // custom min heap to track the lowest-key vertex

        // Initialize keys to INT_MAX and parents to -1
        for (int v = 0; v < numVertices; ++v) {
            key[v] = INT_MAX;
            parent[v] = -1;
        }

        // Start from vertex 0
        key[0] = 0;

        // Insert all vertices with their current key values
        for (int v = 0; v < numVertices; ++v) {
            minHeap.insert(v, key[v]);
        }

        // Build the MST
        while (!minHeap.isEmpty()) {
            int u = minHeap.extractMin();  // Get the vertex with the lowest key

            // Check all neighbors of u
            for (int v = 0; v < numVertices; ++v) {
                int weight = adjMatrix[u][v];

                // If there's an edge, v is still in heap, and this edge is better than what we had
                if (weight != INT_MAX && minHeap.isInMinHeap(v) && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    minHeap.decreaseKey(v, key[v]);
                }
            }
        }

        // Print the MST and compute total cost
        int totalCost = 0;
        for (int i = 1; i < numVertices; ++i) {
            if (parent[i] != -1) {
                std::cout << parent[i] << " -- " << i << " (" << key[i] << ")\n";
                totalCost += key[i];
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