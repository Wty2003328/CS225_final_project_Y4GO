#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "info_constructor.h"
TEST_CASE("try read correct airport and routes", "[weight=0][part=1]") {

    info_container information("../tests/information_test_airport.txt", "../tests/information_test_routes.txt");
    information.read();
    information.clean();
    std::vector<Vertex> airports = information.generate_vertices();
    std::vector<std::pair<Vertex, Vertex>> routes = information.generate_edges();
    REQUIRE(airports.size()=5);
    REQUIRE(routes.size()=4);
    REQUIRE(airports[0]="Goroka Airport");
    REQUIRE(airports[1]="Madang Airport");
    REQUIRE(airports[2]="Mount Hagen Kagamuga Airport");
    REQUIRE(airports[3]="Nadzab Airport");
    REQUIRE(airports[4]="Port Moresby Jacksons International Airport");
    
    REQUIRE(routes[0].first=="Goroka Airport");
    REQUIRE(routes[0].second="Madang Airport");
    REQUIRE(routes[1].first="Madang Airport");
    REQUIRE(routes[1].second="Mount Hagen Kagamuga Airport");
    REQUIRE(routes[2].first="Nadzab Airport");
    REQUIRE(routes[2].second="Port Moresby Jacksons International Airport");
    REQUIRE(routes[3].first="Goroka Airport");
    REQUIRE(routes[3].second="Port Moresby Jacksons International Airport");
}