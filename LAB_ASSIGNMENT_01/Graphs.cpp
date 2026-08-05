#include "Graphs.h"

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <limits>
#include <chrono>

using namespace std;
using namespace chrono;

void BFS(int source, CSRGraph &g, FILE *output_file)
{
    vector<bool> visited(g.V, false);

    queue<int> q;

    auto start = high_resolution_clock::now();

    visited[source] = true;
    q.push(source);

    fprintf(output_file, "Algorithm : BFS\n");
    fprintf(output_file, "Source : %d\n", source);
    fprintf(output_file, "Traversal : ");

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        fprintf(output_file, "%d ", u);

        for (int i = g.row_ptr[u]; i < g.row_ptr[u + 1]; i++)
        {
            int v = g.col_idx[i];

            if (!visited[v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    auto stop = high_resolution_clock::now();

    double time =
        duration<double, milli>(stop - start).count();

    fprintf(output_file, "\n");
    fprintf(output_file, "Execution Time : %.6f ms\n", time);
}

void DFS(int source, CSRGraph &g, FILE *output_file)
{
    vector<bool> visited(g.V, false);

    stack<int> st;

    auto start = high_resolution_clock::now();

    st.push(source);

    fprintf(output_file, "Algorithm : DFS\n");
    fprintf(output_file, "Source : %d\n", source);
    fprintf(output_file, "Traversal : ");

    while (!st.empty())
    {
        int u = st.top();
        st.pop();

        if (visited[u])
            continue;

        visited[u] = true;

        fprintf(output_file, "%d ", u);

        for (int i = g.row_ptr[u + 1] - 1;
             i >= g.row_ptr[u];
             i--)
        {
            int v = g.col_idx[i];

            if (!visited[v])
                st.push(v);
        }
    }

    auto stop = high_resolution_clock::now();

    double time =
        duration<double, milli>(stop - start).count();

    fprintf(output_file, "\n");
    fprintf(output_file, "Execution Time : %.6f ms\n", time);
}

void SSSP(int source, CSRGraph &g, FILE *output_file)
{
    const long long INF = numeric_limits<long long>::max();

    vector<long long> distance(g.V, INF);

    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > pq;

    auto start = high_resolution_clock::now();

    distance[source] = 0;

    pq.push(make_pair(0, source));

    while (!pq.empty())
    {
        pair<long long, int> temp = pq.top();
        pq.pop();

        long long d = temp.first;
        int u = temp.second;

        if (d != distance[u])
            continue;

        for (int i = g.row_ptr[u];
             i < g.row_ptr[u + 1];
             i++)
        {
            int v = g.col_idx[i];
            int w = g.values[i];

            if (distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;

                pq.push(make_pair(distance[v], v));
            }
        }
    }

    auto stop = high_resolution_clock::now();

    double time =
        duration<double, milli>(stop - start).count();

    fprintf(output_file, "Algorithm : SSSP\n");
    fprintf(output_file, "Method : Dijkstra\n");
    fprintf(output_file, "Source : %d\n", source);

    fprintf(output_file, "Distance :\n");

    for (int i = 0; i < g.V; i++)
    {
        if (distance[i] == INF)
            fprintf(output_file,
                    "%d -> INF\n",
                    i);
        else
            fprintf(output_file,
                    "%d -> %lld\n",
                    i,
                    distance[i]);
    }

    fprintf(output_file,
            "Execution Time : %.6f ms\n",
            time);
}