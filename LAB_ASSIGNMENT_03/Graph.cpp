#include "Graph.h"
#include <fstream>

using namespace std;

Graph readGraph(const string& filename)
{
    Graph graph;

    
    ifstream file(filename);
    if (!file)
    {
        throw runtime_error("Could not open input file: " + filename);
    }

    if (!(file >> graph.V >> graph.E))
    {
        throw runtime_error("Invalid input file: could not read V and E.");
    }

    if (graph.V <= 0)
    {
        throw runtime_error("Invalid input file: V must be a positive integer.");
    }

    graph.adj.resize(graph.V);

    for (int i = 0; i < graph.V; i++)
    {
        int u, degree;

        if (!(file >> u >> degree))
        {
            throw runtime_error("Invalid input file: could not read vertex id/degree.");
        }

        if (u < 0 || u >= graph.V)
        {
            throw runtime_error("Invalid input file: vertex id " + to_string(u) + " is out of range.");
        }

        if (degree < 0)
        {
            throw runtime_error("Invalid input file: negative degree for vertex " + to_string(u));
        }

        for (int j = 0; j < degree; j++)
        {
            int v, cap;

            if (!(file >> v >> cap))
            {
                throw runtime_error("Invalid input file: could not read neighbour/capacity for vertex " + to_string(u));
            }

            if (v < 0 || v >= graph.V)
            {
                throw runtime_error("Invalid input file: neighbour id " + to_string(v) + " for vertex " + to_string(u) + " is out of range.");
            }

            graph.adj[u].push_back({v, cap});
        }
    }

    string word;

    file >> word >> graph.source;
    if (!file || word != "SOURCE")
    {
        throw runtime_error("Invalid input file: expected SOURCE line.");
    }

    file >> word >> graph.sink;
    if (!file || word != "SINK")
    {
        throw runtime_error("Invalid input file: expected SINK line.");
    }

    file.close();

    return graph;
}

void validateGraph(const Graph& graph)
{
    if (graph.source < 0 || graph.source >= graph.V)
    {
        throw runtime_error("Invalid graph: source vertex out of range.");
    }

    if (graph.sink < 0 || graph.sink >= graph.V)
    {
        throw runtime_error("Invalid graph: sink vertex out of range.");
    }

    if (graph.source == graph.sink)
    {
        throw runtime_error("Invalid graph: source and sink must be different vertices.");
    }

    for (int u = 0; u < graph.V; u++)
    {
        for (const auto& e : graph.adj[u])
        {
            int v = e.first;
            int cap = e.second;

            if (v < 0 || v >= graph.V)
            {
                throw runtime_error("Invalid graph: neighbour id out of range at vertex " + to_string(u));
            }

            if (cap < 0)
            {
                throw runtime_error("Invalid graph: negative capacity on edge (" + to_string(u) + ", " + to_string(v) + ").");
            }
        }
    }
}
