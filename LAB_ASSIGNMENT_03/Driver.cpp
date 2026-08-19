#include<bits/stdc++.h>

#include "GradientDescent.h"
#include "Graph.h"
#include "CSR.h"
#include "MaxFlow.h"


using namespace std;
using namespace chrono;
namespace fs = std::filesystem;

struct GDInput
{
    int degree;
    vector<double> coefficients;
    double initialX;
    double learningRate;
    double tolerance;
    int maxIterations;
};

GDInput readGDInput(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
        throw runtime_error("Could not open input file: " + filename);

    GDInput in;
    string word;

    file >> word >> in.degree;
    if (!file || word != "DEGREE")
        throw runtime_error("Expected DEGREE line.");
    if (in.degree < 0)
        throw runtime_error("Invalid degree: must be positive.");

    file >> word;
    if (!file || word != "COEFFICIENTS")
        throw runtime_error("Expected COEFFICIENTS line.");

    string coeffLine;
    getline(file, coeffLine);
    stringstream ss(coeffLine);
    double c;
    while (ss >> c)
        in.coefficients.push_back(c);

    if ((int)in.coefficients.size() != in.degree + 1)
        throw runtime_error("COEFFICIENTS count (" + to_string(in.coefficients.size()) +
                             ") does not match degree + 1 (" + to_string(in.degree + 1) + ").");

    file >> word >> in.initialX;
    if (!file || word != "INITIAL_X")
        throw runtime_error("Expected INITIAL_X line.");

    file >> word >> in.learningRate;
    if (!file || word != "LEARNING_RATE")
        throw runtime_error("Expected LEARNING_RATE line.");
    if (in.learningRate <= 0)
        throw runtime_error("LEARNING_RATE must be positive.");

    file >> word >> in.tolerance;
    if (!file || word != "TOLERANCE")
        throw runtime_error("Expected TOLERANCE line.");
    if (in.tolerance <= 0)
        throw runtime_error("TOLERANCE must be positive.");

    file >> word >> in.maxIterations;
    if (!file || word != "MAX_ITERATIONS")
        throw runtime_error("Expected MAX_ITERATIONS line.");
    if (in.maxIterations <= 0)
        throw runtime_error("MAX_ITERATIONS must be positive.");

    return in;
}

void printGDResult(ostream& out, int degree, const GDResult& result, double timeMs)
{
    out << fixed << setprecision(10);
    out << "Algorithm: Gradient Descent\n";
    out << "Degree: " << degree << "\n";
    out << "Final x: " << result.finalX << "\n";
    out << "Final f(x): " << result.finalFx << "\n";
    out << "Iterations: " << result.iterations << "\n";
    out << "Converged: " << (result.converged ? "true" : "false") << "\n";
    out << "Execution time: " << timeMs << " ms\n";
}

void runGradientDescent(const string& inputFile, const string& outputFile)
{
    GDInput in = readGDInput(inputFile);

    auto start = high_resolution_clock::now();
    GDResult result = gradientDescent(in.coefficients, in.initialX,
                                       in.learningRate, in.tolerance, in.maxIterations);
    auto stop = high_resolution_clock::now();
    double timeMs = duration<double, milli>(stop - start).count();

    printGDResult(cout, in.degree, result, timeMs);

    ofstream outFile(outputFile);
    if (!outFile.is_open())
        throw runtime_error("Could not create output file: " + outputFile);
    printGDResult(outFile, in.degree, result, timeMs);
    outFile.close();

    cout << "\nOutput saved to: " << outputFile << "\n";
}


void printMaxFlowResult(ostream& out, const Graph& graph, const MaxFlowResult& result, double timeMs)
{
    long long cutCapacity = 0;
    for (const auto& e : result.cutEdges)
        cutCapacity += e.capacity;

    out << "Algorithm: Maxflow-Mincut\n";
    out << "Source: " << graph.source << "\n";
    out << "Sink: " << graph.sink << "\n";
    out << "Maximum flow: " << result.maxFlow << "\n";
    out << "Minimum cut capacity: " << cutCapacity << "\n";

    out << "Source side:";
    for (int v : result.sourceSide) out << " " << v;
    out << "\n";

    out << "Sink side:";
    for (int v : result.sinkSide) out << " " << v;
    out << "\n";

    out << "Cut edges:\n";
    for (const auto& e : result.cutEdges)
        out << e.u << " " << e.v << " " << e.capacity << "\n";

    out << "Execution time: " << timeMs << " ms\n";
}

