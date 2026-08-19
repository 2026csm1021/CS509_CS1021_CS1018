#include "MaxFlow.h"

#include <queue>
#include <functional>
#include <algorithm>
#include <climits>

using namespace std;

namespace
{
    struct Edge
    {
        int to;
        long long cap;
        int rev;   
    };

    void addEdge(vector<vector<Edge>>& adj, int u, int v, long long cap)
    {
        Edge forward{v, cap, (int)adj[v].size()};
        Edge backward{u, 0, (int)adj[u].size()};
        adj[u].push_back(forward);
        adj[v].push_back(backward);
    }

    bool bfsLevels(const vector<vector<Edge>>& adj, int source, int sink, vector<int>& level)
    {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[source] = 0;
        q.push(source);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (const auto& e : adj[u])
            {
                if (e.cap > 0 && level[e.to] < 0)
                {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }

        return level[sink] >= 0;
    }

    
    long long sendFlow(vector<vector<Edge>>& adj, vector<int>& level, vector<int>& it,
                        int u, int sink, long long pushed)
    {
        if (u == sink)
        {
            return pushed;
        }

        for (int& i = it[u]; i < (int)adj[u].size(); i++)
        {
            Edge& e = adj[u][i];

            if (e.cap > 0 && level[e.to] == level[u] + 1)
            {
                long long d = sendFlow(adj, level, it, e.to, sink, min(pushed, e.cap));

                if (d > 0)
                {
                    e.cap -= d;
                    adj[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }

        return 0;
    }
}

MaxFlowResult maxFlowMinCut(const CSR& graph, int source, int sink)
{
    int V = graph.V;
    vector<vector<Edge>> adj(V);

    
    for (int u = 0; u < V; u++)
    {
        int start = graph.row_ptr[u];
        int end = graph.row_ptr[u + 1];

        for (int i = start; i < end; i++)
        {
            addEdge(adj, u, graph.col_idx[i], graph.values[i]);
        }
    }

    
    vector<int> level(V), it(V);
    long long maxFlow = 0;

    while (bfsLevels(adj, source, sink, level))
    {
        fill(it.begin(), it.end(), 0);

        long long pushed;
        while ((pushed = sendFlow(adj, level, it, source, sink, LLONG_MAX)) > 0)
        {
            maxFlow += pushed;
        }
    }

    
    vector<bool> visited(V, false);
    queue<int> q;
    visited[source] = true;
    q.push(source);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (const auto& e : adj[u])
        {
            if (e.cap > 0 && !visited[e.to])
            {
                visited[e.to] = true;
                q.push(e.to);
            }
        }
    }

    MaxFlowResult result;
    result.maxFlow = maxFlow;

    for (int u = 0; u < V; u++)
    {
        if (visited[u])
        {
            result.sourceSide.push_back(u);
        }
        else
        {
            result.sinkSide.push_back(u);
        }
    }

   
    for (int u = 0; u < V; u++)
    {
        if (!visited[u])
        {
            continue;
        }

        int start = graph.row_ptr[u];
        int end = graph.row_ptr[u + 1];

        for (int i = start; i < end; i++)
        {
            int v = graph.col_idx[i];

            if (!visited[v])
            {
                result.cutEdges.push_back({u, v, graph.values[i]});
            }
        }
    }

    return result;
}
