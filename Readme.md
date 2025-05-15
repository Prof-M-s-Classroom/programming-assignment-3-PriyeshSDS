[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/K_t6ffJX)
# Prim's Algorithm with Min Heap and Adjacency Matrix

## Author
Priyesh Patel

## Description
This program finds the mst of a graph using the prims algorithm. It uses a minheap to store the values and an adjancency matrix is used to store the graph.

## Files
- graph.h / graph.cpp
- heap.h / heap.cpp
- main.cpp (unchanged)
- README.md

## How to Compile and Run
This project was developed and tested in CLion.  
Run directly from the IDE.

## Time Complexity Analysis


| Operation            | Time Complexity   |
|----------------------|-------------------|
| Insert in MinHeap    |     O(logv)|
| Extract Min          |      O(logv)             |
| Decrease Key         |      O(logv)             |
| Prim’s MST Overall   |      O(V^2)           |

_Explain why your MST implementation has the above runtime._
Prims MSt overall is v^2 b/c the loop that checks all the neighbors is v^2 and to extract the min its logv to get it from a heap this is the same for insert in min heap and decrease key because of how the heap is structured.

## Assumptions
The input graph is connected and undirected
## Test Case Description

Input:  g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

The ouput of this is 
0 -- 1 (2)
1 -- 2 (3)
0 -- 3 (6)
1 -- 4 (5)
Total Cost: 16
Which i beleive is the correct ouput
## Test plan
I just used the example test input and it seems to work
