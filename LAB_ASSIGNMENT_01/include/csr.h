#ifndef CSR_H
#define CSR_H

#include <bits/stdc++.h>
using namespace std;

struct Graph
{
    int V;
    int E;
    int source;
    vector<vector<int>> adj;
};

struct CSRGraph
{
    int totalVertices;
    vector<int> row_ptr;
    vector<int> col_idx;
};

Graph readGraph(string filename);

CSRGraph buildCSR(Graph graph);

#endif