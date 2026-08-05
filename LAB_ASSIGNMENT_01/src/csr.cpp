#include "csr.h"

Graph readGraph(string filename)
{
    Graph graph;

    ifstream file(filename);

    if (!file)
    {
        cout << "Error: Cannot open input file!" << endl;
        exit(1);
    }

    file >> graph.V >> graph.E;

    graph.adj.resize(graph.V);

    for (int i = 0; i < graph.V; i++)
    {
        int vertex, degree;

        file >> vertex >> degree;

        for (int j = 0; j < degree; j++)
        {
            int neighbour;
            file >> neighbour;

            graph.adj[vertex].push_back(neighbour);
        }
    }

    string temp;
    file >> temp >> graph.source;

    file.close();

    return graph;
}

CSRGraph buildCSR(Graph graph)
{
    CSRGraph csr;

    csr.totalVertices = graph.V;

    csr.row_ptr.push_back(0);

    for (int i = 0; i < graph.V; i++)
    {
        for (int neighbour : graph.adj[i])
        {
            csr.col_idx.push_back(neighbour);
        }

        csr.row_ptr.push_back(csr.col_idx.size());
    }

    return csr;
}