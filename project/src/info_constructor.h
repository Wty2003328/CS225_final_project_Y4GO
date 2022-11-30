#pragma once
#include <string>
#include <vector>
class info_container
{
public:
	info_container(std::string airports, std::string routes);
	void clean();
	void read();
	std::vector<std::string> generate_vertices();
	std::vector<std::pair<std::string,std::string>> generate_edges();
	std::vector<double> calculate_dist();
private:

};