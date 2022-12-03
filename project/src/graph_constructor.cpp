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
		inner.setEdgeWeight(it->first,it->second,distances[it->edges.begin()]);
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
    map<Vertex, int> d;
    map<Vertex, Vertex> p;
    vector<Vertex> nodes = inner.getVertices();
    for(unsigned i = 0; i < nodes.size(); i++) {
        d[nodes[i]] = INT_MAX;
        p[nodes[i]] = "0";
    }
    d[start] = 0;
    
    //set up queue and new graph for traversal 
    vector<Vertex> heap_;
    make_heap(heap_.begin(), heap_.end());
    Graph T = new Graph(true,true);

    //finding shortest path
    while(heap_.empty() == false) {
        //removemin form q
         Vertex u = heap_[0];
        pop_heap(heap_.begin(), heap_.end());
        T.insertVertex(u);
        //check aroung the neighbor
        vector<Vertex> temp = inner.getAdjacent(u);
        for(unsigned i = 0; i < temp.size();i++) {
            if(T.vertexExists(temp[i]) == false) {
                //if(distance(u, it) + d[u] <d[it]) {
                    if(1 + d[u] <d[temp[i]])
                    //d[it] = distance(u, it) + d[u];
                    d[temp[i]] = 1 + d[u];
                    p[temp[i]] = u;
                    heap_.push_back(temp[i]);
                    push_heap(heap_.begin(), heap_.end());
                }
            }
        }
    //temporaily return the total number of distance, may change it according to the final output we want
    Vertex find = end;
    vector<Vertex> output;
    int i = 0;
    output.push_back(end);
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
    for(unsigned i = 0; i < output.size();i++) {
        std::cout << output[i] << std::endl;
    }
    return output;
}
