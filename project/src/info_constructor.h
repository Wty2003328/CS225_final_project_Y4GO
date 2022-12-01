#pragma once
#include <string>
#include <vector>
#include "math.h"
#define pi 3.1415926535897932384626433832795
#define EARTH_RAD 6378.137 //unit: km
//calculate distance in unit of km
;

class info_container
{
public:
	info_container(std::string airports, std::string routes);
	void clean();
	void read();
	std::vector<std::string> generate_vertices();
	std::vector<std::pair<std::string,std::string>> generate_edges();
	std::vector<double> calculate_dist();
	double cal_dist(double longitude1, double latitude1, double longitude2, double latitude2);
private:

};