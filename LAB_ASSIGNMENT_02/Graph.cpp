#include "make_csr.h"
using namespace std;
#include "Graph.h"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

void connectedComponents(CSRGraph &G)
{
    auto start = high_resolution_clock::now();

    vector<int> component(G.V, -1);

    int componentCount = 0;

    for (int u = 0; u < G.V; u++){
        if (component[u] != -1)
            continue;

        vector<int> stack;

        stack.push_back(u);
        component[u] = componentCount;

        // DFS
        while (!stack.empty()){
            int current = stack.back();
            stack.pop_back();

            for (int i = G.row_ptr[current];i < G.row_ptr[current + 1];i++)
            {
                int neighbour = G.col_idx[i]; 
                if (component[neighbour] == -1){
                    component[neighbour] = componentCount;
                    stack.push_back(neighbour);
                }
            }
        }

        componentCount++;
    }

    auto end = high_resolution_clock::now();

    auto executionTime = duration_cast<milliseconds>(end - start);

    cout << "Algorithm: Connected Components"<< endl;
    cout << "Number of components: "<< componentCount<< endl;

    cout << "Vertex Component" << endl;

    for (int i = 0; i < G.V; i++){
        cout << i << "  "<< component[i]<< endl;
    }

    cout << "Execution time: "<< executionTime.count()<< " ms" << endl;
}