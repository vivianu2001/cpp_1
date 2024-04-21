# Graph Algorithms Implementation

**Author:** Vivian Umansky  
**Email:** Umanskyvivian@gmail.com  

## Overview

This my first assignment in CPP involves creating a class to represent graphs and implementing various algorithms to operate on them. The graph is represented using an adjacency matrix, and the implemented algorithms include determining connectivity, finding the shortest path, detecting cycles, checking bipartiteness, and identifying negative cycles.

## Files

- **Graph.cpp**: Contains the implementation of the `Graph` class for graph representation.
- **Algorithms.cpp**: Implements various graph algorithms including `isConnected`, `shortestPath`, `isContainsCycle`, `isBipartite`, and `negativeCycle`.
- **Demo.cpp**: Provides examples demonstrating the usage of implemented classes and algorithms.

## Graph Representation

Graphs are represented using an adjacency matrix, a square matrix where each cell indicates the presence or absence of an edge between two vertices. Diagonal elements represent self-loops, and non-diagonal elements represent edge connections.

## Implemented Algorithms

1. **isConnected(g)**:
   - Determines if the given graph `g` is connected.
   - Returns 1 if the graph is connected, otherwise returns 0.

2. **shortestPath(g, start, end)**:
   - Finds the shortest path between the start and end vertices in the graph `g`.
   - Returns the path as a sequence of vertices if exists, otherwise returns -1.

3. **isContainsCycle(g)**:
   - Detects if the given graph `g` contains any cycles.
   - Returns 1 if a cycle exists, otherwise returns 0.

4. **isBipartite(g)**:
   - Checks if the graph `g` can be partitioned into two sets such that no two vertices within the same set are adjacent.
   - Returns the partitioning of the graph if bipartite, otherwise returns 0.

5. **negativeCycle(g)**:
   - Identifies if the given graph `g` contains a negative cycle.
   - Prints the negative cycle if exists, otherwise indicates that no negative cycle is present.

## Code Division

The code is divided into three main files:

- **Graph.cpp**: Contains the implementation of the `Graph` class.
- **Algorithms.cpp**: Contains implementations of various graph algorithms.
- **Demo.cpp**: Provides examples demonstrating the usage of implemented classes and algorithms.

## Usage

