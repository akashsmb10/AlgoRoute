# Architecture and design decisions

The application is a small C++17 modular library with a CLI, not a web service. `Graph` owns an adjacency list and an edge list. An undirected edge appears twice in adjacency but once in the edge list. This supports fast traversal and efficient Kruskal sorting.

Shortest path methods return a `PathResult` containing the distance and the reconstructed path. Unreachable targets return `INF` and an empty path. Prim and Kruskal return a minimum spanning forest for disconnected graphs with `connected=false`.

`DSU` uses path compression and union by rank. Dijkstra uses a min-priority queue with stale-entry skipping. Bellman–Ford scans adjacency and rejects reachable negative cycles. A* uses a Euclidean heuristic and validates its consistency against each graph edge; it does not claim validity for arbitrary coordinate/weight combinations.

Limitations: no frontend, no file persistence, no dynamic edge removal, no multi-criteria route planning, no thread-safe graph mutation, and no support for unbounded integer path sums.
