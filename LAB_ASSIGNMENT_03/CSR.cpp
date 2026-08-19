#include "CSR.h"

using namespace std;

CSR convertToCSR(const Graph& graph)
{
    CSR csr;

    csr.V = graph.V;
    csr.E = graph.E;

    csr.row_ptr.resize(csr.V + 1);
    csr.row_ptr[0] = 0;

    for (int u = 0; u < csr.V; u++)
    {
        csr.row_ptr[u + 1] = csr.row_ptr[u] + (int)graph.adj[u].size();
    }

    int totalEntries = csr.row_ptr[csr.V];
    csr.col_idx.resize(totalEntries);
    csr.values.resize(totalEntries);

    int index = 0;
    for (int u = 0; u < csr.V; u++)
    {
        for (const auto& edge : graph.adj[u])
        {
            csr.col_idx[index] = edge.first;
            csr.values[index] = edge.second;
            index++;
        }
    }

    return csr;
}
