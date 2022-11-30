#pragma once
//graph constructer
//vector of string: vertices
//vector of double: edges weights
//vector of string: edges
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include "edge.h"
#include "graph.h"
class container
{ 
	public:
		container(std::vector<std::string>&vertices, std::vector<std::pair<std::string,std::string>>&edges, std::vector<double>&distances);
		container(std::vector<std::string>&vertices, std::vector<std::pair<std::string,std::string>>&edges);
		Graph inner;
		container();
		std::vector<Vertex> solvebyBFS(std::vector<Vertex> &airports, Vertex start, Vertex end);
};