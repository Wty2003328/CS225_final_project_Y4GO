#pragma once
//graph constructer
//vector of string: vertices
//vector of double: edges weights
//vector of string: edges
#include <vector>
#include <string>
#include "edge.h"
#include "graph.h"
class container
{ 
	public:
		container(std::vector<std::string>&vertices, std::vector<std::pair<std::string,std::string>>&edges, std::vector<double>&distances);
		Graph inner;
		container();
		std::vector<std::vector<std::string>> adjcentmatrix;
};