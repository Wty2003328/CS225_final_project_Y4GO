#include <iostream>
#include "info_constructor.h"
#include "graph_constructor.h"
using namespace std;
int main()
{
    info_container information("../data/airports.txt", "../data/routes.txt","../data/airlines.txt");
    information.read();
    information.clean();
    vector<Vertex> airports = information.generate_vertices();
    vector<pair<Vertex, Vertex>> routes = information.generate_edges();
    vector<double> dist = information.calculate_dist();
    container calculator(airports, routes, dist);
    string start,end;
    cout << "Your place of departure:" << endl;
    getline(cin,start);
    bool find=false;
    for(auto it=airports.begin();it!=airports.end();++it)
    {
        if(*it==start)
        find=true;
    }
    if(find==false)
    {
        cout << "Invalid Input!" << endl;
        return 0;
    }
    cout << "Your destination:" << endl;
    getline(cin,end);
    find=false;
    for(auto it=airports.begin();it!=airports.end();++it)
    {
        if(*it==end)
        find=true;
    }
    if(find==false)
    {
        cout << "Invalid Input!" << endl;
        return 0;
    }
    vector<Vertex> min_transfer = calculator.solvebyBFS(start, end);
    vector<Vertex> min_dist = calculator.solvebyDij(start, end);
    cout << "\n"<<"minimum transfer route:" << endl;
    for (auto it = min_transfer.begin(); it != min_transfer.end(); ++it)
    {
        cout << *it <<endl;
    }
    cout <<"\n"<<"minimum distance route:" << endl;
    for (auto it = min_dist.begin(); it != min_dist.end(); ++it)
    {
        cout << *it <<endl;
    }
    return 0;
}

