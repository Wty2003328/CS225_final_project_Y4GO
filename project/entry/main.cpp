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
    
    bool find=false;
    while(find==false)
    {
        cout << "Your place of departure:" << endl;
        getline(cin,start);
        start="\""+start+"\"";
        for(auto it=airports.begin();it!=airports.end();++it)
        {
            if(*it==start)
            find=true;
        }
        if(find==false)
        {
            cout << "Invalid Input!" << endl;
        }
    }
    find=false;
    while(find==false)
    {
        cout << "Your destination:" << endl;
        getline(cin,end);
        end="\""+end+"\"";
        for(auto it=airports.begin();it!=airports.end();++it)
        {
            if(*it==start)
            find=true;
        }
        if(find==false)
        {
            cout << "Invalid Input!" << endl;
        }
    }
    
    

    vector<Vertex> min_transfer = calculator.solvebyBFS(start, end);
    vector<Vertex> min_dist = calculator.solvebyDij(start, end);
    vector<string> min_transfer_airlineinfo=information.airlineinfo(min_transfer);
    vector<string> min_dist_airlineinfo=information.airlineinfo(min_dist);
    cout << "\n"<<"minimum transfer route:" << endl;
    for (auto it = min_transfer.begin(); it != min_transfer.end(); ++it)
    {
        cout << *it <<endl;
    }
     cout<<"Airlines available for corresponding route section: "<<endl;
    for (unsigned idx=0;idx<min_transfer_airlineinfo.size();idx++)
    {
       cout<<"Section"<<idx+1<<": "<<min_transfer_airlineinfo[idx]<<endl;
    }
    cout <<"\n"<<"minimum distance route:" << endl;
    for (auto it = min_dist.begin(); it != min_dist.end(); ++it)
    {
        cout << *it <<endl;
    }
    cout<<"Airlines available for corresponding route section: "<<endl;
    for (unsigned idx=0;idx<min_dist_airlineinfo.size();idx++)
    {
        cout<<"Section"<<idx+1<<": "<<min_dist_airlineinfo[idx]<<endl;
    }
    return 0;
}

