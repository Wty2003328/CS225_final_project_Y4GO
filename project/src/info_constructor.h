#pragma once
#include <string>
#include <vector>
#include "math.h"

#include <utility>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <fstream>
#include <utility>

#define pi 3.1415926535897932384626433832795
#define EARTH_RAD 6378.137 //unit: km
//calculate distance in unit of km

class info_container
{
public:
	info_container(std::string & airports, std::string & routes, std::string & airlines);
	void getAirportName();
	void getAirportCode();
	void getRoute();
	void getStruct();

	std::vector<std::vector<std::string>> airport_v;
	std::vector<std::vector<std::string>> route_v;
	std::vector<std::string> AirportName;
	std::vector<std::string> AirportCode;
	std::vector<std::pair<std::string, std::string>> allRoute;

	void clean();
	void cleanAirport();
	void cleanRoute();

	void read();
	std::string readfile(const std::string & filename);
	std::vector<std::vector<std::string>> transferFile(const std::string & filename);

	int divide(const std::string &line, char ch, std::vector<std::string> &temp);
	std::string TrimRight(const std::string & str);
	std::string TrimLeft(const std::string & str);
	std::string Trim(const std::string & str);

	std::vector<std::string> generate_vertices();
	std::vector<std::pair<std::string,std::string>> generate_edges();
	std::vector<double> calculate_dist();
	double cal_dist(double longitude1, double latitude1, double longitude2, double latitude2);

	struct airport_s {
		std::string airport_name_;
		std::string city_;
		std::string airport_country_;
		std::string airport_IATA_;
		std::string airport_ICAO_;
		std::string latitude_;
		std::string longtitude_;
		std::string altitude_;
	};

	struct route_s {
		std::string airline_;
		std::string src_code_;
		std::string dest_code_;
	};

	struct airline_s {
		std::string airline_name_;
		std::string airline_IATA_;
		std::string airline_ICAO_;
		std::string airline_country_;
		std::string active_;
	};

	std::vector<airport_s> airports_s;
	std::vector<route_s> routes_s;
	std::vector<airline_s> airline_s;
	std::vector<std::pair<std::string, std::string>> route_pairs;

private:
    std::string airports_;
	std::string routes_;
	std::string airlines_;

	std::unordered_map<std::string, std::vector<std::string>> code_airport;
    std::unordered_map<std::string, std::vector<std::string>> name_airport;
    std::unordered_map<std::string, std::string> pair_route;

};