/*
ID : 322880857
GMAIL : Umanskyvivian@gmail.com
*/
#include "Algorithms.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <climits> // For INT_MAX
#include <algorithm>
#include <sstream>
namespace ariel
{


bool Algorithms::isConnected(const Graph &graph)
{
    const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
    size_t n = matrix.size();
    if (n == 0)
    {
        // Consider an empty graph as connected; return true if this is the intended behavior.
        return true;
    }

    if (graph.getIsDirected())
    {
        // For directed graphs, check if the graph is strongly connected.
        return isStronglyConnected(graph);
    }

    // Find a starting node that is not isolated (if possible)
    size_t start = n;  // Initialized to n, which is an invalid index.
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (matrix[i][j] != 0)
            {
                start = i;
                break;  // Break from the inner loop only.
            }
        }
        if (start != n)
        {
            break;  // Break from the outer loop if a start node has been found.
        }
    }

    if (start == n)
    {
        // If no starting node has been found, all nodes are isolated.
        return false;
    }

    // Use breadth-first search (BFS) from the start node to check connectivity.
    return bfs(matrix, start);
}

  #include <vector>

bool Algorithms::isStronglyConnected(const Graph &graph)
{
    const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
    size_t n = matrix.size();  // Use size_t for sizes and indices

    // Perform DFS from each vertex to check for strong connectivity
    for (size_t i = 0; i < n; ++i)
    {
        std::vector<bool> visited(n, false);  // Directly use size_t for initialization

        dfs(matrix, visited, i);

        // If any vertex cannot be reached from the current vertex, return false
        for (bool v : visited)
        {
            if (!v)
            {
                return false;  // Return false if any vertex is not visited
            }
        }
    }
    return true;  // Return true if all vertices are strongly connected
}

