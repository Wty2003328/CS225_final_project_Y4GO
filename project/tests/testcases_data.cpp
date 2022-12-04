#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "info_constructor.h"
TEST_CASE("try read correct airport and routes", "[weight=0][part=1]") {

    info_container information("../tests/information_test_airport.txt", "../tests/information_test_routes.txt","../tests/information_test_airlines.txt");
    information.read();
    information.clean();
    std::vector<std::string> airports = information.generate_vertices();
    std::vector<std::pair<std::string, std::string>> routes = information.generate_edges();
    REQUIRE(airports.size()==5);
    REQUIRE(airports[0]=="\"Goroka Airport\"");
    REQUIRE(airports[1]=="\"Madang Airport\"");
    REQUIRE(airports[2]=="\"Mount Hagen Kagamuga Airport\"");
    REQUIRE(airports[3]=="\"Nadzab Airport\"");
    REQUIRE(airports[4]=="\"Port Moresby Jacksons International Airport\"");
    REQUIRE(routes.size()==4);
    REQUIRE(routes[0].first=="\"Goroka Airport\"");
    REQUIRE(routes[0].second=="\"Madang Airport\"");
    REQUIRE(routes[1].first=="\"Madang Airport\"");
    REQUIRE(routes[1].second=="\"Mount Hagen Kagamuga Airport\"");
    REQUIRE(routes[2].first=="\"Nadzab Airport\"");
    REQUIRE(routes[2].second=="\"Port Moresby Jacksons International Airport\"");
    REQUIRE(routes[3].first=="\"Goroka Airport\"");
    REQUIRE(routes[3].second=="\"Port Moresby Jacksons International Airport\"");
}

/*
TEST_CASE("try read correct airport and routes, some routes need to be delete", "[weight=0][part=1]") {

    info_container information("../tests/information_test_airport3.txt", "../tests/information_test_routes3.txt");
    information.read();
    information.clean();
    std::vector<Vertex> airports = information.generate_vertices();
    std::vector<std::pair<Vertex, Vertex>> routes = information.generate_edges();
    REQUIRE(airports.size()=8);
    REQUIRE(routes.size()=8);
    REQUIRE(airports[0]=="Akureyri Airport");
    REQUIRE(airports[1]=="Egilsstaðir Airport");
    REQUIRE(airports[2]=="Hornafjörður Airport");
    REQUIRE(airports[3]=="Húsavík Airport");
    REQUIRE(airports[4]=="Ísafjörður Airport");
    REQUIRE(airports[5]=="Keflavik Airport");
    REQUIRE(airports[6]=="Patreksfjörður Airport");
    REQUIRE(airports[7]=="Reykjavik Airport");

    REQUIRE(routes[0].first=="Akureyri Airport");
    REQUIRE(routes[0].second=="Egilsstaðir Airport");
    REQUIRE(routes[1].first=="Keflavik International Airport");
    REQUIRE(routes[1].second=="Patreksfjörður Airport");
    REQUIRE(routes[2].first=="Hornafjörður Airport");
    REQUIRE(routes[2].second=="Ísafjörður Airport");
    REQUIRE(routes[3].first=="Keflavik International Airport");
    REQUIRE(routes[3].second=="Hornafjörður Airport");
}


TEST_CASE("try read correct airport and routes, some airports need to be delete", "[weight=0][part=1]") {

    info_container information("../tests/information_test_airport2.txt", "../tests/information_test_routes2.txt");
    information.read();
    information.clean();
    std::vector<Vertex> airports = information.generate_vertices();
    std::vector<std::pair<Vertex, Vertex>> routes = information.generate_edges();
    REQUIRE(airports.size()=7);
    REQUIRE(routes.size()=8);
    REQUIRE(airports[0]=="Akureyri Airport");
    REQUIRE(airports[1]=="Egilsstaðir Airport");
    REQUIRE(airports[2]=="Hornafjörður Airport");
    REQUIRE(airports[3]=="Ísafjörður Airport");
    REQUIRE(airports[4]=="Keflavik Airport");
    REQUIRE(airports[5]=="Patreksfjörður Airport");

    REQUIRE(routes[0].first=="Akureyri Airport");
    REQUIRE(routes[0].second=="Egilsstaðir Airport");
    REQUIRE(routes[1].first=="Keflavik International Airport");
    REQUIRE(routes[1].second=="Hornafjörður Airport");
}*/
