#include <iostream>
#include <vector>
#include "info_constructor.h"
#include "graph_constructor.h"

using namespace std;

int main()
{
    info_container information("airport.txt", "routes.txt");
    information.read();
    information.clean();
    vector<Vertex> airports = information.generate_vertices();
    vector<pair<Vertex, Vertex>> routes = information.generate_edges();
    vector<double> dist = information.calculate_dist();
    container calculator(airports, routes, dist);
    string start,end;
    cout << "Your place of departure:" << endl;
    cin >> start;
    cout << "Your destination:" << endl;
    cin >> end;
    vector<Vertex> min_transfer = calculator.solvebyBFS(start, end);
    vector<Vertex> min_dist = calculator.solvebyDij(start, end);
    cout << "minimum transfer route:" << endl;
    for (auto it = min_transfer.begin(); it != min_transfer.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << "minimum distance route:" << endl;
    for (auto it = min_dist.begin(); it != min_dist.end(); ++it)
    {
        cout << *it << " ";
    }
    return 0;
}

