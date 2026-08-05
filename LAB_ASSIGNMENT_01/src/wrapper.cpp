#include <bits/stdc++.h>
#include "csr.h"
#include "bfs.h"
#include <fstream>
using namespace std;

int main()
{
    // Read graph from input file
    Graph graph = readGraph("input.txt");

    // Convert Adjacency List to CSR
    CSRGraph csr = buildCSR(graph);
    
    ofstream fout("output.txt");

    if (!fout)
    {
        cout << "Cannot create output file!" << endl;
        return 1;
    }

    // Print CSR (optional)
    cout << "ROW_PTR : ";
    fout << "ROW_PTR : ";
    for (int x : csr.row_ptr){
        cout << x << " ";
        fout << x << " ";
    }
    cout << endl;
    fout << endl;

    cout << "COL_IDX : ";
    fout << "COL_IDX : ";

    for(int x : csr.col_idx)
    {
        cout << x << " ";
        fout << x << " ";
    }

    cout << endl;
    fout << endl;

    // output file 
    BFS(graph.source,
        csr.row_ptr,
        csr.col_idx,
        csr.totalVertices,
        fout);

    return 0;
}