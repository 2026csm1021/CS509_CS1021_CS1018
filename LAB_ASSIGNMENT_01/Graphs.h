#ifndef GRAPHS_H
#define GRAPHS_H

#include <cstdio>
#include "make_csr.h"

void BFS(int source, CSRGraph &g, FILE *output_file);

void DFS(int source, CSRGraph &g, FILE *output_file);

void SSSP(int source, CSRGraph &g, FILE *output_file);

#endif