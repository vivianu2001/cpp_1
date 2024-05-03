# 🧮 Graph Algorithms Implementation

**Author:** Vivian Umansky  
**Email:** Umanskyvivian@gmail.com

## Overview

👋 Welcome to my first assignment in CPP! This assignment involves creating a class to represent graphs and implementing various algorithms to operate on them.

## Files

- **Graph.cpp**: Contains the implementation of the `Graph` class for graph representation.
- **Algorithms.cpp**: Implements various graph algorithms including `isConnected`, `shortestPath`, `isContainsCycle`, `isBipartite`, and `negativeCycle`.
- **Demo.cpp**: Provides examples demonstrating the usage of implemented classes and algorithms.

## Graph Representation

🔍 Graphs are represented using an adjacency matrix, a square matrix where each cell indicates the presence or absence of an edge between two vertices. Diagonal elements represent self-loops, and non-diagonal elements represent edge connections.

## Implemented Algorithms

- **isConnected(g)**
  - **Implementation:** Utilizes BFS for undirected graphs and a series of DFS checks for directed graphs to ensure strong connectivity.
  - **Output:** Returns `true` if the graph is connected; otherwise, returns `false`.

### Shortest Path

- **shortestPath(g, start, end)**
  - **Implementation:** Uses Dijkstra's algorithm, leveraging a priority queue to manage the frontier vertices.
  - **Output:** Returns a string representing the path by listing vertices (e.g., "0->1->2") if a path exists; otherwise, returns "-1".

### Cycle Detection

- **isContainsCycle(g)**
  - **Implementation:** Applies DFS to explore the graph, using recursion to track visited nodes and detect backtracking.
  - **Output:** Returns "The cycle is: [cycle path]" if a cycle is detected (e.g., "0->1->2->0"); otherwise, returns "No cycle found."

### Bipartiteness Check

- **isBipartite(g)**
  - **Implementation:** Uses BFS to attempt coloring the graph, starting from uncolored vertices.
  - **Output:** If bipartite, returns a string detailing the groups (e.g., "The graph is bipartite: A={0, 2}, B={1}"); otherwise, returns "The graph is not bipartite."

### Negative Cycle Detection

- **negativeCycle(g)**
  - **Implementation:** Employs the Bellman-Ford algorithm, iterating over all vertices to relax edges repeatedly and check for changes beyond the expected iterations.
  - **Output:** Returns "Negative cycle found: [cycle path]" detailing the vertices in the negative cycle if one is found (e.g., "Negative cycle found: 0->1->2->0"); otherwise, states "No negative cycle found."


## Code Division

🧩 The code is divided into three main files:

- **Graph.cpp**: Contains the implementation of the `Graph` class.
- **Algorithms.cpp**: Contains implementations of various graph algorithms.
- **Demo.cpp**: Provides examples demonstrating the usage of implemented classes and algorithms.

## Usage

To use this project, follow these steps:

1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Build the project using the provided Makefile and it will run for you the tests:
   

That's it! You should now be able to run the demo program and the tests for this project.
