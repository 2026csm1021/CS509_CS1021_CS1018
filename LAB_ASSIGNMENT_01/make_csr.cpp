#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge
{
    int source;
    int destination;
    int weight;
};

int main()
{
    vector<edge> edges;
    edge e;

    int V,E;

    FILE *input_file = fopen("input.txt", "r");
    if (input_file == NULL)
    {
        cout << "[ERROR] Can't input file " << endl;
        return 1;
    }

    fscanf(input_file,"%d %d",&V,&E);

    while (fscanf(input_file, "%d %d %d", &e.source, &e.destination, &e.weight) == 3)
    {
        edges.push_back(e);

    }


    vector<int> count(V, 0);

    for (auto &e : edges)
        count[e.source]++;

    vector<int> row_ptr(V + 1);

    row_ptr[0] = 0;

    for (int i = 1; i <= V; i++)
        row_ptr[i] = row_ptr[i - 1] + count[i - 1];



    vector<int> col_idx;
    vector<int> values;

    for (auto &e : edges)
    {
        col_idx.push_back(e.destination);
        values.push_back(e.weight);
    }

    // fclose(input_file);
    // int i = 0;
    // auto temp = edges[0];
    // row_ptr.push_back(i);

    // for (auto &a : edges)
    // {
    //     if (a.source != temp.source)
    //     {
    //         temp = a;
    //         row_ptr.push_back(i);
    //     }
    //     col_ptr.push_back(a.destination);
    //     values.push_back(a.weight);
    //     i++;
    // }

    cout << "COL_PTR : ";
    for (auto a : col_idx)
        cout << a << " ";
    cout << endl;
    cout << "ROW_PTR : ";
    for (auto a : row_ptr)
        cout << a << " ";
    cout << endl;
    cout << "Values : ";
    for (auto a : values)
        cout << a << " ";

    cout << endl;
}