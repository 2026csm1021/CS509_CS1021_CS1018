#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int source;
    int destination;
    int weight;
};

void BFS(int source,
         vector<int> &row_ptr,
         vector<int> &col_idx,
         int V)
{
    vector<bool> visited(V, false);
    queue<int> q;

    visited[source] = true;
    q.push(source);

    cout << "\nBFS Traversal : ";

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        cout << u << " ";

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

    cout << endl;
}

int main()
{
    vector<edge> edges;
    edge e;

    int V, E;

    FILE *input_file = fopen("input.txt", "r");

    if (input_file == NULL)
    {
        cout << "[ERROR] Can't open input file." << endl;
        return 1;
    }

    fscanf(input_file, "%d %d", &V, &E);

    while (fscanf(input_file, "%d %d %d",
                  &e.source,
                  &e.destination,
                  &e.weight) == 3)
    {
        edges.push_back(e);
    }

    fclose(input_file);

    // Sort edges by source vertex
    sort(edges.begin(), edges.end(), [](edge a, edge b)
    {
        if (a.source == b.source)
            return a.destination < b.destination;

        return a.source < b.source;
    });

    vector<int> row_ptr(V + 1, 0);
    vector<int> col_idx;
    vector<int> values;

    int currentVertex = 0;

    for (auto &e : edges)
    {
        while (currentVertex < e.source)
        {
            row_ptr[currentVertex + 1] = col_idx.size();
            currentVertex++;
        }

        col_idx.push_back(e.destination);
        values.push_back(e.weight);
    }

    while (currentVertex < V)
    {
        row_ptr[currentVertex + 1] = col_idx.size();
        currentVertex++;
    }

    cout << "ROW_PTR : ";
    for (int x : row_ptr)
        cout << x << " ";

    cout << endl;

    cout << "COL_IDX : ";
    for (int x : col_idx)
        cout << x << " ";

    cout << endl;

    cout << "VALUES : ";
    for (int x : values)
        cout << x << " ";

    cout << endl;

    int source = 0;

    BFS(source, row_ptr, col_idx, V);

    return 0;
}