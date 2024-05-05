/*
ID : 322880857
GMAIL : Umanskyvivian@gmail.com
*/
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
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite.");
}

TEST_CASE("2-Unweighted Undirected Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, false);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found.");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");
}

TEST_CASE("3-Test invalid size ")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 3},
    };
    CHECK_THROWS(g.loadGraph(graph, true)); // Assuming loading invalid weights throws
}

TEST_CASE("4-Graph with no edges")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("5-Graph with negative cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {-3, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 1->2->0->1");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite.");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("6-Graph with multiple edges and one negative cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, -3},
        {-2, 0, 1},
        {1, -2, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 2->1->0->2");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "Negative cycle detected, shortest path not defined.");
}
TEST_CASE("7-Sparse Graph with No Cycles")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 1},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found.");
}

TEST_CASE("8-Dense Directed Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
}

TEST_CASE("9-Disconnected Undirected Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, false);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("10-Graph with Self Loops")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->0");
}

TEST_CASE("11-Complete Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("12-Bipartite Test with Even Cycle")
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

TEST_CASE("13-Non-Bipartite Test with Odd Cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 1}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite.");
}

TEST_CASE("14-Graph with Multiple Disconnected Components")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, 0},
        {2, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, false);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("15-Graph with Loop and Negative Cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {-1, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("16-Graph with Highly Negative Edges")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -100, 0},
        {0, 0, -100},
        {-100, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 1->2->0->1");
}

TEST_CASE("17-Empty Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {}; // Empty graph
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("18-Single Node Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {{0}}; // Single node graph
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found.");
}

TEST_CASE("19-Two Nodes with Negative Edge")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -1},
        {-1, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 1->0->1");
}
TEST_CASE("20-Shortest Path with Negative Weights") // SHOW TEST!
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

TEST_CASE("21-Undirected, ") // SHOW TEST
{
    // Create a graph with negative weights
    ariel::Graph g;
    std::vector<std::vector<int>> graph26 = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0},
    };

    // Load the graph and check for connectivity
    g.loadGraph(graph26, false);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 2->3->4->5->2");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 8) == "0->1->2->8");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite.");
}
TEST_CASE("22-Bipartite, ") // SHOW TEST
{
    // Create a graph with negative weights
    ariel::Graph g;
    std::vector<std::vector<int>> graph28 = {
        {0, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 1},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 1, 0, 0, 0, 1, 0},
    };

    // Load the graph and check for connectivity
    g.loadGraph(graph28, false);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 2->3->4->5->6->7->2");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->1->2->3->4");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4, 6}, B={1, 3, 5, 7}");
}
TEST_CASE("23-Bipartite, ") // SHOW TEST
{
    // Create a graph with negative weights
    ariel::Graph g;
    std::vector<std::vector<int>> graph28 = {
        {0, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 1},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 1},
        {0, 1, 0, 0, 1, 0},

    };

    // Load the graph and check for connectivity
    g.loadGraph(graph28, false);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 1->2->3->4->5->1");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite.");
}

TEST_CASE("24-Bipartite, ") // SHOW TEST
{
    // Create a graph with negative weights
    ariel::Graph g;
    std::vector<std::vector<int>> graph30 = {
        {0, 6, 4, 5, 0, 0},
        {0, 0, 0, 0, -1, 0},
        {0, -2, 0, 0, 3, 0},
        {0, 0, -2, 0, 0, -1},
        {0, 0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0, 0},

    };

    // Load the graph and check for connectivity
    g.loadGraph(graph30, true);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found.");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite.");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 5) == "0->3->2->1->4->5");
}

TEST_CASE("26-Disconnected Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("26-Disconnected Graph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 3, 2, 8, 0},
        {3, 5, 0, 7, 0},
        {2, 0, 0, 4, 9},
        {8, 7, 4, 0, 6},
        {0, 0, 9, 6, 0},
    };
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 1->1");
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite.");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->2->3");
}
