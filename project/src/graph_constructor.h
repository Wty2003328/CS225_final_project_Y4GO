#pragma once
// graph constructer
// vector of string: vertices
// vector of double: edges weights
// vector of string: edges
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include "../lib/cs225/graph.h"
class graph_container
{
public:
	graph_container(std::vector<std::string> &vertices, std::vector<std::pair<std::string, std::string>> &edges, std::vector<double> &distances);
	graph_container(std::vector<std::string> &vertices, std::vector<std::pair<std::string, std::string>> &edges);

	graph_container();
	std::vector<Vertex> solvebyBFS(Vertex start, Vertex end);
	std::vector<Vertex> solvebyDij(Vertex start, Vertex end);
	std::vector<Vertex> solvebyDeltaStepping(Vertex start, Vertex end);
private:
	Graph inner;
	std::vector<Vertex> airports;
	void findRoutes(vector<Vertex> newBucket, string kind);
	std::vector<Vertex> extend(Vertex nowV, double changed_length, Vertex p);
	
};
