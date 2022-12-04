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

std::vector<double> info_container::calculate_dist()
{
    std::vector<double> calculated_dists;
    
    for(unsigned i = 0; i < routes_s.size();i++) {
        auto departure=code_airport.find(routes_s[i].src_code_);
        auto arrival=code_airport.find(routes_s[i].dest_code_);
        calculated_dists.push_back(cal_dist(departure->second.longtitude_,departure->second.latitude_,
                    arrival->second.longtitude_,arrival->second.latitude_));
    }
    return calculated_dists;
}

std::vector<std::string> info_container::generate_vertices()
{    
    std::vector<std::string> result;
    for(unsigned idx=0;idx<airports_s.size();idx++)
    {
        result.push_back(airports_s[idx].airport_name_);
    }
    return result;
}

std::vector<std::pair<std::string,std::string>> info_container::generate_edges()
{
    std::vector<std::pair<std::string,std::string>> result;
    for(unsigned idx=0;idx<routes_s.size();idx++)
    {
        result.push_back(std::pair<std::string,std::string>(
            code_airport.find(routes_s[idx].src_code_)->second.airport_name_,
                code_airport.find(routes_s[idx].dest_code_)->second.airport_name_));
    }
    
    return result;
}

info_container::info_container(std::string airports, std::string routes, std::string airlines)
                :code_airport(std::unordered_map<std::string, airport_s>()),name_airport(std::unordered_map<std::string, airport_s>()),
                pair_route(std::unordered_map<std::string,std::string>()),
                code_airline(std::unordered_map<std::string, airline_s>())
{
	airports_ = airports;
	routes_ = routes;
    airlines_ = airlines;
}

void info_container::clean()
{
    cleanAirport();
    cleanAirline();
    cleanRoute();
	return;
}

void info_container::cleanAirport() {
    for(unsigned idx=0;idx<airports_s.size();idx++)
    {
        if(airports_s[idx].airport_name_==""||
            (airports_s[idx].airport_IATA_==""&&airports_s[idx].airport_ICAO_==""))
        {
            airports_s.erase(airports_s.begin()+idx);
            idx--;
        }
        else if(airports_s[idx].airport_name_.find("Airbase")!=std::string::npos)
        {
            airports_s.erase(airports_s.begin()+idx);
            idx--;
        }
        else if(airports_s[idx].airport_IATA_.length()!=5)
        {
            airports_s[idx].airport_IATA_="\\N";
            if(airports_s[idx].airport_ICAO_.length()!=6)
            {
                airports_s.erase(airports_s.begin()+idx);
                idx--;
            }
        }
        else if(airports_s[idx].airport_IATA_=="\\N"&&airports_s[idx].airport_ICAO_=="\\N")
        {
            airports_s.erase(airports_s.begin()+idx);
            idx--;
        }
        else if(airports_s[idx].longtitude_>180||airports_s[idx].longtitude_<-180)
        {
            airports_s.erase(airports_s.begin()+idx);
            idx--;
        }
        else if(airports_s[idx].latitude_>90||airports_s[idx].latitude_<-90)
        {
            airports_s.erase(airports_s.begin()+idx);
            idx--;
        }
        else if(airports_s[idx].altitude_>5500||airports_s[idx].altitude_<-500)
        {
            airports_s.erase(airports_s.begin()+idx);
            idx--;
        }
    }
    for(unsigned idx=0;idx<airports_s.size();idx++)
    {
        if(airports_s[idx].airport_IATA_!="\\N")
        {
            code_airport[airports_s[idx].airport_IATA_]=airports_s[idx];
        }
        else
        {
            code_airport[airports_s[idx].airport_ICAO_]=airports_s[idx];
        }
        name_airport[airports_s[idx].airport_name_]=airports_s[idx];
    }
}

void info_container::cleanRoute() {   
    for(unsigned idx=0;idx<routes_s.size();idx++)
    {
        if(code_airport.find(routes_s[idx].src_code_)==code_airport.end()||
            code_airport.find(routes_s[idx].dest_code_)==code_airport.end())
        {
            routes_s.erase(routes_s.begin()+idx);
            idx--;
        }
        else if(code_airline.find(routes_s[idx].airline_)==code_airline.end())
        {
            routes_s.erase(routes_s.begin()+idx);
            idx--;
        }
    }
    for(unsigned idx=0;idx<routes_s.size();idx++)
    {
        auto it=pair_route.find(routes_s[idx].src_code_+"-"+routes_s[idx].dest_code_);
        if(it==pair_route.end())
        {
            pair_route[routes_s[idx].src_code_+"-"+routes_s[idx].dest_code_]=routes_s[idx].airline_;
        }
        else
        {
            it->second=it->second+","+routes_s[idx].airline_;
        }
    }
}

