#include "heap_fordijkstra.h"
#include "graph.h"
//not sure about limits.h
#include <limits.h>
#include "dist.h"

int dijkstra(Graph original, Vertex staring, Vertex ending) {
    //set up map for distance and previous vertex
    map<Vertex, int> d;
    map<Vertex, Vertex> p;
    //not sure whether the graph can be used like that in for loop
    for(Vertex v: original) {
        d[v] = INT_MAX;
        p[v] = NULL;
    }
    d[starting] = 0;
    
    //set up queue and new graph for traversal 
    vector<Vertex> temp = g.getVertices();
    heap q = new heap(temp);
    Graph T = new Graph(true,true);

    //finding shortest path
    while(q.empty() == false) {
        //removemin form q
        Vertex u = q.pop();
        T.insertVertex(u);
        //i tried to find out the neighbor of vertex u by iterator, not sure whether it will work or not
        for(auto it = u.begin();it != u.end(); it++) {
            if(T.vertexExists(it) == false) {
                //maybe we need another new distance function or a helper method for the original distance
                if(distance(u, it) + d[u] <d[it]) {
                    d[it] = distance(u, it) + d[u];
                    p[it] = u;
                }
            }
        }
    }
    //temporaily return the total number of distance, may change it according to the final output we want
    return d[ending];
}