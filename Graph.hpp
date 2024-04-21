// Graph.hpp
/*
ID : 322880857
GMAIL : Umanskyvivian@gmail.com
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

namespace ariel
{

    class Graph
    {
    private:
        std::vector<std::vector<int>> adjacencyMatrix;

    public:
        void loadGraph(const std::vector<std::vector<int>> &adjacencyMatrix);
        void printGraph() const;
        const std::vector<std::vector<int>> &getAdjacencyMatrix() const; // Declaration of getAdjacencyMatrix function
    };

} // namespace ariel

#endif // GRAPH_HPP