void Algorithms::dfs(const std::vector<std::vector<int>> &matrix, std::vector<bool> &visited, size_t node)
{
    visited[node] = true;

    // Using size_t directly for loop index and eliminating unnecessary casts
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        // Ensure `i` is used directly with `visited` and `matrix[node]` without casting
        if (matrix[node][i] != 0 && !visited[i])
        {
            dfs(matrix, visited, i);
        }
    }
}
bool Algorithms::bfs(const std::vector<std::vector<int>>& matrix, size_t start)
{
    size_t n = matrix.size();
    std::vector<bool> visited(n, false);
    std::queue<size_t> q;  // Use size_t for the queue to match the type of indices
    q.push(start);
    visited[start] = true;  // No need for casting with start as size_t

    while (!q.empty())
    {
        size_t node = q.front();  // Use size_t for node
        q.pop();

        for (size_t i = 0; i < n; ++i)
        {
            if (matrix[node][i] != 0 && !visited[i])  // Use direct index without casting
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    // Check if all nodes were visited
    for (bool v : visited)
    {
        if (!v)
            return false;
    }

    return true;
}

bool Algorithms::isCycleUtil(const std::vector<std::vector<int>>& matrix, size_t v, std::vector<bool>& visited, std::vector<int>& cyclePath, std::vector<bool>& recStack, size_t parent)
{
    visited[v] = true;
    recStack[v] = true;
    cyclePath.push_back(static_cast<int>(v));  // Safe as long as v is within int's range

    for (size_t i = 0; i < matrix.size(); ++i)
    {
        if (matrix[v][i] != 0)
        {
            if (!visited[i])
            {
                if (isCycleUtil(matrix, i, visited, cyclePath, recStack, v))
                {
                    return true;
                }
            }
            else if (recStack[i] && i != parent && parent != std::numeric_limits<size_t>::max())  // Ensure parent is valid and not the special value
            {
                auto startIt = std::find(cyclePath.begin(), cyclePath.end(), static_cast<int>(i));
                cyclePath.erase(cyclePath.begin(), startIt);
                return true;
            }
        }
    }

    recStack[v] = false;
    cyclePath.pop_back();
    return false;
}


    #include <limits> // Include for std::numeric_limits

std::string Algorithms::isContainsCycle(const Graph &graph)
{
    const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
    size_t n = matrix.size(); // Use size_t directly for consistency
    if (n == 0)
    {
        // Handle empty graph
        return "No cycle found.";
    }

    std::vector<bool> visited(n, false);
    std::vector<int> cyclePath;
    std::vector<bool> recStack(n, false);

    for (size_t i = 0; i < n; ++i)
    {
        if (!visited[i])
        {
            // Use std::numeric_limits<size_t>::max() to signify no parent
            if (isCycleUtil(matrix, i, visited, cyclePath, recStack, std::numeric_limits<size_t>::max()))
            {
                return "The cycle is: " + constructPath(cyclePath) + "->" + std::to_string(cyclePath.front());
            }
        }
    }
    return "No cycle found.";
}



std::string Algorithms::buildBipartiteResult(const std::vector<int> &color) {
  std::vector<int> A, B;
for (size_t i = 0; i < color.size(); ++i) {
    if (color[i] == 0)
        A.push_back(static_cast<int>(i));
    else if (color[i] == 1)
        B.push_back(static_cast<int>(i));
}


    std::ostringstream result;
    result << "The graph is bipartite: A={";
    for (size_t i = 0; i < A.size(); ++i) {
        result << A[i];
        if (i < A.size() - 1)
            result << ", ";
    }
    result << "}, B={";
    for (size_t i = 0; i < B.size(); ++i) {
        result << B[i];
        if (i < B.size() - 1)
            result << ", ";
    }
    result << "}";
    return result.str();
}




std::string Algorithms::isBipartite(const Graph &graph)
{
    const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
    size_t n = matrix.size();
    std::vector<int> color(n, -1); // Initializing colors to -1 to indicate unvisited nodes

    if (n == 0)
    {
        // Directly handle the empty graph case
        return "The graph is not bipartite.";
    }

    // Check each component of the graph
    for (size_t i = 0; i < n; ++i)
    {
        if (color[i] == -1) // If this component isn't colored yet
        {
            if (!checkBipartite(matrix, color, i))
            {
                return "The graph is not bipartite.";
            }
        }
    }

    return buildBipartiteResult(color);
}

    std::string Algorithms::constructPath(const std::vector<int> &path)
    {
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

#include <vector>
#include <queue>

bool Algorithms::checkBipartite(const std::vector<std::vector<int>>& matrix, std::vector<int>& color, size_t start) {
    std::queue<size_t> q;  // Use size_t for queue to align with the vector indexing
    q.push(start);
    color[start] = 0;  // Properly using size_t for index

    while (!q.empty()) {
        size_t u = q.front();  // Use size_t for index
        q.pop();

        for (size_t v = 0; v < matrix.size(); ++v) {  // Use size_t for index
            if (matrix[u][v] != 0) {  // There is an edge
                if (color[v] == -1) {  // If not colored
                    color[v] = 1 - color[u];  // Color with the opposite color
                    q.push(v);
                } else if (color[v] == color[u]) {  // If same color as parent
                    return false;  // Not bipartite
                }
            }
        }
    }
    return true;
}



    std::string Algorithms::negativeCycle(const Graph &g)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        size_t n = matrix.size();
        std::vector<int> dist, prev;
        
        if (n == 0)
        {
            // Handle empty graph
            return "No negative cycle found";
        }

        if (!bellmanFord(matrix, 0, dist, prev))
        {
            // Find and construct the negative cycle path
            for (size_t u = 0; u < n; ++u)
            {
                for (size_t v = 0; v < n; ++v)
                {
                    if (matrix[u][v] != 0 && dist[u] + matrix[u][v] < dist[v])
                    {
                        std::vector<int> cycle;
                         int x = v;
                        do
                        {
                            cycle.push_back(static_cast<int>(x));
                            x = prev[static_cast<size_t>(x)];
                        } while (x != v);
                        cycle.push_back(static_cast<int>(v));
                        std::reverse(cycle.begin(), cycle.end());

                        return "Negative cycle found: " + constructPath(cycle);
                    }
                }
            }
        }

        return "No negative cycle found";
    }


std::string Algorithms::shortestPath(const Graph &graph, int start, int end)
{
    const std::vector<std::vector<int>>& matrix = graph.getAdjacencyMatrix();
    size_t n = matrix.size();
    if (n == 0)
    {
        return "No shortest path in empty graph";
    }

    // Ensure start and end are within the valid range and non-negative
    if (start < 0 || static_cast<size_t>(start) >= n || end < 0 || static_cast<size_t>(end) >= n)
    {
        return "Invalid start or end vertex."; // Return an error message for invalid vertices
    }

    // Use size_t for start index in vectors to comply with C++ type safety
    size_t s = static_cast<size_t>(start); // Safe as we already checked it's non-negative and within bounds

    // Check for negative cycles using the existing negativeCycle function
    std::string negativeCycleResult = negativeCycle(graph);
    if (negativeCycleResult.find("Negative cycle found") != std::string::npos)
    {
        return "Negative cycle detected, shortest path not defined.";
    }

    std::vector<int> dist(n, std::numeric_limits<int>::max());
    std::vector<int> prev(n, -1);

    if (graph.NegativeEdges)
    {
        // Use Bellman-Ford algorithm for graphs with negative edges
        dist[s] = 0; // Now using s which is of type size_t

        if (!bellmanFord(matrix, static_cast<int>(s), dist, prev))

        {
            return "Negative cycle detected, shortest path not defined.";
        }

        return constructPathFromPrev(prev, end, s);
    }
    else
    {
        // Use Dijkstra's algorithm for graphs without negative edges
        std::vector<int> prev = dijkstra(matrix, static_cast<int>(s));


        return constructPathFromPrev(prev, end, s);
    }
}

std::string Algorithms::constructPathFromPrev(const std::vector<int>& prev, int end, size_t start)
{
    std::vector<int> path;
    int current = end;
    while (current != -1 && static_cast<size_t>(current) != start)
    {
        path.push_back(current);
        current = prev[static_cast<size_t>(current)];
    }
    path.push_back(static_cast<int>(start));
    std::reverse(path.begin(), path.end());

    return constructPath(path);
}



bool Algorithms::bellmanFord(const std::vector<std::vector<int>>& matrix, int source, std::vector<int>& dist, std::vector<int>& prev)
{
    size_t n = matrix.size();
    if (source < 0 || static_cast<size_t>(source) >= n) {
        // Handle invalid source
        return false;
    }

    size_t s = static_cast<size_t>(source);  // Ensure source is size_t for safe indexing
    dist.assign(n, std::numeric_limits<int>::max());
    prev.assign(n, -1);

    dist[s] = 0; // Initialize the source vertex distance to zero

    bool updated=false;
    // Relax all edges |V-1| times
    for (size_t i = 0; i < n - 1; ++i)
    {
        updated = false;
        for (size_t u = 0; u < n; ++u)
        {
            if (dist[u] == std::numeric_limits<int>::max()) continue; // Skip if u is unreachable

            for (size_t v = 0; v < n; ++v)
            {
                if (matrix[u][v] != 0 && dist[u] + matrix[u][v] < dist[v])
                {
                    dist[v] = dist[u] + matrix[u][v];
                    prev[v] = static_cast<int>(u);
                    updated = true;
                }
            }
        }
        if (!updated) break; // Early exit if no updates occur
    }

    // Check for negative weight cycles
    for (size_t u = 0; u < n; ++u)
    {
        if (dist[u] == std::numeric_limits<int>::max()) continue; // Skip if u is unreachable

        for (size_t v = 0; v < n; ++v)
        {
            if (matrix[u][v] != 0 && dist[u] + matrix[u][v] < dist[v])
            {
                // Negative cycle detected
                return false;
            }
        }
    }

    return true; // No negative cycles found
}


std::vector<int> Algorithms::dijkstra(const std::vector<std::vector<int>>& matrix, int start) {
    size_t n = matrix.size();
    std::vector<int> dist(n, std::numeric_limits<int>::max());
    std::vector<int> prev(n, -1);
      std::priority_queue<std::pair<int, int>, 
                        std::vector<std::pair<int, int>>, 
                        std::greater<std::pair<int, int>>>
                        pq;

    if (start < 0 || static_cast<size_t>(start) >= n) {
        throw std::invalid_argument("Invalid start vertex"); // Ensuring start is within range
    }

    size_t s = static_cast<size_t>(start); // Convert start to size_t safely after checking
    dist[s] = 0;
    pq.push({0, static_cast<int>(s)});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        size_t su = static_cast<size_t>(u); // Convert u to size_t before use
        if (d > dist[su])
            continue;

        for (size_t v = 0; v < n; ++v) {
            if (matrix[su][v] != 0) { // Ensure su is used for indexing
                int new_dist = dist[su] + matrix[su][v];
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    prev[v] = u;
                    pq.push({new_dist, static_cast<int>(v)});
                }
            }
        }
    }

    return prev;
}

} // namespace ariel