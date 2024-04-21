// Graph.cpp
/*
ID : 322880857
GMAIL : Umanskyvivian@gmail.com
*/
#include "Graph.hpp"
#include <iostream> // Include iostream header file for std::cout

namespace ariel
{

    void Graph::loadGraph(const std::vector<std::vector<int>> &adjacencyMatrix)
    {
        this->adjacencyMatrix = adjacencyMatrix;
    }

    void Graph::printGraph() const
    {
        for (const auto &row : adjacencyMatrix)
        {
            for (int val : row)
            {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }

    const std::vector<std::vector<int>> &Graph::getAdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }

} // namespace ariel
