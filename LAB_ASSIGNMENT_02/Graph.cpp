using namespace std;
#include <iostream>
#include <vector>
#include <chrono>
#include <queue>
#include "make_csr.h"

using namespace std;
using namespace chrono;

void connectedComponents(CSRGraph &G)
{
    auto start = high_resolution_clock::now();

    vector<int> component(G.V, -1);

    int componentCount = 0;

    for (int u = 0; u < G.V; u++){
        if (component[u] != -1)
            continue;

        vector<int> stack;

        stack.push_back(u);
        component[u] = componentCount;

        // DFS
        while (!stack.empty()){
            int current = stack.back();
            stack.pop_back();

            for (int i = G.row_ptr[current];i < G.row_ptr[current + 1];i++)
            {
                int neighbour = G.col_idx[i]; 
                if (component[neighbour] == -1){
                    component[neighbour] = componentCount;
                    stack.push_back(neighbour);
                }
            }
        }

        componentCount++;
    }

    auto end = high_resolution_clock::now();

    auto executionTime = duration_cast<milliseconds>(end - start);

    cout << "Algorithm: Connected Components"<< endl;
    cout << "Number of components: "<< componentCount<< endl;

    cout << "Vertex Component" << endl;

    for (int i = 0; i < G.V; i++){
        cout << i << "  "<< component[i]<< endl;
    }

    cout << "Execution time: "<< executionTime.count()<< " ms" << endl;
}



long long betweennessCentrality(CSRGraph &G)
{
    auto start = high_resolution_clock::now();

    int V = G.V;

    vector<double> BC(V, 0.0);

    for (int source = 0; source < V; source++)
    {
        vector<int> S;
        vector<vector<int>> P(V);
        vector<long long> sigma(V, 0);
        vector<int> dist(V, -1);
        vector<double> delta(V, 0.0);

        queue<int> Q;

        sigma[source] = 1;
        dist[source] = 0;

        Q.push(source);

        // BFS
        while (!Q.empty())
        {
            int v = Q.front();
            Q.pop();

            S.push_back(v);

            // Traverse CSR neighbours
            for (int i = G.row_ptr[v];
                 i < G.row_ptr[v + 1];
                 i++)
            {
                int w = G.col_idx[i];

                if (dist[w] == -1)
                {
                    dist[w] = dist[v] + 1;
                    Q.push(w);
                }

                if (dist[w] == dist[v] + 1)
                {
                    sigma[w] += sigma[v];
                    P[w].push_back(v);
                }
            }
        }

        // Accumulation
        while (!S.empty())
        {
            int w = S.back();
            S.pop_back();

            for (int v : P[w])
            {
                delta[v] +=
                    ((double)sigma[v] / sigma[w])
                    * (1.0 + delta[w]);
            }

            if (w != source)
            {
                BC[w] += delta[w];
            }
        }
    }

    auto end = high_resolution_clock::now();

    auto executionTime =
        duration_cast<milliseconds>(end - start);

    cout << "Algorithm: Betweenness Centrality" << endl;
    cout << "Vertex Centrality" << endl;

    for (int v = 0; v < V; v++)
    {
        cout << v << "  "
             << BC[v] << endl;
    }

    return executionTime.count();
}



long long triangleCounting(CSRGraph &G)
{
    auto start = high_resolution_clock::now();

    long long triangleCount = 0;

    for (int u = 0; u < G.V; u++)
    {
        for (int i = G.row_ptr[u];
             i < G.row_ptr[u + 1];
             i++)
        {
            int v = G.col_idx[i];

            for (int j = i + 1;
                 j < G.row_ptr[u + 1];
                 j++)
            {
                int w = G.col_idx[j];

                // Check whether v and w are connected
                for (int k = G.row_ptr[v];
                     k < G.row_ptr[v + 1];
                     k++)
                {
                    if (G.col_idx[k] == w)
                    {
                        triangleCount++;
                        break;
                    }
                }
            }
        }
    }

    // Every triangle is counted 3 times
    triangleCount /= 3;

    auto end = high_resolution_clock::now();

    auto executionTime =
        duration_cast<milliseconds>(end - start);

    cout << "Algorithm: Triangle Counting" << endl;
    cout << "Number of triangles: "
         << triangleCount << endl;

    return executionTime.count();
}