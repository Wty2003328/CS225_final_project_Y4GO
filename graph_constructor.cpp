#include "graph_constructor.h"
container::container(std::vector<Vertex>&vertices, std::vector<std::pair<Vertex,Vertex>>&edges, std::vector<double>&distances):inner(Graph(true,true))
{
	for(auto it=vertices.begin();it!=vertices.end();++it)
	{
		inner.insertVertex(*it);
	}
	for(auto it=edges.begin();it!=edges.end();++it)
	{
		inner.insertEdge(it->first,it->second);
		inner.setEdgeWeight(it->first,it->second,distances[it-edges.begin()]);
	}
	adjcentmatrix.resize(vertices.size(),std::vector<Vertex>());
	for(auto it=vertices.begin();it!=vertices.end();++it)
	{
		adjcentmatrix[it-vertices.begin()]=inner.getAdjacent(*it);
	}
	
}


