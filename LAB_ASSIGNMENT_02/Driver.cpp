#include <bits/stdc++.h>
#include "make_csr.h"
#include "Graph.h"

using namespace std;

int main()
{
    string inputFiles[] = {
        "testcases/case1.txt",
        "testcases/case2.txt",
        "testcases/case3.txt",
        "testcases/case4.txt"};

    string outputFiles[] = {
        "output/case1_output.txt",
        "output/case2_output.txt",
        "output/case3_output.txt",
        "output/case4_output.txt"};

    for (int i = 0; i < 4; i++)
    {
        CSRGraph G;

        if (!make_csr(inputFiles[i], G))
        {
            cout << "Error reading "
                 << inputFiles[i] << endl;
            continue;
        }

        ofstream output(outputFiles[i]);

        streambuf *old = cout.rdbuf(output.rdbuf());

        connectedComponents(G);

        cout.rdbuf(old);

        output.close();

        cout << "Done: "
             << inputFiles[i] << endl;
    }

    return 0;
