#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

TEST_CASE("Unweighted Directed Graph")
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

TEST_CASE("Unweighted Undirected Graph")
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

TEST_CASE("Weighted Directed Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, 0},
        {0, 0, 3},
        {4, 0, 0}};
    g.loadGraph(graph, true); // false indicates directed graph
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
}

TEST_CASE("Weighted Undirected Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, 3},
        {2, 0, 4},
        {3, 4, 0}};
    g.loadGraph(graph, false); // true indicates undirected graph
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
}

TEST_CASE("Test invalid weight in unweighted graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 3},
    };
    CHECK_THROWS(g.loadGraph(graph, true)); // Assuming loading invalid weights throws
}

TEST_CASE("Graph with no edges")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Graph with no cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Graph with positive cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, 0},
        {0, 0, 3},
        {1, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}
TEST_CASE("Graph with multiple edges and one negative cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, -3},
        {-2, 0, 1},
        {1, -2, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 2->1->0->2");
}
TEST_CASE("Sparse Graph with No Cycles")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 1},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found.");
}

TEST_CASE("Dense Directed Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
}

TEST_CASE("Disconnected Undirected Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, false);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Graph with Self Loops")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->0");
}

TEST_CASE("Graph with All Negative Weights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -1, -1},
        {-1, 0, -1},
        {-1, -1, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 2->1->2");
}

TEST_CASE("Complete Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("Bipartite Test with Even Cycle")
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

TEST_CASE("Non-Bipartite Test with Odd Cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 1}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite.");
}

TEST_CASE("Graph with Multiple Disconnected Components")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, 0},
        {2, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, false);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Graph with Loop and Negative Cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {-1, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Graph with Highly Negative Edges")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -100, 0},
        {0, 0, -100},
        {-100, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 1->2->0->1");
}

TEST_CASE("Graph with Large Weights and No Cycles")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 999, 0},
        {0, 0, 999},
        {999, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
}

TEST_CASE("Graph with Zero Weights Only")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Empty Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {}; // Empty graph
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("Single Node Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {{0}}; // Single node graph
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found.");
}

TEST_CASE("Two Nodes with Negative Edge")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -1},
        {-1, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 1->0->1");
}
