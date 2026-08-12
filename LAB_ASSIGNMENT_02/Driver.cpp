#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include "make_csr.h"
#include "Graph.h"

using namespace std;
namespace fs = std::filesystem;

int main()
{
   
    cout << "========================================" << endl;
    cout << "           GRAPH ALGORITHM              " << endl;
    cout << "========================================" << endl;

    cout << endl;
    cout << "Select algorithm:" << endl;
    cout << "1. Connected Components" << endl;
    cout << "2. Triangle Counting" << endl;
    cout << "3. Betweenness Centrality" << endl;
    cout << endl;

    int choice;

    cout << "Enter your choice: ";
    cin >> choice;

    if (choice < 1 || choice > 3)
    {
        cout << "Invalid choice." << endl;
        return 1;
    }

    string algorithmFolder;
    string algorithmName;

    if (choice == 1)
    {
        algorithmFolder = "ConnectedComponents";
        algorithmName = "Connected Components";
    }
    else if (choice == 2)
    {
        algorithmFolder = "TriangleCount";
        algorithmName = "Triangle Counting";
    }
    else if (choice == 3)
    {
        algorithmFolder = "BetweennessCentrality";
        algorithmName = "Betweenness Centrality";
    }

    string inputDir = "testcases/input/" + algorithmFolder;
    string outputDir = "testcases/output/" + algorithmFolder;



    if (!fs::exists(inputDir))
    {
        cout << "Error: Input directory not found: "
             << inputDir << endl;

        return 1;
    }


    if (!fs::exists(outputDir))
    {
        fs::create_directories(outputDir);
    }

    cout << endl;
    cout << "Processing: " << algorithmName << endl;
    cout << "Input Directory: " << inputDir << endl;
    cout << "Output Directory: " << outputDir << endl;
    cout << "========================================" << endl;
    cout << endl;


    vector<fs::path> inputFiles;

    for (const auto &entry : fs::directory_iterator(inputDir))
    {
        if (entry.is_regular_file())
        {
            inputFiles.push_back(entry.path());
        }
    }


    sort(inputFiles.begin(), inputFiles.end());

    if (inputFiles.empty())
    {
        cout << "No input files found in "
             << inputDir << endl;

        return 1;
    }


    for (const auto &inputPath : inputFiles)
    {
        cout << endl;
        cout << "Processing: "
             << inputPath.string() << endl;

        CSRGraph G;

        // Convert input graph to CSR
        if (!make_csr(inputPath.string(), G))
        {
            cout << "Error reading "
                 << inputPath.string() << endl;

            continue;
        }


        string fileName = inputPath.stem().string();

        fs::path outputPath =
            fs::path(outputDir) /
            (fileName + "_output.txt");

        ofstream output(outputPath);

        if (!output)
        {
            cout << "Error creating output file: "
                 << outputPath.string() << endl;

            continue;
        }


        streambuf *oldCout = cout.rdbuf(output.rdbuf());


        if (choice == 1)
        {
            connectedComponents(G);
        }
        else if (choice == 2)
        {
            long long executionTime =
                triangleCounting(G);

            cout << "Execution time: "
                 << executionTime
                 << " ms" << endl;
        }
        else if (choice == 3)
        {
            long long executionTime =
                betweennessCentrality(G);

            cout << "Execution time: "
                 << executionTime
                 << " ms" << endl;
        }

   
        cout.rdbuf(oldCout);

        output.close();

        cout << "Output written to: "
             << outputPath.string() << endl;
    }

    cout << endl;
    cout << "All input files processed." << endl;

    return 0;
}