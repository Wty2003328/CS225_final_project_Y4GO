#include <cmath>
#include <cstdlib>
#include <sstream>
#include <fenv.h>
#include <signal.h>
#include <vector>
#include <stdlib.h>
#include <unordered_map>

#include "info_constructor.h"
#include <algorithm>

double info_container::cal_dist(double longitude1, double latitude1, double longitude2, double latitude2)
{
	double rad_longtitude1 = pi * longitude1 / 180;
	double rad_latitude1 = pi * latitude1 / 180;
	double rad_longtitude2 = pi * longitude2 / 180;
	double rad_latitude2 = pi * latitude2 / 180;
	double rad_diff_longtitude =rad_longtitude1 - rad_longtitude2;
	double rad_diff_latitude = rad_latitude1 - rad_latitude2;
	double dist = 2 * asin(sqrt(pow(sin(rad_diff_latitude / 2), 2) + cos(rad_latitude1) * cos(rad_latitude2) * pow(sin(rad_diff_longtitude / 2), 2)));
	dist = dist * EARTH_RAD;
	return dist;
}

info_container::info_container(std::string airports, std::string routes)
{
	airports_ = airports;
	routes_ = routes;
}

void info_container::clean()
{
    cleanAirport();
	cleanRoute();
	return;
}

void info_container::cleanAirport() {
    for (unsigned long i = 0; i < airport_v.size(); ) {  
        double latitude = stod(airport_v[i][7]);
        double longitude = stod(airport_v[i][8]);
        std::string::size_type findName;
        if ((findName = airport_v[i][1].find("Air Base")) == std::string::npos) {    //delete airbase
            if((latitude > -90 && latitude < 90) && (longitude > -180 && longitude < 180)) {    //delete beyond
				if(airport_v[i].size() == 8) {    //if information lost, then delete it
					i ++ ;
				}
			}       
        }
        else {
            airport_v.erase(airport_v.begin() + i);
        }
    }
}

void info_container::cleanRoute() {   //delete the route that src/dest not in the list
    for (unsigned long i = 0; i < route_v.size(); ) { 
        if (std::count(AirportCode.begin(), AirportCode.end(), route_v[i][3]) != 0
            && std::count(AirportCode.begin(), AirportCode.end(), route_v[i][5]) != 0) {
                i ++ ;
        }
        else {
            route_v.erase(route_v.begin() + i);
        }
    }
}

void info_container::read()
{
    airport_v = transferFile(airports_);
	route_v = transferFile(routes_);

	return;
}

std::string info_container::readfile(const std::string& filename){
	std::ifstream in(filename);

	std::stringstream strStream;
	if (in.is_open()) {
		strStream << in.rdbuf();
	}
	return strStream.str();
}

std::vector<std::vector<std::string>> info_container::transferFile(const std::string & filename){
    std::string newString = readfile(filename);
    std::vector<std::string> rows;
    
    int num_row = divide(newString, '\n', rows);
    std::vector<std::vector<std::string>> newV2D;

    for(int i = 0;i < num_row;i ++) {
        std::vector<std::string> cols;
        newV2D.push_back({});

        int num_col = divide(rows[i], ',', cols);
        for(int j = 0;j < num_col;j ++) {
            std::string single = Trim(cols[j]);
            newV2D[i].push_back(single);
        }    
    }
    return newV2D;
}

void info_container::getAirportName() {
    for(unsigned long i = 0; i < airport_v.size();i++) {    
        AirportName[i] = airport_v[i][1];
    }
}
void info_container::getAirportCode() {
    for(unsigned long i = 0; i < airport_v.size();i++) {    
        AirportCode[i] = airport_v[i][0];
    }
}

void info_container::getRoute() {
    for(unsigned long i = 0; i < route_v.size();i++) {    
        allRoute[i].first = route_v[i][3];     //first--src, second--dest
        allRoute[i].second = route_v[i][5];
    }
}

void info_container::getStruct() {
    for(unsigned long i = 0; i < airport_v.size();i++) {
        std::string id = airport_v[i][0];
        struct airports s;
        s.code_ = airport_v[i][0];
        s.name_ = airport_v[i][1];
        s.latitude_ = airport_v[i][6];
        s.longtitude_ = airport_v[i][7];
    }
}

std::vector<std::string> info_container::generate_vertices()
{    
    return std::vector<std::string>();
}

std::vector<std::pair<std::string,std::string>> info_container::generate_edges()
{
    return std::vector<std::pair<std::string,std::string>>();
}

std::vector<double> info_container::calculate_dist()
{
    return std::vector<double>();
}

int info_container::divide(const std::string &line, char ch, std::vector<std::string> &temp) {
    std::string newLine = line;
    std::string::size_type pos;
    while((pos = newLine.find(ch)) != std::string::npos) {
        temp.push_back(newLine.substr(0,pos));
        newLine.erase(0,pos+1);  
    }
    temp.push_back(newLine);
    return temp.size();
}

std::string info_container::TrimRight(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

std::string info_container::TrimLeft(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

std::string info_container::Trim(const std::string & str) {
    std::string tmp = str;
    return TrimLeft(TrimRight(str));
}