void info_container::cleanAirline()
{
    for(unsigned idx=0;idx<airlines_s.size();idx++)
    {
        if(airlines_s[idx].airline_name_==""||
            (airlines_s[idx].airline_IATA_==""&&airlines_s[idx].airline_ICAO_==""))
        {
            airlines_s.erase(airlines_s.begin()+idx);
            idx--;
        }
        else if(airlines_s[idx].active_=="\"N\"")
        {
            airlines_s.erase(airlines_s.begin()+idx);
            idx--;
        }
        else if(airlines_s[idx].airline_IATA_.length()!=4)
        {
            airlines_s[idx].airline_IATA_="\\N";
            if(airlines_s[idx].airline_ICAO_.length()!=5)
            {
                airlines_s.erase(airlines_s.begin()+idx);
                idx--;
            }
        }
        else if(airlines_s[idx].airline_IATA_=="\\N"&&airlines_s[idx].airline_ICAO_=="\\N")
        {
            airlines_s.erase(airlines_s.begin()+idx);
            idx--;
        }
    }
    for(unsigned idx=0;idx<airlines_s.size();idx++)
    {
        if(airlines_s[idx].airline_IATA_!="\\N")
        {
            code_airline[airlines_s[idx].airline_IATA_]=airlines_s[idx];
        }
        else
        {
            code_airline[airlines_s[idx].airline_ICAO_]=airlines_s[idx];
        }
    }
}

void info_container::read()
{
    std::vector<std::vector<std::string>> airport_v;
	std::vector<std::vector<std::string>> route_v;
	std::vector<std::vector<std::string>> airline_v;

    airport_v = transferFile(airports_);
	route_v = transferFile(routes_);
    airline_v = transferFile(airlines_);

    for(unsigned long i = 0; i < airport_v.size();i++) {
        struct airport_s s;
        if(airport_v[i].size()<9)
        continue;
        s.city_ = airport_v[i][2];
        if(s.city_.length()>0&&s.city_[s.city_.length()-1]!='\"')
        continue;
        s.airport_name_ = airport_v[i][1];
        if(s.airport_name_.length()>0&&s.airport_name_[s.airport_name_.length()-1]!='\"')
        continue;
        s.latitude_ = stod(airport_v[i][6]);
        s.longtitude_ = stod(airport_v[i][7]);
        s.altitude_ = stod(airport_v[i][8]);
        s.airport_IATA_ = airport_v[i][4];    //3
        if(s.airport_IATA_.length()>0&&s.airport_IATA_[s.airport_IATA_.length()-1]!='\"')
        continue;
        s.airport_ICAO_ = airport_v[i][5];    //4
        if(s.airport_ICAO_.length()>0&&s.airport_ICAO_[s.airport_ICAO_.length()-1]!='\"')
        continue;
        s.airport_country_ = airport_v[i][3];
        if(s.airport_country_.length()>0&&s.airport_country_[s.airport_country_.length()-1]!='\"')
        continue;
        airports_s.push_back(s);
    }

    for(unsigned long i = 0; i < route_v.size();i++) {
        struct route_s s;
        if(route_v[i].size()<5)
        continue;
        s.airline_ = "\""+route_v[i][0]+"\"";
        s.src_code_ = "\""+route_v[i][2]+"\"";        //3 or 4
        s.dest_code_ = "\""+route_v[i][4]+"\"";       //3 or 4
        
        routes_s.push_back(s);   
    }

    for(unsigned long i = 0; i < airline_v.size();i++) {
        struct airline_s s;
        if(airline_v[i].size()<8)
        continue;
        s.airline_name_ = airline_v[i][1];
        s.airline_IATA_ = airline_v[i][3];     //2
        s.airline_ICAO_ = airline_v[i][4];     //3
        s.airline_country_ = airline_v[i][5];
        s.active_ = airline_v[i][7];

        airlines_s.push_back(s);
        
    }

    
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



int info_container::divide(const std::string &line, char ch, std::vector<std::string> &temp) {
    std::string newLine = line;
    std::string::size_type pos,check;
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