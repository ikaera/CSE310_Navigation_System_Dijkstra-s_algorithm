# CSE310_Navigation_System_Dijkstra-s_algorithm

## Overview
This project implements a navigation system capable of computing shortest paths in directed or undirected graphs using Dijkstra's algorithm. The system reads graph data from an input file, processes user instructions (e.g., path computation, printing), and outputs results with strict formatting requirements.

Key features:
- Graph representation using adjacency lists
- Priority queue (min-heap) for efficient path computation
- Stack for path reversal and printing
- Support for both directed and undirected graphs
- Memory management to avoid leaks

## Project Structure
The project follows a modular design with these files:
```
PJ3/
├── main.cpp        - Main program logic and instruction processing
├── main.h          - Header for main program
├── graph.cpp       - Graph algorithms implementation
├── graph.h         - Graph module header
├── heap.cpp        - Min-heap implementation
├── heap.h          - Min-heap header
├── stack.cpp       - Stack implementation
├── stack.h         - Stack header
├── util.cpp        - Utility functions
├── util.h          - Utility header
├── data_structures.h - Core data structures
└── Makefile        - Build configuration
```

---

## Building and Execution
1. Compile using the provided Makefile:
   ```bash
   make clean && make
   ```

2. Execute the program:
   ```bash
   ./PJ3 <InputFile> <GraphType> <Flag>
   ```
   Where:
   - `<InputFile>`: Graph data file (e.g., `network01.txt`)
   - `<GraphType>`: `DirectedGraph` or `UndirectedGraph`
   - `<Flag>`: `0` (insert at front) or `1` (insert at rear)

Example:
```bash
./PJ3 network01.txt DirectedGraph 1
```

---

## Input Format
Graph input files contain:
1. First line: `n m` (number of vertices and edges)
2. Subsequent lines: `edgeIndex u v w(u,v)` (edge details)

Example (`network01.txt`):
```
8 14
1 1 2 10
2 1 4 5
...
14 8 6 1
```

---

## Supported Instructions
| Instruction        | Description                                  | Example                   |
|--------------------|----------------------------------------------|---------------------------|
| `Stop`             | Terminates the program                       | `Stop`                    |
| `PrintADJ`         | Prints adjacency lists                       | `PrintADJ`                |
| `SinglePair s t`   | Computes s-t shortest path                   | `SinglePair 1 3`          |
| `SingleSource s`   | Computes paths from s to all nodes           | `SingleSource 1`          |
| `PrintLength s t`  | Prints length of last computed s-t path      | `PrintLength 1 5`         |
| `PrintPath s t`    | Prints nodes in last computed s-t path       | `PrintPath 1 3`           |

---

## Output Examples
1. Adjacency list output (`PrintADJ`):
   ```
   ADJ[1]:-->[1 2: 10.00]-->[1 4: 5.00]
   ADJ[2]:-->[2 3: 1.00]-->[2 4: 2.00]
   ...
   ```

2. Path output (`PrintPath`):
   ```
   The shortest path from 1 to 3 is:
   [1: 0.00]-->[4: 5.00]-->[2: 8.00]-->[3: 9.00].
   ```

3. Length output (`PrintLength`):
   ```
   The length of the shortest path from 1 to 5 is: 7.00
   ```

---

## Technical Requirements
- Time Complexity:
  - Path computation: O((m+n)log n)
  - Path printing: O(n)
  - Length printing: O(1)
- Memory: Dynamically allocated and properly freed
- Platform: Linux/g++ (tested on general.asu.edu)

---

## Development Notes
1. **Data Structures**:
   - Vertices use `VERTEX` struct with `index`, `key`, `pi`, etc.
   - Edges use `NODE` struct in adjacency lists
   - Min-heap modified from Project 2 to use `ELEMENT**`

2. **Algorithm**:
   - Implements Dijkstra's algorithm with early termination for SinglePair
   - Uses vertex coloring (WHITE/GRAY/BLACK) for tracking

3. **Error Handling**:
   - Invalid executions print usage to stderr
   - Invalid instructions print error message

---

## Testing
Test cases available on Canvas cover:
- Graph building (directed/undirected, front/rear insertion)
- Path computations (SinglePair/SingleSource)
- Output formatting (exact match required)
- Edge cases (unreachable nodes, invalid inputs)

