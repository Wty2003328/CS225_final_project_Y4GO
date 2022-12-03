#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "info_constructor.h"

TEST_CASE("Get small dataset of airlines, '.txt'", "[weight=0][part=1]") {
	/*
       a is the center, b,c,d,e,f are points around a and a has edges pointing to them, g is the point at one layer further and is 
    */
    info_container information("../data/airport.txt", "../data/routes.txt");
    information.read();
    information.clean();
    vector<Vertex> airports = information.generate_vertices();
    vector<pair<Vertex, Vertex>> routes = information.generate_edges();
    vector<double> dist = information.calculate_dist();
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "g");
}