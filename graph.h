#ifndef GRAPH_H
#define GRAPH_H

class Graph {
public:
    Graph(int vertices) {
        numVertices = vertices;
        adjMatrix = new int*[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            adjMatrix[i] = new int[numVertices];
            for (int j = 0; j < numVertices; ++j) {
                if (i == j)
                    adjMatrix[i][j] = 0;
                else
                    adjMatrix[i][j] = -1;
            }
        }
    };
    ~Graph() {
        for (int i = 0; i < numVertices; ++i) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }

    void addEdge(int u, int v, int weight){
        if (u >= 0 && v >= 0 && u < numVertices && v < numVertices) {
            adjMatrix[u][v] = weight;
            adjMatrix[v][u] = weight;
        }
    }
    void primMST() {

        // Must print MST edges and total weight
    }

private:
    int** adjMatrix;
    int numVertices;
};

#endif