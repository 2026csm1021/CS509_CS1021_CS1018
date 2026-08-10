#include <iostream>
#include <filesystem>

#include "make_csr.h"
#include "Graphs.h"

namespace fs = std::filesystem;

using namespace std;

int main()
{
    string testcase_dir = "testcases/input";
    string output_dir = "testcases/output";

    if (!fs::exists(testcase_dir))
    {
        cout << "[ERROR] Testcase directory not found." << endl;
        return 1;
    }

    fs::create_directory(output_dir);

    int processed = 0;
    int skipped = 0;

    for (const auto &entry : fs::directory_iterator(testcase_dir))
    {
        if (!entry.is_regular_file())
            continue;

        string input_path = entry.path().string();

        string filename = entry.path().stem().string();

        string output_path =
            output_dir + "/output_" + filename + ".txt";

        CSRGraph g;

        if (!make_csr(input_path, g))
        {
            skipped++;
            continue;
        }

        FILE *output_file;

        output_file = fopen(output_path.c_str(), "w");

        if (output_file == NULL)
        {
            cout << "[ERROR] Cannot create "
                 << output_path << endl;

            skipped++;
            continue;
        }

        fprintf(output_file,
                "===== %s =====\n\n",
                filename.c_str());

        fprintf(output_file,
                "Vertices : %d\n",
                g.V);

        fprintf(output_file,
                "Edges : %d\n",
                g.E);

        fprintf(output_file,
                "Source : %d\n\n",
                g.source);

        BFS(g.source, g, output_file);

        fprintf(output_file, "\n");

        DFS(g.source, g, output_file);

        fprintf(output_file, "\n");

        SSSP(g.source, g, output_file);

        fclose(output_file);

        cout << "[OK] "
             << filename
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