/*
ID : 0857
GMAIL : Umanskyvivian@gmail.com
*/
#include "Graph.hpp"
#include <stdexcept> // Include for std::invalid_argument

namespace ariel
{
    // Constructor implementation
    Graph::Graph()
        : isDirected(false), NegativeEdges(false)
    {
    }

    // Load graph from a given adjacency matrix
    void Graph::loadGraph(const std::vector<std::vector<int>> &matrix, bool directed)
    {
        if (matrix.empty())
        {
            throw std::invalid_argument("The adjacency matrix is empty.");
        }

        size_t size = matrix.size();
        for (size_t i = 0; i < size; ++i)
        {
            if (matrix[i].size() != size)
            {
                throw std::invalid_argument("The adjacency matrix must be square.");
            }

            for (size_t j = (directed ? 0 : i); j < size; ++j)
            {
                if ((i == j) && matrix[i][j] != 0)
                {
                    throw std::invalid_argument("No self-loops allowed.");
                }
                if (matrix[i][j] < 0)
                {
                    NegativeEdges = true;
                }
                if (!directed && matrix[i][j] != matrix[j][i])
                {
                    throw std::invalid_argument("Matrix must be symmetric for undirected graphs.");
                }
            }
        }

        // If validation is successful, update the graph state
        isDirected = directed;
        adjacencyMatrix = matrix;
    }

    // Print the graph in a readable format
    void Graph::printGraph() const
    {
        // Print the header with the number of vertices and edges
        std::cout << "Graph with " << adjacencyMatrix.size() << " vertices and " << countEdges() << " edges." << std::endl;
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
                if (!isDirected && i != j && adjacencyMatrix[j][i] != 0)
                {
                    edges++;
                }
                else
                {
                    if (adjacencyMatrix[i][j] != 0)
                    {
                        edges++;
                    }
                }
            }
        }
        return (edges); // Divide by 2 for undirected graphs
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
    bool Graph::getIsNegativeEdges() const
    {
        return NegativeEdges;
    }
} // namespace ariel
