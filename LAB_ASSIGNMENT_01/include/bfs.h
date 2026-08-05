#ifndef BFS_H
#define BFS_H

#include <bits/stdc++.h>
#include <fstream>
#include "csr.h"

using namespace std;

void BFS(int source,
         vector<int> &row_ptr,
         vector<int> &col_idx,
         int V,
         ostream &out);

#endif