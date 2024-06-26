/*
 * Demo program for Exercise 2.
 * Author: Benjamin Saldman.
 */
/*
ID : 0857
GMAIL : Umanskyvivian@gmail.com
*/
#include "Graph.hpp"
#include "Algorithms.hpp"
using ariel::Algorithms;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

void runDemo()
{
    ariel::Graph g;
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, true); // Load the graph to the object as undirected.
    cout << "Graph 1:\n";
    g.printGraph();                                    // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 2) << endl; // Should print: 0->1->2.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "No cycle found".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={0, 2}, B={1}".
    cout << "\n";
    // 5x5 matrix that represents a non-connected graph with a cycle.
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};

    g.loadGraph(graph2, false); // Load the graph to the object as undirected.
    cout << "Graph 2:\n";
    g.printGraph();                                    // Should print: "Graph with 5 vertices and 4 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "0" (false).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "No path available" (there is no path between 0 and 4).
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->2->0".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is not bipartite."
    cout << "\n";

    // 5x5 matrix that represents a connected weighted graph.
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {0, 0, 3, 0, 0},
        {0, 0, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3, true); // Load the graph to the object as directed.
    cout << "Graph 3:\n";
    g.printGraph();                                    // Should print: "Graph with 5 vertices and 6 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "0" (false).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: 0->1->2->3->4.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "No cycle found" (false).
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={0, 2, 4}, B={1, 3}".
    cout << "\n";

    // 5x4 matrix that represents an invalid graph.
    vector<vector<int>> graph4 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    try
    {
        cout << "Graph 4:\n";
        g.loadGraph(graph4, false); // Load the graph to the object as undirected.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // "The adjacency matrix must be square."
    }
    cout << "\n";
    vector<vector<int>> graph5 = {
        {0, 6, 4, 5, 0, 0},
        {0, 0, 0, 0, -1, 0},
        {0, -2, 0, 0, 3, 0},
        {0, 0, -2, 0, 0, -1},
        {0, 0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0, 0},
    };
    g.loadGraph(graph5, true); // Load the graph to the object as directed.

    cout << "Graph 5:\n";
    g.printGraph();                                    // Should print: "Graph with 6 vertices and 9 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "0" (false).
    cout << Algorithms::shortestPath(g, 0, 5) << endl; // Should print: 0->3->2->1->4->5.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "No cycle found."
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is not bipartite.".
    cout << "\n";
}
