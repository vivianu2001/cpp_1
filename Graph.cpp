#include "Graph.hpp"

namespace ariel
{
    Graph::Graph()
    {
        // Initialize the adjacency matrix as empty
    }

    void Graph::loadGraph(const std::vector<std::vector<int>> &adjacencyMatrix)
    {
        // Clear the existing adjacency matrix
        this->adjacencyMatrix.clear();

        // Copy the new adjacency matrix
        for (const auto &row : adjacencyMatrix)
        {
            this->adjacencyMatrix.push_back(row);
        }
    }

    void Graph::printGraph() const
    {
        int n = adjacencyMatrix.size();
        std::cout << "Graph with " << n << " vertices and " << n * (n - 1) / 2 << " edges." << std::endl;
        // Print the adjacency matrix
        for (const auto &row : adjacencyMatrix)
        {
            for (int weight : row)
            {
                std::cout << weight << " ";
            }
            std::cout << std::endl;
        }
    }

    const std::vector<std::vector<int>> &Graph::getAdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }

    // Implement other member functions here.
}
