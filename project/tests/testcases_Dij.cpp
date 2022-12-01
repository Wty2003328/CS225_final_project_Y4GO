#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "graph_constructor.h"

std::vector<Vertex> large_graph_path_unweighted(Vertex start, Vertex end)
{
    std::vector<Vertex> airports{ "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
    std::vector<std::pair<Vertex, Vertex>> edges{
        std::pair<Vertex,Vertex>("a","b"),
        std::pair<Vertex,Vertex>("a","c"),
        std::pair<Vertex,Vertex>("a","j"),
        std::pair<Vertex,Vertex>("a","g"),
        std::pair<Vertex,Vertex>("b","y"),
        std::pair<Vertex,Vertex>("b","f"),
        std::pair<Vertex,Vertex>("b","p"),
        std::pair<Vertex,Vertex>("c","x"),
        std::pair<Vertex,Vertex>("c","n"),
        std::pair<Vertex,Vertex>("c","l"),
        std::pair<Vertex,Vertex>("d","a"),
        std::pair<Vertex,Vertex>("g","i"),
        std::pair<Vertex,Vertex>("g","w"),
        std::pair<Vertex,Vertex>("g","j"),
        std::pair<Vertex,Vertex>("h","r"),
        std::pair<Vertex,Vertex>("i","m"),
        std::pair<Vertex,Vertex>("i","s"),
        std::pair<Vertex,Vertex>("j","e"),
        std::pair<Vertex,Vertex>("j","u"),
        std::pair<Vertex,Vertex>("k","w"),
        std::pair<Vertex,Vertex>("l","t"),
        std::pair<Vertex,Vertex>("o","d"),
        std::pair<Vertex,Vertex>("p","y"),
        std::pair<Vertex,Vertex>("q","p"),
        std::pair<Vertex,Vertex>("q","f"),
        std::pair<Vertex,Vertex>("r","z"),
        std::pair<Vertex,Vertex>("u","e"),
        std::pair<Vertex,Vertex>("v","k"),
        std::pair<Vertex,Vertex>("y","o"),
        std::pair<Vertex,Vertex>("z","h"),
    };
    std::vector<double> distances = vector(edges.size(), 1);
    container graph(airports, edges,distances);
    std::vector<Vertex> path = graph.solvebyDij(airports, start, end);
    return path;
}
//**need modification on weight
std::vector<Vertex> large_graph_path_weighted(Vertex start, Vertex end)
{
    std::vector<Vertex> airports{ "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
    std::vector<std::pair<Vertex, Vertex>> edges{
        std::pair<Vertex,Vertex>("a","b"),
        std::pair<Vertex,Vertex>("a","c"),
        std::pair<Vertex,Vertex>("a","j"),
        std::pair<Vertex,Vertex>("a","g"),
        std::pair<Vertex,Vertex>("b","y"),
        std::pair<Vertex,Vertex>("b","f"),
        std::pair<Vertex,Vertex>("b","p"),
        std::pair<Vertex,Vertex>("c","x"),
        std::pair<Vertex,Vertex>("c","n"),
        std::pair<Vertex,Vertex>("c","l"),
        std::pair<Vertex,Vertex>("d","a"),
        std::pair<Vertex,Vertex>("g","i"),
        std::pair<Vertex,Vertex>("g","w"),
        std::pair<Vertex,Vertex>("g","j"),
        std::pair<Vertex,Vertex>("h","r"),
        std::pair<Vertex,Vertex>("i","m"),
        std::pair<Vertex,Vertex>("i","s"),
        std::pair<Vertex,Vertex>("j","e"),
        std::pair<Vertex,Vertex>("j","u"),
        std::pair<Vertex,Vertex>("k","w"),
        std::pair<Vertex,Vertex>("l","t"),
        std::pair<Vertex,Vertex>("o","d"),
        std::pair<Vertex,Vertex>("p","y"),
        std::pair<Vertex,Vertex>("q","p"),
        std::pair<Vertex,Vertex>("q","f"),
        std::pair<Vertex,Vertex>("r","z"),
        std::pair<Vertex,Vertex>("u","e"),
        std::pair<Vertex,Vertex>("v","k"),
        std::pair<Vertex,Vertex>("y","o"),
        std::pair<Vertex,Vertex>("z","h"),
    };
    std::vector<double> distances = vector(edges.size(), 1);
    container graph(airports, edges, distances);
    std::vector<Vertex> path = graph.solvebyDij(airports, start, end);
    return path;
}

TEST_CASE("Dij works on small graph with all out directing unweighted graph", "[weight=0][part=1]") {

    std::vector<Vertex> airports{ "a","b","c","d","e","f","g" };
    std::vector<std::pair<Vertex, Vertex>> edges{
        std::pair<Vertex,Vertex>("a","b"),
        std::pair<Vertex,Vertex>("a","c"),
        std::pair<Vertex,Vertex>("a","d"),
        std::pair<Vertex,Vertex>("a","e"),
        std::pair<Vertex,Vertex>("a","f"),
        std::pair<Vertex,Vertex>("b","g")
    };
    std::vector<double> distances = vector(edges.size(), 1);
    container graph(airports, edges, distances);
    std::vector<Vertex> path = graph.solvebyBFS(airports, "a", "g");
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "g");
}

TEST_CASE("Dij works on small graph with undirected unweighted graph", "[weight=0][part=1]") {
    /*
       same graph structure of above graph, but undirected edges
    */
    std::vector<Vertex> airports{ "a","b","c","d","e","f","g" };
    std::vector<std::pair<Vertex, Vertex>> edges{
        std::pair<Vertex,Vertex>("a","b"),
        std::pair<Vertex,Vertex>("a","b"),
        std::pair<Vertex,Vertex>("a","c"),
        std::pair<Vertex,Vertex>("c","a"),
        std::pair<Vertex,Vertex>("a","d"),
        std::pair<Vertex,Vertex>("d","a"),
        std::pair<Vertex,Vertex>("a","e"),
        std::pair<Vertex,Vertex>("e","a"),
        std::pair<Vertex,Vertex>("a","f"),
        std::pair<Vertex,Vertex>("f","a"),
        std::pair<Vertex,Vertex>("b","g")
        std::pair<Vertex,Vertex>("g","b")
    };
    std::vector<double> distances = vector(edges.size(), 1);
    container graph(airports, edges, distances);
    std::vector<Vertex> path = graph.solvebyBFS(airports, "a", "g");
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "g");
}

