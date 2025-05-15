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
            if (v == 0)
                minHeap.insert(v, 0);        // start node gets key 0
            else
                minHeap.insert(v, INT_MAX);  // others get infinity
        }


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

        int totalCost = 0;
        for (int i = 0; i < numVertices; ++i) {
            if (parent[i] != -1 && parent[i] != i) {  // skip self-loops or unconnected nodes
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