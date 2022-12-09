#include "graph_constructor.h"

/*
    graph container initializer with distances
    input: vector of vertices, vector of edges, vector of distances
    output: nothing
    construct graph in private member using input vertices, edges and distances
*/
graph_container::graph_container(std::vector<Vertex> &vertices, std::vector<std::pair<Vertex, Vertex>> &edges, std::vector<double> &distances) : inner(Graph(true, true))
{
    for (auto it = vertices.begin(); it != vertices.end(); ++it)
    {
        inner.insertVertex(*it);
        airports.push_back(*it);
    }
    for (auto it = edges.begin(); it != edges.end(); ++it)
    {
        inner.insertEdge(it->first, it->second);
        inner.setEdgeWeight(it->first, it->second, distances[it - edges.begin()]);
    }
}

/*
    graph container initializer withour distances
    input: vector of vertices, vector of edges
    output: nothing
    construct graph in private member using input vertices, edges, distances are all set as 1
*/
graph_container::graph_container(std::vector<Vertex> &vertices, std::vector<std::pair<Vertex, Vertex>> &edges) : inner(Graph(false, true))
{
    for (auto it = vertices.begin(); it != vertices.end(); ++it)
    {
        inner.insertVertex(*it);
        airports.push_back(*it);
    }
    for (auto it = edges.begin(); it != edges.end(); ++it)
    {
        inner.insertEdge(it->first, it->second);
    }
}

/*
    graph solver by BFS
    input: two vertices, a start and an end
    output: a vector of vertices that passed by when travelling from start to end
    using an undered map as visited for checking and storing predecessor
*/
std::vector<Vertex> graph_container::solvebyBFS(Vertex start, Vertex end)
{
    std::unordered_map<Vertex, Vertex> visited;
    std::vector<Vertex> solution;
    for (auto it = airports.begin(); it != airports.end(); ++it)
    {
        visited[*it] = "NONE";
    }
    std::queue<Vertex> solve;
    solve.push(start);
    visited.find(start)->second = "start";
    while (!solve.empty())
    {
        Vertex v = solve.front();
        solve.pop();
        if (v == end)
            break;
        std::vector<Vertex> neighbours = inner.getAdjacent(v);
        for (auto it = neighbours.begin(); it != neighbours.end(); ++it)
        {
            auto it1 = visited.find(*it);
            if (it1->second == "NONE")
            {
                solve.push(*it);
                it1->second = v;
            }
        }
    }
    auto it = visited.find(end);
    if (it->second == "NONE")
    {
        solution.insert(solution.begin(), "Destination not reachable!");
        return solution;
    }
    solution.insert(solution.begin(), end);
    while (it->second != "start")
    {
        solution.insert(solution.begin(), it->second);
        it = visited.find(it->second);
    }
    return solution;
}

/*
    graph solver by dijkstra's algorithm
    input: two vertices, a start and an end
    output: a vector of vertices that passed by when travelling from start to end
*/
std::vector<Vertex> graph_container::solvebyDij(Vertex start, Vertex end)
{
    std::unordered_map<Vertex, double> d;
    std::unordered_map<Vertex, Vertex> p;
    std::vector<Vertex> nodes = inner.getVertices();
    for (unsigned i = 0; i < nodes.size(); i++)
    {
        d[nodes[i]] = INT_MAX;
        p[nodes[i]] = "0";
    }
    d[start] = 0;
    std::priority_queue<std::pair<double, Vertex>, vector<std::pair<double, Vertex>>, std::greater<std::pair<double, Vertex>>> queue_;
    queue_.push(make_pair(0, start));

    while (queue_.empty() == false)
    {
        Vertex u = queue_.top().second;
        queue_.pop();
        std::vector<Vertex> temp = inner.getAdjacent(u);
        for (unsigned i = 0; i < temp.size(); i++)
        {

            Vertex v = temp[i];
            double length = inner.getEdge(u, v).getWeight();
            if (d[v] > d[u] + length)
            {
                d[v] = d[u] + length;
                p[v] = u;
                queue_.push(make_pair(d[v], v));
            }
        }
    }
    Vertex find = end;
    std::vector<Vertex> output;
    output.push_back(end);
    int i = 0;
    while (p[find] != start)
    {
        i++;
        output.push_back(p[find]);
        find = p[find];
        if (i > 1000)
        {
            std::vector<Vertex> output1;
            output1.push_back("Destination not reachable!");
            return output1;
        }
    }
    output.push_back(start);

    std::vector<Vertex> output2;
    for (unsigned i = 0; i < output.size(); i++)
    {
        output2.push_back(output[output.size() - 1 - i]);
    }
    return output2;
}

