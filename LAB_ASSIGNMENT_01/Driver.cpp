#include <iostream>
#include <filesystem>
#include <cstdio>
#include <string>

#include "make_csr.h"
#include "Graphs.h"

namespace fs = std::filesystem;

using namespace std;

int main()
{
    string testcase_dir = "testcases/input";
    string output_dir = "testcases/outputs";

    // Check whether input directory exists
    if (!fs::exists(testcase_dir))
    {
        cout << "[ERROR] Testcase directory not found: "
             << testcase_dir << endl;
        return 1;
    }

    // Create output directory if it does not exist
    if (!fs::exists(output_dir))
    {
        fs::create_directory(output_dir);
    }

    int processed = 0;
    int skipped = 0;

    // Process every file inside testcases/input
    for (const auto &entry : fs::directory_iterator(testcase_dir))
    {
        if (!entry.is_regular_file())
            continue;

        string input_path = entry.path().string();

        // Get filename without extension
        string filename = entry.path().stem().string();

        // Output file:
        // testcases/outputs/output_case1.txt
        string output_path =
            output_dir + "/output_" + filename + ".txt";

        CSRGraph g;

        // Convert input graph to CSR
        if (!make_csr(input_path, g))
        {
            cout << "[SKIPPED] " << filename
                 << " - Invalid input" << endl;

            skipped++;
            continue;
        }

        // Open output file
        FILE *output_file = fopen(output_path.c_str(), "w");

        if (output_file == NULL)
        {
            cout << "[ERROR] Cannot create "
                 << output_path << endl;

            skipped++;
            continue;
        }

        // Testcase heading
        fprintf(output_file,
                "===== %s =====\n\n",
                filename.c_str());

        // Graph information
        fprintf(output_file,
                "Vertices : %d\n",
                g.V);

        fprintf(output_file,
                "Edges : %d\n",
                g.E);

        fprintf(output_file,
                "Source : %d\n\n",
                g.source);

        // BFS
        BFS(g.source, g, output_file);

        fprintf(output_file, "\n");

        // DFS
        DFS(g.source, g, output_file);

        fprintf(output_file, "\n");

        // Single Source Shortest Path
        SSSP(g.source, g, output_file);

        // Close output file
        fclose(output_file);

        cout << "[OK] "
             << filename
             << " -> "
             << output_path
             << endl;

        processed++;
    }

    cout << endl;

    cout << "Processed : "
         << processed
         << endl;

    cout << "Skipped : "
         << skipped
         << endl;

    return 0;
}