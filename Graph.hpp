#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream> // Include for std::cout

namespace ariel
{
    class Graph
    {
    public:
        Graph(); // Constructor
        void loadGraph(const std::vector<std::vector<int>> &adjacencyMatrix);
        void printGraph() const;
        const std::vector<std::vector<int>> &getAdjacencyMatrix() const; // Declaration for getAdjacencyMatrix function
        // You can add other member functions and variables here as needed.
    private:
        std::vector<std::vector<int>> adjacencyMatrix;
    };
}

#endif // GRAPH_HPP
