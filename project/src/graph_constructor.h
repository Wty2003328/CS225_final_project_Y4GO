#pragma once
//graph constructer
//vector of string: vertices
//vector of double: edges weights
//vector of string: edges
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <map>
#include "../lib/cs225/graph.h"
class container
{ 
public:
		container(std::vector<std::string>&vertices, std::vector<std::pair<std::string,std::string>>&edges, std::vector<double>&distances);
		container(std::vector<std::string>&vertices, std::vector<std::pair<std::string,std::string>>&edges);
		
		container();
		std::vector<Vertex> solvebyBFS(Vertex start, Vertex end);
		std::vector<Vertex> solvebyDij(Vertex start, Vertex end);
private:
		Graph inner;
		std::vector<Vertex> airports;
};
