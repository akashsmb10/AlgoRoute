#ifdef NDEBUG
#undef NDEBUG
#endif
#include "algoroute/graph.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <stdexcept>
using namespace algoroute;
template<class E>void expect_throw(std::function<void()>f){bool threw=false;try{f();}catch(const E&){threw=true;}assert(threw);}
int main(){
 Graph g(5);g.add_edge(0,1,4);g.add_edge(0,2,1);g.add_edge(2,1,2);g.add_edge(1,3,1);g.add_edge(2,3,5);g.add_edge(3,4,3);
 assert((bfs(g,0)==std::vector<int>{0,1,2,3,4}));assert((dfs(g,0)==std::vector<int>{0,1,2,3,4}));
 auto d=dijkstra(g,0,4);assert(d.distance==7);assert((d.path==std::vector<int>{0,2,1,3,4}));assert(bellman_ford(g,0,4).distance==7);
 auto k=kruskal(g),p=prim(g);assert(k.connected&&p.connected&&k.total_weight==7&&p.total_weight==7);assert(k.edges.size()==4);
 std::vector<std::pair<double,double>>coords={{0,0},{0,0},{0,0},{0,0},{0,0}};assert(astar(g,0,4,coords).distance==7);
 expect_throw<std::invalid_argument>([&]{Graph bad(0);});expect_throw<std::out_of_range>([&]{g.add_edge(0,8,1);});
 Graph neg(3,true);neg.add_edge(0,1,-2);neg.add_edge(1,2,3);assert(bellman_ford(neg,0,2).distance==1);expect_throw<std::invalid_argument>([&]{dijkstra(neg,0,2);});
 Graph cycle(2,true);cycle.add_edge(0,1,-1);cycle.add_edge(1,0,-1);expect_throw<std::domain_error>([&]{bellman_ford(cycle,0,1);});
 Graph disconnected(3);disconnected.add_edge(0,1,2);assert(!kruskal(disconnected).connected);assert(!prim(disconnected).connected);assert(dijkstra(disconnected,0,2).distance==INF);
 Graph directed(2,true);directed.add_edge(0,1,3);expect_throw<std::invalid_argument>([&]{kruskal(directed);});
 Graph geo(2);geo.add_edge(0,1,1);expect_throw<std::invalid_argument>([&]{astar(geo,0,1,{{0,0},{5,0}});});
 std::cout<<"All AlgoRoute assertions passed.\n";
}
