// Algorithms.hpp
/*
ID : 322880857
GMAIL : Umanskyvivian@gmail.com
*/

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>

namespace ariel
{
    class Algorithms
    {
    public:
        static bool isConnected(const Graph &g);
        static std::string shortestPath(const Graph &g, int start, int end);
        static bool isContainsCycle(const Graph &g);
        static bool isBipartite(const Graph &g);
        static bool negativeCycle(const Graph &g);

    private:
        static bool isCycleUtil(const std::vector<std::vector<int>> &matrix, int v, std::vector<bool> &visited, std::vector<bool> &recStack);
    };
}

#endif /* ALGORITHMS_HPP */