void runMaxFlow(const string& inputFile, const string& outputFile)
{
    Graph graph = readGraph(inputFile);
    validateGraph(graph);

    CSR csr = convertToCSR(graph);

    auto start = high_resolution_clock::now();
    MaxFlowResult result = maxFlowMinCut(csr, graph.source, graph.sink);
    auto stop = high_resolution_clock::now();
    double timeMs = duration<double, milli>(stop - start).count();

    printMaxFlowResult(cout, graph, result, timeMs);

    ofstream outFile(outputFile);
    if (!outFile.is_open())
        throw runtime_error("Could not create output file: " + outputFile);
    printMaxFlowResult(outFile, graph, result, timeMs);
    outFile.close();

    cout << "\nOutput saved to: " << outputFile << "\n";
}


void listInputFiles(const string& inputDir, const string& prefix, vector<string>& files)
{
    files.clear();

    if (!filesystem::exists(inputDir) || !filesystem::is_directory(inputDir))
        throw runtime_error("Input directory not found: " + inputDir);

    for (const auto& entry : filesystem::directory_iterator(inputDir))
    {
        if (!entry.is_regular_file())
            continue;

        string name = entry.path().filename().string();
        if (entry.path().extension() == ".txt" && name.rfind(prefix, 0) == 0)
            files.push_back(name);
    }

    sort(files.begin(), files.end());
}

int chooseInputFile(const string& inputDir, const string& prefix, const string& title,
                    string& inputFile, string& outputFile)
{
    vector<string> files;
    listInputFiles(inputDir, prefix, files);

    if (files.empty())
        throw runtime_error("No " + title + " input files found in " + inputDir);

    cout << "\nAvailable " << title << " input files:\n";
    for (size_t i = 0; i < files.size(); ++i)
        cout << "  " << (i + 1) << ". " << files[i] << "\n";

    cout << "\nEnter file number: ";
    int fileNumber;
    if (!(cin >> fileNumber))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("invalid file number.");
    }

    if (fileNumber < 1 || fileNumber > static_cast<int>(files.size()))
        throw runtime_error("file number must be between 1 and " + to_string(files.size()) + ".");

    const string& filename = files[fileNumber - 1];
    inputFile = (filesystem::path(inputDir) / filename).string();

    filesystem::create_directories("output");
    outputFile = (filesystem::path("output") / filename).string();

    cout << "\nSelected input : " << filename << "\n";
    cout << "Output file    : " << outputFile << "\n";

    return fileNumber;
}

void runMenu()
{
    while (true)
    {
        cout << "\n===== CS509 Assignment 3 - Buddy Task =====\n";
        cout << "1. Run Gradient Descent\n";
        cout << "2. Run Maxflow-Mincut\n";
        cout << "3. Exit\n";
        cout << "\nEnter choice: ";

        int choice;
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: invalid choice.\n";
            continue;
        }

        if (choice == 3)
        {
            cout << "Exiting.\n";
            return;
        }

        if (choice != 1 && choice != 2)
        {
            cout << "Error: choice must be 1, 2 or 3.\n";
            continue;
        }

        try
        {
            string inputFile;
            string outputFile;

            if (choice == 1)
            {
                chooseInputFile("input", "gd_", "Gradient Descent", inputFile, outputFile);
                runGradientDescent(inputFile, outputFile);
            }
            else
            {
                chooseInputFile("input", "maxflow_", "Maxflow-Mincut", inputFile, outputFile);
                runMaxFlow(inputFile, outputFile);
            }
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << "\n";
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc == 4)
    {
        string algorithm = argv[1];
        string inputFile = argv[2];
        string outputFile = argv[3];

        try
        {
            if (algorithm == "gd")
                runGradientDescent(inputFile, outputFile);
            else if (algorithm == "maxflow")
                runMaxFlow(inputFile, outputFile);
            else
            {
                cerr << "Error: first argument must be 'gd' or 'maxflow'.\n";
                return 1;
            }
        }
        catch (const exception& e)
        {
            cerr << "Error: " << e.what() << "\n";
            return 1;
        }

        return 0;
    }

    runMenu();

    return 0;
}

