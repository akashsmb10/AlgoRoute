# AlgoRoute — Graph Algorithms & Optimization Engine

A **C++17** graph algorithms library, command-line tool, test suite, and reproducible benchmark. Created as a software engineering/DSA portfolio project. This is a real executable, not a UI mockup.

## Algorithms

| Algorithm | Purpose | Complexity | Conditions |
|---|---|---|---|
| BFS | Unweighted traversal | O(V+E) | Directed/undirected |
| DFS | Depth-first traversal | O(V+E) | Iterative, directed/undirected |
| Dijkstra | Shortest weighted path | O((V+E) log V) | Nonnegative weights |
| Bellman–Ford | Shortest path | O(VE) | Negative weights allowed, rejects reachable negative cycles |
| A* | Heuristic shortest path | O((V+E) log V) typical queue operations; worst-case search depends on heuristic | Nonnegative edge weights and Euclidean lower-bound heuristic |
| Kruskal | Minimum spanning forest | O(E log E) | Undirected |
| Prim | Minimum spanning forest | O(E log E) | Undirected |

A* uses Euclidean distance to the target and checks that each edge weight is at least its endpoint geometric distance, ensuring an admissible/consistent heuristic. Zero coordinates are valid (A* then behaves like Dijkstra). Graph weights are integral and bounded; very large accumulated weights are not a supported use case.

## Build

Requires CMake >= 3.16 and a C++17 compiler.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

## CLI usage

```bash
./build/algoroute dijkstra < examples/weighted_graph.txt
./build/algoroute bellman-ford < examples/weighted_graph.txt
./build/algoroute astar < examples/astar_graph.txt
./build/algoroute kruskal < examples/mst_graph.txt
./build/algoroute prim < examples/mst_graph.txt
./build/algoroute bfs < examples/weighted_graph.txt
./build/algoroute dfs < examples/weighted_graph.txt
./build/benchmark_algoroute
```

Input format: `n m directed`, then `m` lines `u v weight`. For BFS/DFS/Dijkstra/Bellman–Ford/A*, provide `source target` afterward (BFS/DFS ignore target). For A*, add `n` lines of `x y` coordinates. Vertices are zero-indexed. Undirected edges are entered once. For MST algorithms, omit source and target.

Example expected shortest path: `distance=7 path=0 -> 2 -> 1 -> 3 -> 4`.

## Design

- `include/algoroute/graph.hpp`: public API and types
- `src/graph.cpp`: graph representation, algorithms, DSU, path reconstruction
- `src/main.cpp`: command-line input/output
- `tests/test_graph.cpp`: executable assertions for core correctness and invalid inputs
- `benchmarks/benchmark.cpp`: deterministic synthetic graph timing
- `docs/`: interview prep, complexity and architecture
- `.github/workflows/ci.yml`: build/test CI on Ubuntu

## Verified and unverified

The project includes a test executable and a deterministic benchmark. See `docs/verification.md` for actual local results. Benchmarks are machine-dependent and must not be represented as universal throughput or performance guarantees. No graphical visualization frontend is included.

## Interview topics

Explain priority queue stale entries, Bellman–Ford negative cycles, DSU path compression/union by rank, Prim vs Kruskal, admissible A* heuristics, unreachable vertices, disconnected MSTs, and asymptotic complexity. See `docs/interview-guide.md`.

## License

MIT — see `LICENSE`.