TEST_CASE("Dij works on larger unweighted graph for unreachable vertex", "[weight=0][part=1]") {
    std::vector<Vertex> path = large_graph_path("a", "h");
    REQUIRE(path[0] == "Destination not reachable!");
    std::vector<Vertex> path1 = large_graph_path("a", "q");
    REQUIRE(path1[0] == "Destination not reachable!");
}

TEST_CASE("Dij works on larger unweighted graph for reachable vertex", "[weight=0][part=1]") {

    std::vector<Vertex> path = large_graph_path("a", "d");
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "y");
    REQUIRE(path[3] == "o");
    REQUIRE(path[4] == "d");
    std::vector<Vertex> path1 = large_graph_path("a", "w");
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "g");
    REQUIRE(path[2] == "w");
}

//test on weighted graph **need modification
TEST_CASE("Dij works on small graph with all out directing weighted graph", "[weight=0][part=1]") {

    std::vector<Vertex> airports{ "a","b","c","d","e","f","g" };
    std::vector<std::pair<Vertex, Vertex>> edges{
        std::pair<Vertex,Vertex>("a","b"),
        std::pair<Vertex,Vertex>("a","c"),
        std::pair<Vertex,Vertex>("a","d"),
        std::pair<Vertex,Vertex>("a","e"),
        std::pair<Vertex,Vertex>("a","f"),
        std::pair<Vertex,Vertex>("b","g")
    };
    std::vector<double> distances = vector(edges.size(), 1);
    container graph(airports, edges, distances);
    std::vector<Vertex> path = graph.solvebyBFS(airports, "a", "g");
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "g");
}

TEST_CASE("Dij works  on small graph with undirected weighted graph", "[weight=0][part=1]") {
    /*
       same graph structure of above graph, but undirected edges
    */
    std::vector<Vertex> airports{ "a","b","c","d","e","f","g" };
    std::vector<std::pair<Vertex, Vertex>> edges{
        std::pair<Vertex,Vertex>("a","b"),
        std::pair<Vertex,Vertex>("a","b"),
        std::pair<Vertex,Vertex>("a","c"),
        std::pair<Vertex,Vertex>("c","a"),
        std::pair<Vertex,Vertex>("a","d"),
        std::pair<Vertex,Vertex>("d","a"),
        std::pair<Vertex,Vertex>("a","e"),
        std::pair<Vertex,Vertex>("e","a"),
        std::pair<Vertex,Vertex>("a","f"),
        std::pair<Vertex,Vertex>("f","a"),
        std::pair<Vertex,Vertex>("b","g")
        std::pair<Vertex,Vertex>("g","b")
    };
    std::vector<double> distances = vector(edges.size(), 1);
    container graph(airports, edges, distances);
    std::vector<Vertex> path = graph.solvebyBFS(airports, "a", "g");
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "g");
}

TEST_CASE("Dij works on larger weighted graph for unreachable vertex", "[weight=0][part=1]") {

    std::vector<Vertex> path = large_graph_path_weighted("a", "h");
    REQUIRE(path[0] == "Destination not reachable!");
    std::vector<Vertex> path1 = large_graph_path_weighted("a", "q");
    REQUIRE(path1[0] == "Destination not reachable!");
}

TEST_CASE("Dij works on larger weighted graph for reachable vertex", "[weight=0][part=1]") {
    std::vector<Vertex> path = large_graph_path_weighted("a", "d");
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "y");
    REQUIRE(path[3] == "o");
    REQUIRE(path[4] == "d");
    std::vector<Vertex> path1 = large_graph_path_weighted("a", "w");
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "g");
    REQUIRE(path[2] == "w");
}