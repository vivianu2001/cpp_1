#include "Graph.hpp"
#include <stdexcept> // Include for std::invalid_argument

namespace ariel
{
    // Constructor implementation
    Graph::Graph(bool directed) : isDirected(directed) {}

    // Load graph from a given adjacency matrix
    void Graph::loadGraph(const std::vector<std::vector<int>> &matrix, bool directed)
    {
        // Load the graph from the given adjacency matrix
        isDirected = directed;

        // Check if the matrix is empty
        if (matrix.empty())
        {
            adjacencyMatrix.clear();
            return;
        }

        // Check if the matrix is square
        size_t size = matrix.size();
        for (const auto &row : matrix)
        {
            if (row.size() != size)
            {
                throw std::invalid_argument("The adjacency matrix must be square.");
            }
        }

        // If the graph is undirected, check for symmetry
        if (!isDirected)
        {
            for (size_t i = 0; i < size; i++)
            {
                for (size_t j = 0; j < i; j++)
                { // Check only half as matrix should be symmetric
                    if (matrix[i][j] != matrix[j][i])
                    {
                        throw std::invalid_argument("Matrix must be symmetric for undirected graphs");
                    }
                }
            }
        }

        // Check for invalid weights
        for (const auto &row : matrix)
        {
            for (int weight : row)
            {
                if (weight < 0)
                {
                    throw std::invalid_argument("Weights must be non-negative.");
                }
            }
        }

        // Set the adjacency matrix
        adjacencyMatrix = matrix;
    }

    // Print the graph in a readable format
    void Graph::printGraph() const
    {
        // Print the header with the number of vertices and edges
        std::cout << "Graph with " << adjacencyMatrix.size() << " vertices and " << countEdges() << " edges." << std::endl;

        // Print the adjacency matrix
        for (const auto &row : adjacencyMatrix)
        {
            for (int val : row)
            {
                if (val == std::numeric_limits<int>::max())
                {
                    std::cout << "INF ";
                }
                else
                {
                    std::cout << val << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    int Graph::countEdges() const
    {
        int edges = 0;
        size_t size = adjacencyMatrix.size();
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = (isDirected ? 0 : i + 1); j < size; ++j)
            {
                // For directed graphs, count all non-zero edges
                // For undirected graphs, count only the upper triangular matrix
                if (!isDirected && i != j && adjacencyMatrix[j][i] != 0 && adjacencyMatrix[i][j] != std::numeric_limits<int>::max())
                {
                    edges++;
                }
                if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != std::numeric_limits<int>::max())
                {
                    edges++;
                }
            }
        }
        return (isDirected ? edges : edges / 2); // Divide by 2 for undirected graphs
    }

    // Accessor for the adjacency matrix
    const std::vector<std::vector<int>> &Graph::getAdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }

    // Check if the graph is directed
    bool Graph::getIsDirected() const
    {
        return isDirected;
    }
} // namespace ariel
