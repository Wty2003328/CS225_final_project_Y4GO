#include "graph_constructor.h"
container::container(std::vector<Vertex>&vertices, std::vector<std::pair<Vertex,Vertex>>&edges, std::vector<double>&distances):inner(Graph(true,true))
{
	for(auto it=vertices.begin();it!=vertices.end();++it)
	{
		inner.insertVertex(*it);
        airports.push_back(*it);
	}
	for(auto it=edges.begin();it!=edges.end();++it)
	{
		inner.insertEdge(it->first,it->second);
		inner.setEdgeWeight(it->first,it->second,distances[it-edges.begin()]);
	}
	
}
container::container(std::vector<Vertex>&vertices, std::vector<std::pair<Vertex,Vertex>>&edges):inner(Graph(false,true))
{
	for(auto it=vertices.begin();it!=vertices.end();++it)
	{
		inner.insertVertex(*it);
        airports.push_back(*it);
	}
	for(auto it=edges.begin();it!=edges.end();++it)
	{
		inner.insertEdge(it->first,it->second);
	}
	
}
std::vector<Vertex> container::solvebyBFS(Vertex start, Vertex end)
{
    std::unordered_map<Vertex,Vertex> visited;
    std::vector<Vertex> solution;
    for(auto it=airports.begin();it!=airports.end();++it)
    {
        visited[*it]="NONE";
    }
    std::queue<Vertex> solve;
    solve.push(start);
    visited.find(start)->second="start";
    while (!solve.empty())
    {
        Vertex v = solve.front();
        solve.pop();
        if(v==end)
        break;
        std::vector<Vertex> neighbours=inner.getAdjacent(v);
        for(auto it=neighbours.begin();it!=neighbours.end();++it)
        {
            auto it1=visited.find(*it);
            if(it1->second=="NONE")
            {
                solve.push(*it);
                it1->second=v;
            }
        }
    }
    auto it=visited.find(end);
    if (it->second == "NONE")
    {
        solution.insert(solution.begin(), "Destination not reachable!");
        return solution;
    }
        
    solution.insert(solution.begin(),end);
    while(it->second!="start")
    {
        solution.insert(solution.begin(),it->second);
        it=visited.find(it->second);
    }
    return solution;
}

std::vector<Vertex> container::solvebyDij(Vertex start, Vertex end)
{
    return std::vector<Vertex>();
}