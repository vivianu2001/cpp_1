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
        static bool isStronglyConnected(const Graph &g); // Add this declaration
        static std::string shortestPath(const Graph &g, int start, int end);

        static std::string isContainsCycle(const Graph &g);
        static std::string isBipartite(const Graph &g);
        static std::string negativeCycle(const Graph &g);

    private:
        static bool isCycleUtil(const std::vector<std::vector<int>> &matrix, int v, std::vector<bool> &visited, std::vector<int> &cyclePath, std::vector<bool> &recStack, int parent);
        static void dfs(const std::vector<std::vector<int>> &matrix, std::vector<bool> &visited, int node); // Add this declaration
    };
}

#endif /* ALGORITHMS_HPP */
