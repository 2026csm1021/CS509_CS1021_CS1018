#ifndef MAXFLOW_H
#define MAXFLOW_H

#include "CSR.h"
#include <vector>

using namespace std;


struct CutEdge
{
    int u;
    int v;
    int capacity;
};

struct MaxFlowResult
{
    long long maxFlow;
    vector<int> sourceSide;
    vector<int> sinkSide;
    vector<CutEdge> cutEdges;
};


MaxFlowResult maxFlowMinCut(const CSR& graph, int source, int sink);

#endif
