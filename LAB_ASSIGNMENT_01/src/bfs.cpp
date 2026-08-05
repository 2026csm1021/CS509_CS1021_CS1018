#include "bfs.h"
#include <chrono>

using namespace std;
using namespace chrono;

void BFS(int source,
         vector<int> &row_ptr,
         vector<int> &col_idx,
         int V,
         ostream &out)
{
    vector<bool> visited(V, false);
    queue<int> q;

    auto start = high_resolution_clock::now();

    visited[source] = true;
    q.push(source);

    out << "Algorithm : BFS" << endl;
    out << "Source : " << source << endl;
    out << "Traversal : ";

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        out << u << " ";

        for (int i = row_ptr[u]; i < row_ptr[u + 1]; i++)
        {
            int v = col_idx[i];

            if (!visited[v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    auto stop = high_resolution_clock::now();

    double time = duration<double, milli>(stop - start).count();

    out << endl;
    out << "Execution Time : " << time << " ms" << endl;
}