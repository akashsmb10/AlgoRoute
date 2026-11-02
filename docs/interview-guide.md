# AlgoRoute — 25 interview questions and answers

1. **Why adjacency lists?** O(V+E) storage, efficient sparse graph traversal.
2. **BFS vs DFS?** BFS explores by distance in edge count; DFS follows branches deeply.
3. **Why queue for BFS?** FIFO processes vertices in increasing hop distance.
4. **Why iterative DFS?** Avoids recursion depth limits.
5. **What is a relaxation?** Improving a tentative shortest-path distance using an edge.
6. **Why a priority queue in Dijkstra?** Efficiently select the smallest tentative distance.
7. **Why reject negative weights in Dijkstra?** Its greedy finalization property may fail.
8. **What is a stale queue entry?** A previous larger distance left in the heap after improvement.
9. **Dijkstra complexity?** O((V+E)log V) with binary heap, often written O(E log V) for connected graphs.
10. **Bellman–Ford advantage?** Supports negative edges and detects reachable negative cycles.
11. **Bellman–Ford complexity?** O(VE).
12. **Why V−1 rounds?** A simple shortest path uses at most V−1 edges.
13. **What is a negative cycle?** A reachable cycle whose total weight is negative, making shortest distances undefined for affected targets.
14. **What is A*?** Best-first shortest path using f=g+h.
15. **What is an admissible heuristic?** One that never overestimates remaining cost.
16. **Why Euclidean distance?** A valid lower bound if each edge cost covers its geometric length.
17. **A* vs Dijkstra?** A* can prioritize promising nodes; h=0 makes it Dijkstra-like.
18. **What is an MST?** A minimum-weight tree spanning all vertices of a connected undirected graph.
19. **Prim vs Kruskal?** Prim grows a tree via a heap; Kruskal sorts edges and unions components.
20. **Why DSU?** Efficient cycle detection during Kruskal.
21. **DSU optimizations?** Path compression and union by rank, amortized near-constant time.
22. **What happens if graph is disconnected?** Return a minimum spanning forest and `connected=false`.
23. **Can an MST include negative edges?** Yes, negative weights are valid in undirected MSTs.
24. **Why use long long?** Reduces overflow risk compared with int, but still requires explicit bounds.
25. **How to validate correctness?** Deterministic unit tests, edge cases, cross-checking Dijkstra against Bellman–Ford on nonnegative graphs, and randomized property tests.
