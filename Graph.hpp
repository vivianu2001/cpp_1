#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <limits> // Include for std::numeric_limits
#include <iostream>

namespace ariel
{
    class Graph
    {
    private:
        std::vector<std::vector<int>> adjacencyMatrix; // Store the adjacency matrix
        bool isDirected;

    public:
        // Constructor to initialize a directed or undirected graph
        Graph(bool directed = false);

        // Load the adjacency matrix into the graph, with checks for proper structure
        void loadGraph(const std::vector<std::vector<int>> &matrix ,bool directed);

        // Print the graph to standard output
        void printGraph() const;

        // Get a constant reference to the adjacency matrix
        const std::vector<std::vector<int>> &getAdjacencyMatrix() const;

        // Check if the graph is directed
        bool getIsDirected() const;

    private:
        // Count the number of edges in the graph
        int countEdges() const;
    };

} // namespace ariel

#endif // GRAPH_HPP
