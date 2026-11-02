#pragma once
#include <vector>
#include <tuple>
#include <string>
#include <cstdint>
namespace algoroute {
using Weight = long long;
constexpr Weight INF = (1LL<<60);
struct Edge { int from, to; Weight weight; };
struct PathResult { Weight distance; std::vector<int> path; };
struct MSTResult { Weight total_weight; std::vector<Edge> edges; bool connected; };
class Graph {
 public:
  explicit Graph(int vertices, bool directed=false);
  void add_edge(int from, int to, Weight weight);
  int size() const { return n_; }
  bool directed() const { return directed_; }
  const std::vector<std::vector<std::pair<int,Weight>>>& adjacency() const { return adj_; }
  const std::vector<Edge>& edges() const { return edges_; }
 private:
  int n_; bool directed_;
  std::vector<std::vector<std::pair<int,Weight>>> adj_;
  std::vector<Edge> edges_;
};
std::vector<int> bfs(const Graph& g, int source);
std::vector<int> dfs(const Graph& g, int source);
PathResult dijkstra(const Graph& g, int source, int target);
PathResult bellman_ford(const Graph& g, int source, int target);
PathResult astar(const Graph& g, int source, int target, const std::vector<std::pair<double,double>>& coordinates);
MSTResult kruskal(const Graph& g);
MSTResult prim(const Graph& g);
std::string path_to_string(const std::vector<int>& path);
}
