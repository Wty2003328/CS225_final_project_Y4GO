// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "graph_constructor.h"

using namespace std;

int main()
{
    std::vector<Vertex> airports{ "a","b","c","d","e","f","g" };
    std::vector<std::pair<Vertex, Vertex>> edges{
        std::pair<Vertex,Vertex>("a","b"),
        std::pair<Vertex,Vertex>("b","c"),
        std::pair<Vertex,Vertex>("c","d"),
        std::pair<Vertex,Vertex>("d","e"),
        std::pair<Vertex,Vertex>("e","f"),
        std::pair<Vertex,Vertex>("f","g"),
        std::pair<Vertex,Vertex>("a","c"),
        std::pair<Vertex,Vertex>("c","d"),
        std::pair<Vertex,Vertex>("d","g")
    };
    container graph(airports, edges);
    std::vector<Vertex> path = graph.solvebyBFS(airports, "a", "g");
    for (auto it = path.begin(); it != path.end(); ++it)
    {
        cout << *it << endl;
    }  
    return 0;
}
