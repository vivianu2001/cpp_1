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
