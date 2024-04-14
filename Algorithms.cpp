#include "Algorithms.hpp"
#include <vector>
#include <queue>
#include <algorithm> // For std::min
#include <cstddef>

namespace ariel
{
    namespace Algorithms
    {
        bool isCycleUtil(const std::vector<std::vector<int>> &adjacencyMatrix, size_t v, std::vector<bool> &visited, int parent);

        bool isConnected(const Graph &g)
        {
            const auto &adjacencyMatrix = g.getAdjacencyMatrix();
            size_t numVertices = adjacencyMatrix.size();
            std::vector<bool> visited(numVertices, false);
            std::queue<size_t> q;

            q.push(0);
            visited[0] = true;

            while (!q.empty())
            {
                size_t current = q.front();
                q.pop();

                for (size_t i = 0; i < numVertices; ++i)
                {
                    if (adjacencyMatrix[current][i] && !visited[i])
                    {
                        q.push(i);
                        visited[i] = true;
                    }
                }
            }

            return std::all_of(visited.begin(), visited.end(), [](bool v)
                               { return v; });
        }

        std::string shortestPath(const Graph &g, size_t start, size_t end)
        {
            const auto &adjacencyMatrix = g.getAdjacencyMatrix();
            size_t numVertices = adjacencyMatrix.size();
            std::vector<std::vector<int>> dist = adjacencyMatrix;

            for (size_t k = 0; k < numVertices; ++k)
            {
                for (size_t i = 0; i < numVertices; ++i)
                {
                    for (size_t j = 0; j < numVertices; ++j)
                    {
                        if (dist[i][k] != 0 && dist[k][j] != 0 && (dist[i][j] == 0 || dist[i][j] > dist[i][k] + dist[k][j]))
                        {
                            if (dist[i][k] + dist[k][j] < dist[i][j])
                            {
                                // Handle negative cycle
                                return "-1";
                            }
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }

            if (dist[start][end] == 0)
            {
                return "-1";
            }

            std::string path = std::to_string(start);
            size_t current = start;
            while (current != end)
            {
                for (size_t i = 0; i < numVertices; ++i)
                {
                    if (dist[current][i] != 0 && dist[i][end] != 0 && dist[current][end] == dist[current][i] + dist[i][end])
                    {
                        path += "->" + std::to_string(i);
                        current = i;
                        break;
                    }
                }
            }

            return path;
        }

        bool isContainsCycle(const Graph &g)
        {
            const auto &adjacencyMatrix = g.getAdjacencyMatrix();
            size_t numVertices = adjacencyMatrix.size();
            std::vector<bool> visited(numVertices, false);

            for (size_t i = 0; i < numVertices; ++i)
            {
                if (!visited[i] && isCycleUtil(adjacencyMatrix, i, visited, -1))
                {
                    return true;
                }
            }
            return false;
        }

        bool isCycleUtil(const std::vector<std::vector<int>> &adjacencyMatrix, size_t v, std::vector<bool> &visited, int parent)
        {
            visited[v] = true;
            for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
            {
                if (adjacencyMatrix[v][i])
                {
                    if (!visited[i])
                    {
                        if (isCycleUtil(adjacencyMatrix, i, visited, v))
                        {
                            return true;
                        }
                    }
                    else if (i != parent)
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        std::string isBipartite(const Graph &g)
        {
            const auto &adjMatrix = g.getAdjacencyMatrix();
            size_t numVertices = adjMatrix.size();
            std::vector<int> color(numVertices, -1);
            std::vector<size_t> partitionA, partitionB;

            std::queue<size_t> q;
            for (size_t i = 0; i < numVertices; ++i)
            {
                if (color[i] == -1)
                {
                    color[i] = 1;
                    partitionA.push_back(i);
                    q.push(i);
                    while (!q.empty())
                    {
                        size_t u = q.front();
                        q.pop();
                        for (size_t v = 0; v < numVertices; ++v)
                        {
                            if (adjMatrix[u][v])
                            {
                                if (color[v] == -1)
                                {
                                    color[v] = 1 - color[u];
                                    if (color[v] == 1)
                                        partitionA.push_back(v);
                                    else
                                        partitionB.push_back(v);
                                    q.push(v);
                                }
                                else if (color[v] == color[u])
                                {
                                    return "The graph is not bipartite.";
                                }
                            }
                        }
                    }
                }
            }

            std::string result = "The graph is bipartite: A={";

            // Add elements of partitionA to the string
            for (size_t i = 0; i < partitionA.size(); ++i)
            {
                result += std::to_string(partitionA[i]);
                if (i < partitionA.size() - 1) // Add comma if it's not the last element
                    result += ", ";
            }

            result += "}, B={";

            // Add elements of partitionB to the string
            for (size_t i = 0; i < partitionB.size(); ++i)
            {
                result += std::to_string(partitionB[i]);
                if (i < partitionB.size() - 1) // Add comma if it's not the last element
                    result += ", ";
            }

            result += "}";

            return result;
        }

    } // namespace Algorithms
} // namespace ariel
