// Algorithms.cpp
/*
ID : 322880857
GMAIL : Umanskyvivian@gmail.com
*/

#include "Algorithms.hpp"
#include <vector>
#include <queue>
#include <iostream>

namespace ariel
{

    bool Algorithms::isConnected(const Graph &g)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();
        std::vector<bool> visited(n, false);
        std::queue<int> q;
        q.push(0);
        visited[0] = true;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            for (int i = 0; i < n; ++i)
            {
                if (matrix[node][i] && !visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        for (bool v : visited)
        {
            if (!v)
                return false; // If any node is not visited, graph is not connected
        }
        return true;
    }

    std::string Algorithms::shortestPath(const Graph &g, int start, int end)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();
        std::vector<int> dist(n, -1);
        std::vector<int> prev(n, -1);
        std::queue<int> q;
        q.push(start);
        dist[start] = 0;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            for (int i = 0; i < n; ++i)
            {
                if (matrix[node][i] && dist[i] == -1)
                {
                    dist[i] = dist[node] + 1;
                    prev[i] = node;
                    q.push(i);
                }
            }
        }

        if (dist[end] == -1)
        {
            return "-1"; // No path found
        }

        // Reconstruct the shortest path
        std::string shortestPath = std::to_string(end);
        int current = end;
        while (current != start)
        {
            current = prev[current];
            shortestPath = std::to_string(current) + "->" + shortestPath;
        }

        return shortestPath;
    }

    bool Algorithms::isContainsCycle(const Graph &g)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();
        std::vector<bool> visited(n, false);
        std::vector<bool> recStack(n, false);

        for (int i = 0; i < n; ++i)
        {
            if (!visited[i] && isCycleUtil(matrix, i, visited, recStack))
            {
                return true;
            }
        }
        return false;
    }

    bool Algorithms::isCycleUtil(const std::vector<std::vector<int>> &matrix, int v, std::vector<bool> &visited, std::vector<bool> &recStack)
    {
        visited[v] = true;
        recStack[v] = true;

        for (int i = 0; i < static_cast<int>(matrix.size()); ++i)

        {
            if (matrix[v][i])
            {
                if (!visited[i] && isCycleUtil(matrix, i, visited, recStack))
                {
                    return true;
                }
                else if (recStack[i])
                {
                    return true;
                }
            }
        }
        recStack[v] = false;
        return false;
    }

    bool Algorithms::isBipartite(const Graph &g)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();
        std::vector<int> color(n, -1);
        std::queue<int> q;

        for (int i = 0; i < n; ++i)
        {
            if (color[i] == -1)
            {
                q.push(i);
                color[i] = 0;
                while (!q.empty())
                {
                    int u = q.front();
                    q.pop();
                    for (int v = 0; v < n; ++v)
                    {
                        if (matrix[u][v] && color[v] == -1)
                        {
                            color[v] = 1 - color[u];
                            q.push(v);
                        }
                        else if (matrix[u][v] && color[u] == color[v])
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    bool Algorithms::negativeCycle(const Graph &g)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();
        std::vector<int> dist(n, INT_MAX);

        for (int i = 0; i < n; ++i)
        {
            for (int u = 0; u < n; ++u)
            {
                for (int v = 0; v < n; ++v)
                {
                    if (matrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + matrix[u][v] < dist[v])
                    {
                        dist[v] = dist[u] + matrix[u][v];
                    }
                }
            }
        }

        for (int u = 0; u < n; ++u)
        {
            for (int v = 0; v < n; ++v)
            {
                if (matrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + matrix[u][v] < dist[v])
                {
                    return true; // Found a negative cycle
                }
            }
        }

        return false; // No negative cycle found
    }

} // namespace ariel
