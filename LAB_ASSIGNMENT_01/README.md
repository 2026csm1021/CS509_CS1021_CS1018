# Graph Algorithms using CSR

This project implements fundamental graph algorithms using the **Compressed Sparse Row (CSR)** representation.

Each graph is first converted from an edge list to CSR format, after which the following algorithms are executed:

- Breadth First Search (BFS)
- Depth First Search (DFS)
- Single Source Shortest Path (SSSP) using Dijkstra's Algorithm

The program automatically processes all graph test cases present in the input directory and generates corresponding output files.

---

## Files

```
Driver.cpp              -> Driver program

make_csr.h
make_csr.cpp            -> CSR construction

Graphs.h
Graphs.cpp              -> BFS, DFS and SSSP implementations

testcases/              -> Input graph test cases

outputs/                -> Generated output files
```

---

## Input Format

Each graph input file should follow the format:

```
V E Source

u1 v1 w1
u2 v2 w2
...
uE vE wE
```

where

- **V** = Number of vertices
- **E** = Number of edges
- **Source** = Source vertex
- **u v w** = Directed weighted edge from `u` to `v` having weight `w`

### Example

```
6 8 0

0 1 4
0 2 2
1 2 5
1 3 10
2 4 3
4 3 4
3 5 11
4 5 5
```

---

## Output Format

For every testcase, the program generates an output file containing:

- Graph information
- BFS Traversal
- DFS Traversal
- SSSP distances
- Execution time of each algorithm

Example:

```
===== case1 =====

Vertices : 5
Edges : 6
Source : 0

Algorithm : BFS
Traversal : 0 1 2 3 4

Algorithm : DFS
Traversal : 0 1 3 4 2

Algorithm : SSSP
Distance :
0 -> 0
1 -> 4
2 -> 2
3 -> 3
4 -> 6
```

---

## Compilation

```bash
g++ -std=c++17 Driver.cpp make_csr.cpp Graphs.cpp -o run
```

---

## Execution

```bash
./run
```

The program automatically:

- Reads every graph from the `testcases` directory.
- Converts the graph into CSR format.
- Executes BFS, DFS and SSSP.
- Stores the output of every testcase in the `outputs` directory.

---

## Algorithms

### CSR Construction

The graph is converted from edge list format to **Compressed Sparse Row (CSR)** representation consisting of:

- Row Pointer
- Column Index
- Values (Edge Weights)

---

### Breadth First Search (BFS)

Traverses the graph level by level starting from the given source vertex.

---

### Depth First Search (DFS)

Traverses the graph using depth-first exploration starting from the source vertex.

---

### Single Source Shortest Path (SSSP)

Computes the shortest distance from the source vertex to every other vertex using **Dijkstra's Algorithm**.

---

## Time Complexity

| Algorithm | Time Complexity |
|-----------|-----------------|
| CSR Construction | O(V + E) |
| BFS | O(V + E) |
| DFS | O(V + E) |
| SSSP (Dijkstra) | O((V + E) log V) |

---

## Graph Results

| Algorithm | Test File | Vertices | Edges | Input Type | Source | Expected Output | Actual Output | Time (ms) | Status |
|-----------|-----------|---------:|------:|------------|-------:|-----------------|---------------|----------:|:------:|
| BFS | case1 | 5 | 6 | Weighted Graph | 0 | Traversal | `0 1 2 3 4` | 0.002718 | ✅ Pass |
| DFS | case1 | 5 | 6 | Weighted Graph | 0 | Traversal | `0 1 3 4 2` | 0.002712 | ✅ Pass |
| SSSP (Dijkstra) | case1 | 5 | 6 | Weighted Graph | 0 | Shortest Distances | Correct | 0.004365 | ✅ Pass |
| BFS | case2 | 6 | 8 | Weighted Graph | 2 | Traversal | `2 3 4 5 0 1` | 0.002622 | ✅ Pass |
| DFS | case2 | 6 | 8 | Weighted Graph | 2 | Traversal | `2 3 5 0 1 4` | 0.002293 | ✅ Pass |
| SSSP (Dijkstra) | case2 | 6 | 8 | Weighted Graph | 2 | Shortest Distances | Correct | 0.002999 | ✅ Pass |
| BFS | case3 | 7 | 10 | Weighted Graph | 3 | Traversal | `3 5 6 0 1 2 4` | 0.004551 | ✅ Pass |
| DFS | case3 | 7 | 10 | Weighted Graph | 3 | Traversal | `3 5 6 0 1 2 4` | 0.003075 | ✅ Pass |
| SSSP (Dijkstra) | case3 | 7 | 10 | Weighted Graph | 3 | Shortest Distances | Correct | 0.004473 | ✅ Pass |
| BFS | case4 | 10 | 15 | Weighted Graph | 5 | Traversal | `5 7 9 0 1 2 3 4 8 6` | 0.004856 | ✅ Pass |
| DFS | case4 | 10 | 15 | Weighted Graph | 5 | Traversal | `5 7 9 0 1 3 4 6 8 2` | 0.006097 | ✅ Pass |
| SSSP (Dijkstra) | case4 | 10 | 15 | Weighted Graph | 5 | Shortest Distances | Correct | 0.008860 | ✅ Pass |

---

## Directory Structure

```
Graph_Algorithms/
│
├── Driver.cpp
├── make_csr.h
├── make_csr.cpp
├── Graphs.h
├── Graphs.cpp
│
├── testcases/
│
├── outputs/
│
└── README.md
```