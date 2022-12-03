#pragma once
#include <string>
#include <vector>
#include "math.h"

#include <utility>
#include <iostream>
#include <map>
#include <set>
#include <cassert>
#include <fstream>
#include <utility>

#define pi 3.1415926535897932384626433832795
#define EARTH_RAD 6378.137 //unit: km
//calculate distance in unit of km

class info_container
{
public:
	info_container(std::string & airports, std::string & routes);
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

	int info_container::divide(const std::string &line, char ch, std::vector<std::string> &temp);
	std::string TrimRight(const std::string & str);
	std::string TrimLeft(const std::string & str);
	std::string Trim(const std::string & str);

	std::vector<std::string> generate_vertices();
	std::vector<std::pair<std::string,std::string>> generate_edges();
	std::vector<double> calculate_dist();
	double cal_dist(double longitude1, double latitude1, double longitude2, double latitude2);

	struct airports {
		std::string name_;
		std::string code_;
		std::string latitude_;
		std::string longtitude_;
	};

private:
    std::string airports_;
	std::string routes_;
};