std::vector<Vertex> graph_container::solvebyDeltaStepping(Vertex start, Vertex end)
{
    /*
    std::unordered_map<Vertex, double> dist;
    std::unordered_map<Vertex, Vertex> prev;
    vector<Vertex> nodes = inner.getVertices();

    vector<vector<Vertex>> bucket;
    double delta;

    for (unsigned i = 0; i < nodes.size(); i++)
    {
        dist[nodes[i]] = INT_MAX;
        prev[nodes[i]] = "0";
    }

    dist[start] = 0;
    bucket[0].push_back(start);

    extend(start, dist[start], end);

    while (bucket.size() != 0)
    {
        int curr = 0;
        vector<Vertex> temp;
        for (unsigned i = 0; i < bucket.size(); i++)
        {
            if (bucket[i].size() != 0)
            {
                curr = i;
                break;
            }
        }
        while (bucket[curr].size() != 0)
        {
            findRoutes(bucket[curr], "shorter than delta");
            for (unsigned i = 0; i < bucket[curr].size(); i++)
            {
                for (unsigned j = 0; j < bucket[curr].size(); j++)
                {
                    if (bucket[curr][i] == temp[j])
                    {
                        break;
                    }
                }
                temp.push_back(bucket[curr][i]);
            }
            bucket[curr].clear();
        }
        findRoutes(bucket[curr], "longer than delta");
    }

    // copy Dijk
    Vertex find = end;
    vector<Vertex> output_reverse, output_fail, output_success;
    output_reverse.push_back(end);
    int i = 0;
    while (prev[find] != start)
    {
        i++;
        output_reverse.push_back(prev[find]);
        find = prev[find];
        if (i > 1000)
        {
            vector<Vertex> output_fail;
            output_fail.push_back("Destination not reachable!");
            return output_fail;
        }
    }
    output_reverse.push_back(start);

    for (unsigned i = 0; i < output_reverse.size(); i++)
    {
        output_success.push_back(output_reverse[output_reverse.size() - 1 - i]);
    }

    return output_success;
    // end copy
    */
    return std::vector<Vertex>();
}

void graph_container::findRoutes(vector<Vertex> newBucket, string kind)
{
    /*
    std::vector<unordered_map<Vertex, double>> all_length;
    if (kind == "shorter than delta")
    {
        for (unsigned i = 0; i < newBucket.size(); i++)
        {
            vector<Vertex> newAdj = inner.getAdjacent(u);
            for (unsigned j = 0; j < newAdj.size(); j++)
            {
                double adj_length = inner.getEdge(newBucket[i], newAdj[j]).getWeight();
                if (adj_length <= delta)
                {
                    extend(newAdj[j], dist[newBucket[i]] + adj_length, newBucket[i]);
                }
            }
        }
    }

    if (kind == "longer than delta")
    {
        for (unsigned i = 0; i < newBucket.size(); i++)
        {
            vector<Vertex> newAdj = inner.getAdjacent(u);
            for (unsigned j = 0; j < newAdj.size(); j++)
            {
                double adj_length = inner.getEdge(newBucket[i], newAdj[j]).getWeight();
                if (adj_length > delta)
                {
                    extend(newAdj[j], dist[newBucket[i]] + adj_length);
                }
            }
        }
    }
    return all_length;
    */
}

std::vector<Vertex> graph_container::extend(Vertex nowV, double changed_length, Vertex p)
{
    /*
    if (changed_length < dist[nowV])
    {
        for (auto it = bucket[dist[nowV] / delta].begin(); it != bucket[d[nowV] / delta].end(); it++)
        {
            if (dist[nowV] != INT_MAX && it == nowV)
            {
                bucket[dist[nowV] / delta].erase(it);
                it--;
            }
        }
        bucket[changed_length / delta].push_back(nowV);

        dist[nowV] = changed_length;
        prev[nowV] = p;
    }
    */
    return std::vector<Vertex>();
}
