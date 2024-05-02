#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

TEST_CASE("1-Unweighted Directed Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(doctest::toString(ariel::Algorithms::isContainsCycle(g)) == "The cycle is: 0->1->2->0");
    CHECK(doctest::toString(ariel::Algorithms::isBipartite(g)) == "The graph is not bipartite.");
}

TEST_CASE("2-Unweighted Undirected Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, false); // true indicates undirected graph
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found.");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");
}

TEST_CASE("3-Weighted Directed Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 4},
        {2, 0, 0},
        {0, 3, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->2->1->0");
}

TEST_CASE("4-Weighted Undirected Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, 3},
        {2, 0, 4},
        {3, 4, 0}};
    g.loadGraph(graph, false);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
}

TEST_CASE("5-Test invalid size ")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 3},
    };
    CHECK_THROWS(g.loadGraph(graph, true)); // Assuming loading invalid weights throws
}

TEST_CASE("6-Graph with no edges")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("7-Graph with negative cycle") // SHOW
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {-3, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 1->2->0->1");
}

TEST_CASE("8-Graph with positive cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, 0},
        {0, 0, 3},
        {1, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}
TEST_CASE("9-Graph with multiple edges and one negative cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, -3},
        {-2, 0, 1},
        {1, -2, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 2->1->0->2");
}
TEST_CASE("10-Sparse Graph with No Cycles")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 1},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found.");
}

TEST_CASE("11-Dense Directed Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
}

TEST_CASE("12-Disconnected Undirected Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, false);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("13-Graph with Self Loops")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->0");
}

// TEST_CASE("14-Graph with All Negative Weights")  //to many cycles
// {
//     ariel::Graph g;
//     std::vector<std::vector<int>> graph = {
//         {0, -1, -1},
//         {-1, 0, -1},
//         {-1, -1, 0}};
//     g.loadGraph(graph, true);
//     CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 2->1->2");
// }

TEST_CASE("15-Complete Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("16-Bipartite Test with Even Cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
}

TEST_CASE("17-Non-Bipartite Test with Odd Cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 1}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite.");
}

TEST_CASE("18-Graph with Multiple Disconnected Components")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, 0},
        {2, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, false);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("19-Graph with Loop and Negative Cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {-1, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("20-Graph with Highly Negative Edges")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -100, 0},
        {0, 0, -100},
        {-100, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 1->2->0->1");
}

TEST_CASE("21-Graph with Large Weights and No Cycles")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 999, 0},
        {0, 0, 999},
        {999, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
}

TEST_CASE("22-Graph with Zero Weights Only")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("23-Empty Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {}; // Empty graph
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("24-Single Node Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {{0}}; // Single node graph
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found.");
}

TEST_CASE("25-Two Nodes with Negative Edge")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -1},
        {-1, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 1->0->1");
}
TEST_CASE("26-Shortest Path with Negative Weights") // SHOW TEST!
{
    // Create a graph with negative weights
    ariel::Graph g;
    std::vector<std::vector<int>> graph26 = {
        {0, 1, 3, 0},
        {0, 0, 0, -1},
        {0, 0, 0, 1},
        {0, 0, 0, 0}};

    // Load the graph and check for connectivity
    g.loadGraph(graph26, true);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    // The shortest path should be "0->1->3"
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->1->3");
}
