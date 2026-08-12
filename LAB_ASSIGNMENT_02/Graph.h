#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "make_csr.h"

using namespace std;

void connectedComponents(CSRGraph &G);

long long triangleCounting(CSRGraph &G);

long long betweennessCentrality(CSRGraph &G);

#endif