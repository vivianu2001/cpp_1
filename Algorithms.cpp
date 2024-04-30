#include "Algorithms.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <climits> // For INT_MAX

namespace ariel
{
    bool Algorithms::isConnected(const Graph &g)
    {
        if (g.getIsDirected())
        {
            // Use the algorithm for directed graphs
            return isStronglyConnected(g);
        }
        else
        {
            // Use the algorithm for undirected graphs
            const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
            int n = matrix.size();
            std::vector<bool> visited(n, false);
            std::queue<int> q;

            int start = -1;
            for (int i = 0; i < n; ++i)
            {
                if (!matrix[i].empty())
                {
                    start = i;
                    break;
                }
            }

            if (start == -1)
                return true; // Empty graph is considered connected

            q.push(start);
            visited[start] = true;

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
    }

    bool Algorithms::isStronglyConnected(const Graph &g)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();

        // Perform DFS from each vertex to check for strong connectivity
        for (int i = 0; i < n; ++i)
        {
            std::vector<bool> visited(n, false);
            dfs(matrix, visited, i);

            // If any vertex cannot be reached from the current vertex, return false
            for (bool v : visited)
            {
                if (!v)
                    return false;
            }
        }
        return true;
    }

    void Algorithms::dfs(const std::vector<std::vector<int>> &matrix, std::vector<bool> &visited, int node)
    {
        visited[node] = true;

        for (int i = 0; i < static_cast<int>(matrix.size()); ++i)

        {
            if (matrix[node][i] && !visited[i])
            {
                dfs(matrix, visited, i);
            }
        }
    }

    bool Algorithms::isCycleUtil(const std::vector<std::vector<int>> &matrix, int v, std::vector<bool> &visited, std::vector<int> &cyclePath, std::vector<bool> &recStack, int parent)
    {
        visited[v] = true;
        recStack[v] = true;
        cyclePath.push_back(v);

        for (int i = 0; i < static_cast<int>(matrix.size()); ++i)
        {
            if (matrix[v][i])
            {
                if (!visited[i] && isCycleUtil(matrix, i, visited, cyclePath, recStack, v))
                {
                    return true;
                }
                else if (recStack[i] && i != parent) // Check if it's a back edge but not to the parent
                {
                    // Cycle found, extract the cycle path
                    auto startIt = std::find(cyclePath.begin(), cyclePath.end(), i);
                    cyclePath.erase(cyclePath.begin(), startIt);
                    return true;
                }
            }
        }
        recStack[v] = false;
        cyclePath.pop_back();
        return false;
    }

    std::string Algorithms::isContainsCycle(const Graph &g)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();
        std::vector<bool> visited(n, false);
        std::vector<int> cyclePath;
        std::vector<bool> recStack(n, false);

        for (int i = 0; i < n; ++i)
        {
            if (!visited[i])
            {
                if (isCycleUtil(matrix, i, visited, cyclePath, recStack, -1)) // Pass -1 as the parent for the root
                {
                    std::string result = "The cycle is: ";
                    for (int node : cyclePath)
                    {
                        result += std::to_string(node) + "->";
                    }
                    result += std::to_string(cyclePath.front()); // Add the start node to complete the cycle
                    return result;
                }
            }
        }
        return "No cycle found.";
    }

    std::string Algorithms::isBipartite(const Graph &g)
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
                        // Only consider edges with non-zero weights
                        if (matrix[u][v] != 0 && color[v] == -1)
                        {
                            color[v] = 1 - color[u];
                            q.push(v);
                        }
                        else if (matrix[u][v] != 0 && color[u] == color[v])
                        {
                            return "The graph is not bipartite.";
                        }
                    }
                }
            }
        }

        // Build the partitions based on colors
        std::vector<int> A, B;
        for (int i = 0; i < n; ++i)
        {
            if (color[i] == 0)
                A.push_back(i);
            else
                B.push_back(i);
        }

        // Build the result string
        std::string result = "The graph is bipartite: A={";
        for (std::vector<int>::size_type i = 0; i < A.size(); ++i)
        {
            result += std::to_string(A[i]);
            if (i < A.size() - 1)
                result += ", ";
        }
        result += "}, B={";
        for (std::vector<int>::size_type i = 0; i < B.size(); ++i)
        {
            result += std::to_string(B[i]);
            if (i < B.size() - 1)
                result += ", ";
        }
        result += "}";

        return result;
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

    std::string Algorithms::shortestPath(const Graph &g, int start, int end)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();
        std::vector<int> dist(n, INT_MAX);
        std::vector<int> prev(n, -1);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty())
        {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u])
                continue;

            for (int v = 0; v < n; ++v)
            {
                if (matrix[u][v] != 0)
                {
                    int new_dist = dist[u] + matrix[u][v];
                    if (new_dist < dist[v])
                    {
                        dist[v] = new_dist;
                        prev[v] = u;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        // Reconstruct the shortest path if it exists
        if (dist[end] == INT_MAX)
        {
            return "-1"; // No path exists between start and end vertices
        }
        else
        {
            // Reconstruct the shortest path
            std::vector<int> path;
            int current = end;
            while (current != -1)
            {
                path.push_back(current);
                current = prev[current];
            }
            std::reverse(path.begin(), path.end());

            // Convert the path to a string
            std::string pathStr;
            for (size_t i = 0; i < path.size(); ++i)
            {
                pathStr += std::to_string(path[i]);
                if (i < path.size() - 1)
                {
                    pathStr += "->";
                }
            }
            return pathStr;
        }
    }

} // namespace ariel