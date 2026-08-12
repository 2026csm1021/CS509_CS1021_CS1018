# Graph Algorithm Test Cases

## Overview

This directory contains test cases for three graph algorithms:
1. **Triangle Counting**
2. **Betweenness Centrality**
3. **Connected Components**

Each algorithm has its own folder with test cases of varying sizes and metadata files.

---

## Directory Structure

```
input/
├── TriangleCount/
│   ├── META.json          (Algorithm metadata)
│   ├── tc_10.txt          (10 vertices, 15 edges)
│   ├── tc_100.txt         (100 vertices, 250 edges)
│   ├── tc_1000.txt        (1000 vertices, 5000 edges)
│   └── tc_5000.txt        (5000 vertices, 25000 edges)
│
├── BetweennessCentrality/
│   ├── META.json          (Algorithm metadata)
│   ├── bc_10.txt          (10 vertices, 12 edges)
│   ├── bc_100.txt         (100 vertices, 150 edges)
│   ├── bc_1000.txt        (1000 vertices, 1500 edges)
│   └── bc_5000.txt        (5000 vertices, 7500 edges)
│
└── ConnectedComponents/
    ├── META.json          (Algorithm metadata)
    ├── cc_10.txt          (10 vertices, 8 edges)
    ├── cc_100.txt         (100 vertices, 99 edges)
    ├── cc_1000.txt        (1000 vertices, 999 edges)
    └── cc_5000.txt        (5000 vertices, 4999 edges)
```

---

## Test Cases Summary

### Triangle Counting

**Algorithm**: Counts all triangles (3-cycles) in an undirected graph

| File | Vertices | Edges | Purpose |
|------|----------|-------|---------|
| tc_10.txt | 10 | 15 | Quick verification |
| tc_100.txt | 100 | 250 | Standard testing |
| tc_1000.txt | 1000 | 5000 | Performance testing |
| tc_5000.txt | 5000 | 25000 | Stress testing |

**Complexity**: O(V·E)  
**Space**: O(V+E)  
**Metadata**: See `TriangleCount/META.json`

---

### Betweenness Centrality

**Algorithm**: Measures vertex importance based on shortest path calculations

| File | Vertices | Edges | Complexity | Purpose |
|------|----------|-------|-----------|---------|
| bc_10.txt | 10 | 12 | Simple | Verification |
| bc_100.txt | 100 | 150 | Medium | Standard testing |
| bc_1000.txt | 1000 | 1500 | Large | Performance testing |
| bc_5000.txt | 5000 | 7500 | Very Large | Stress testing |

**Complexity**: O(V·(V+E))  
**Space**: O(V+E)  
**Approach**: Brandes algorithm with BFS  
**Metadata**: See `BetweennessCentrality/META.json`

---

### Connected Components

**Algorithm**: Identifies and labels all connected components using DFS

| File | Vertices | Edges | Components | Purpose |
|------|----------|-------|------------|---------|
| cc_10.txt | 10 | 8 | 2 | Verification |
| cc_100.txt | 100 | 99 | 1 | Standard testing |
| cc_1000.txt | 1000 | 999 | 1 | Performance testing |
| cc_5000.txt | 5000 | 4999 | 1 | Stress testing |

**Complexity**: O(V+E)  
**Space**: O(V)  
**Approach**: Depth-First Search  
**Metadata**: See `ConnectedComponents/META.json`

---

## Input File Format

All test files follow this standard format:

```
V E source
u1 v1 weight1
u2 v2 weight2
...
uE vE weightE
```

### Fields:
- **V**: Number of vertices (0 to V-1)
- **E**: Number of edges
- **source**: Source vertex (unused in some algorithms)
- **u, v**: Vertex IDs (0-indexed)
- **weight**: Edge weight (typically 1 for unweighted)

### Example:
```
10 15 0
0 1 1
0 2 1
1 2 1
1 3 1
2 3 1
...
```

---

## Metadata Files (META.json)

Each algorithm folder contains a `META.json` file with:

- **Algorithm description**
- **Test case details** (vertices, edges, complexity level)
- **Time complexity** analysis
- **Space complexity** analysis
- **Approach description**
- **Output format** specification

### Example META.json structure:
```json
{
  "algorithm": "Algorithm Name",
  "description": "Algorithm description",
  "test_cases": [
    {
      "filename": "test_file.txt",
      "vertices": 10,
      "edges": 15,
      "complexity": "Simple",
      "description": "Test description"
    }
  ],
  "algorithm_details": {
    "time_complexity": "O(...)",
    "space_complexity": "O(...)",
    "approach": "Algorithm approach"
  }
}
```

---

## Test Case Selection Guide

### For Quick Testing:
- Use `*_10.txt` files (smallest)
- Fast execution, easy to verify results

### For Standard Testing:
- Use `*_100.txt` files
- Medium complexity, reasonable execution time

### For Performance Analysis:
- Use `*_1000.txt` files
- Larger graphs for meaningful timing measurements

### For Stress Testing:
- Use `*_5000.txt` files
- Maximum size for capacity and scalability analysis

---

## How to Run

1. **Compile**:
   ```bash
   g++ -std=c++17 -o graph_algo Driver.cpp Graph.cpp make_csr.cpp
   ```

2. **Run**:
   ```bash
   ./graph_algo
   ```

3. **Select Algorithm**:
   ```
   Enter your choice: 2  (for Triangle Counting)
   ```

4. **Outputs**:
   - Generated in `../output/TriangleCount/` (or respective algorithm folder)
   - Named as `[testfile]_output.txt`

---

## Graph Characteristics

### TriangleCount Tests:
- Dense connectivity to maximize triangles
- Random edges plus structural edges
- Useful for triangle-rich network analysis

### BetweennessCentrality Tests:
- Linear chain structure with shortcuts
- Identifies bottleneck vertices
- Useful for network flow analysis

### ConnectedComponents Tests:
- Tree structures (edges = vertices - 1)
- Single or multiple components
- Useful for component analysis

---

## Performance Notes

- **tc_5000.txt**: ~5000 vertices, ~25000 edges (largest)
- **bc_5000.txt**: ~5000 vertices, ~7500 edges (medium-large)
- **cc_5000.txt**: ~5000 vertices, ~4999 edges (tree structure)

Execution times will vary based on:
- System specifications
- Available memory
- Compiler optimizations
- Algorithm efficiency

---

## Additional Resources

- See `META.json` in each algorithm folder for detailed specifications
- Check output files for execution statistics
- Compare performance across different test sizes

---

## Notes

✅ All test files are properly formatted  
✅ Each has corresponding metadata  
✅ Multiple size categories for comprehensive testing  
✅ Suitable for performance benchmarking  
✅ Ready for production use

---

**Generated**: Automatically  
**Format Version**: 1.0  
**Last Updated**: August 2026
