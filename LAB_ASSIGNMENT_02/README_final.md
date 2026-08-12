# CS527 Buddy assignment

## Overview

This project implements three graph analytics algorithms:

-   Triangle Counting
-   Betweenness Centrality
-   Connected Components

The input graphs are stored in edge-list format. The graph data is
processed and represented using the required graph representation before
the selected algorithm is executed.

The project also evaluates the algorithms on test graphs of different
sizes and records the output and execution time.

------------------------------------------------------------------------

## Directory Structure

``` text
LAB_ASSIGNMENT_01/
│
├── testcases/
│   ├── input/
│   │   ├── trianglecounting/
│   │   ├── betweennesscentrality/
│   │   └── connectedcomponents/
│   │
│   └── outputs/
│       ├── trianglecounting/
│       ├── betweennesscentrality/
│       └── connectedcomponents/
│
├── graph.cpp
├── graph.h
├── make_csr.cpp
├── make_csr.h
├── driver.cpp
├── run
└── README.md
```

------------------------------------------------------------------------

## Algorithms

### 1. Triangle Counting

Triangle Counting determines the total number of triangles present in
the graph.

The test cases are intended to use the following vertex counts:

``` text
10, 100, 10000, 50000, 100000
```

The output reports the total number of triangles and the execution time.

### 2. Betweenness Centrality

Betweenness Centrality calculates the centrality value of each vertex.

The test cases are intended to use the following vertex counts:

``` text
10, 100, 1000, 5000, 10000
```

The output contains the centrality value for every vertex and the
execution time.

### 3. Connected Components

Connected Components identifies the connected component to which every
vertex belongs.

The test cases are intended to use the following vertex counts:

``` text
10, 100, 10000, 50000, 100000
```

The output contains the number of components, the component assigned to
each vertex, and the execution time.

------------------------------------------------------------------------

## Input Format

The input graphs use an edge-list representation.

The first line contains:

``` text
V E
```

where:

-   `V` = number of vertices
-   `E` = number of edges

Each of the following `E` lines contains:

``` text
u v
```

where `u` and `v` are the endpoints of an edge.

Example:

``` text
5 6
0 1
0 2
1 2
1 3
2 3
3 4
```

Vertices are numbered from `0` to `V-1`.

------------------------------------------------------------------------

## Graph Representation

The input is provided as an edge list. The graph is converted into the
required internal representation before the algorithm is executed.

The CSR-related source files are:

``` text
make_csr.cpp
make_csr.h
```

The general flow is:

``` text
Edge List
    |
    v
Graph / CSR conversion
    |
    v
Selected Graph Algorithm
    |
    v
Output + Execution Time
```

------------------------------------------------------------------------

## Running the Program

Compile the project using:

``` bash
g++ -std=c++17 driver.cpp graph.cpp make_csr.cpp -o driver
```

Run the executable using:

``` bash
./driver
```

The driver processes the test cases according to the selected algorithm.

------------------------------------------------------------------------

## Output

For each test case, an output file is generated in the corresponding
output directory.

For example:

``` text
testcases/
├── input/
│   └── trianglecounting/
│       └── tc_10.txt
│
└── outputs/
    └── trianglecounting/
        └── tc_10_output.txt
```

The output contains the algorithm result followed by the execution time.

------------------------------------------------------------------------

## Performance Readings

The following are the execution results obtained for the test cases.

### Triangle Counting

| Test Case | Number of Vertices | Number of Triangles | Execution Time |
|---|---:|---:|---:|
| `tc_10.txt` | 10 | 1 | 0 ms |
| `tc_100.txt` | 100 | 2 | 0 ms |
| `tc_1000.txt` | 1,000 | 20 | 5 ms |
| `tc_5000.txt` | 5,000 | 19 | 24 ms |

### Betweenness Centrality

| Test Case | Number of Vertices | Execution Time |
|---|---:|---:|
| `bc_10.txt` | 10 | 0 ms |
| `bc_100.txt` | 100 | 16 ms |
| `bc_1000.txt` | 1,000 | 282 ms |
| `bc_5000.txt` | 5,000 | 6129 ms |

### Connected Components

| Test Case | Number of Vertices | Number of Components | Execution Time |
|---|---:|---:|---:|
| `cc_10.txt` | 10 | 2 | 0 ms |
| `cc_100.txt` | 100 | 1 | 0 ms |
| `cc_1000.txt` | 1,000 | 1 | 0 ms |
| `cc_5000.txt` | 5,000 | 1 | 1 ms |

The Triangle Counting outputs report 1, 2, 20, and 19 triangles for the
uploaded `tc_10`, `tc_100`, `tc_1000`, and `tc_5000` test cases
respectively. The corresponding execution times are 0 ms, 0 ms, 5 ms,
and 24 ms.

The Betweenness Centrality runs report execution times of 0 ms, 16 ms,
282 ms, and 6129 ms for 10, 100, 1,000, and 5,000 vertices respectively.

The Connected Components runs report 2 components for the 10-vertex test
case and 1 component for the 100-, 1,000-, and 5,000-vertex test cases.
Their recorded execution times are 0 ms, 0 ms, 0 ms, and 1 ms
respectively.

------------------------------------------------------------------------

## Observations

### Triangle Counting

The recorded execution time increases as the graph size increases in the
uploaded readings:

``` text
10 vertices      -> 0 ms
100 vertices     -> 0 ms
1000 vertices    -> 5 ms
5000 vertices    -> 24 ms
```

### Betweenness Centrality

The execution time increases significantly with the number of vertices:

``` text
10 vertices      -> 0 ms
100 vertices     -> 16 ms
1000 vertices    -> 282 ms
5000 vertices    -> 6129 ms
```

The increase is much more noticeable than for the other two algorithms
in the uploaded readings.

### Connected Components

The recorded execution times remain very small for the uploaded test
cases:

``` text
10 vertices      -> 0 ms
100 vertices     -> 0 ms
1000 vertices    -> 0 ms
5000 vertices    -> 1 ms
```

------------------------------------------------------------------------

## Notes

-   Vertices are numbered from `0` to `V-1`.
-   Input graphs are stored in edge-list format.
-   Test cases for the three algorithms are kept in separate input
    directories.
-   Output files are generated in the corresponding output directories.
-   Execution time is recorded in milliseconds.
-   The performance table above contains the readings from the output
    files uploaded for this report.
-   Additional test cases can be added to the same directory structure
    without changing the overall workflow.
