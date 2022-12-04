#include "graph_constructor.h"
using namespace std;
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
    map<Vertex, double> d;
    map<Vertex, Vertex> p;
    vector<Vertex> nodes = inner.getVertices();
    for(unsigned i = 0; i < nodes.size(); i++) {
        d[nodes[i]] = INT_MAX;
        p[nodes[i]] = "0";
    }
    d[start] = 0;
    
    priority_queue<pair<double, Vertex>, vector<pair<double, Vertex>>, greater<pair<double, Vertex>> > queue_;
    queue_.push(make_pair(0, start));
  
    while (queue_.empty() == false) {
        
        Vertex u = queue_.top().second;
        queue_.pop();

        vector<Vertex> temp = inner.getAdjacent(u);
        for(unsigned i = 0; i < temp.size();i++) {
           
            Vertex v = temp[i];
            double length = inner.getEdge(u,v).getWeight();
            if (d[v] > d[u] + length) {
                d[v] = d[u] + length;
                p[v] = u;
                queue_.push(make_pair(d[v], v));
            }
        }
    }
    Vertex find = end;
    vector<Vertex> output;
    output.push_back(end);
    int i = 0;
    while(p[find] != start) {
        i++;
        output.push_back(p[find]);
        find = p[find];
        if(i > 1000) {
             vector<Vertex> output1;
            output1.push_back("Destination not reachable!");
            return output1;
        }
    }
    output.push_back(start);


    vector<Vertex> output2;
    for(unsigned i = 0; i < output.size();i++) {
        output2.push_back(output[output.size() - 1 - i]);
    }

    return output2;
}