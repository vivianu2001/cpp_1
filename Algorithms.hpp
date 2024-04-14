#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>
#include <iostream> // Include for std::cout and std::endl

namespace ariel
{
    namespace Algorithms
    {
        bool isConnected(const Graph &g);
        std::string shortestPath(const Graph &g, int start, int end);
        bool isContainsCycle(const Graph &g);
        std::string isBipartite(const Graph &g);
        void negativeCycle(const Graph &g);
    }
}

#endif // ALGORITHMS_HPP
