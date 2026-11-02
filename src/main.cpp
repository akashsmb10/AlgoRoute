#include "algoroute/graph.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace algoroute;
int main(int argc,char**argv){
 try{
 if(argc<2){std::cerr<<"Usage: algoroute <bfs|dfs|dijkstra|bellman-ford|kruskal|prim|astar>\nInput: n m directed(0/1), then m lines 'u v weight', then source target for path algorithms; astar additionally requires n lines of 'x y'.\n";return 2;}
 std::string algo=argv[1];int n,m,dir;if(!(std::cin>>n>>m>>dir)||m<0||(dir!=0&&dir!=1))throw std::invalid_argument("invalid graph header");Graph g(n,dir);for(int i=0;i<m;++i){int u,v;Weight w;if(!(std::cin>>u>>v>>w))throw std::invalid_argument("invalid edge");g.add_edge(u,v,w);}
 if(algo=="kruskal"||algo=="prim"){auto r=algo=="kruskal"?kruskal(g):prim(g);std::cout<<"weight="<<r.total_weight<<" connected="<<r.connected<<" edges="<<r.edges.size()<<'\n';for(auto e:r.edges)std::cout<<e.from<<' '<<e.to<<' '<<e.weight<<'\n';}
 else {int s,t;if(!(std::cin>>s>>t))throw std::invalid_argument("missing source and target");if(algo=="bfs"||algo=="dfs"){auto v=algo=="bfs"?bfs(g,s):dfs(g,s);for(auto x:v)std::cout<<x<<' ';std::cout<<'\n';}
 else {PathResult r;if(algo=="dijkstra")r=dijkstra(g,s,t);else if(algo=="bellman-ford")r=bellman_ford(g,s,t);else if(algo=="astar"){std::vector<std::pair<double,double>> coords(n);for(auto&c:coords)if(!(std::cin>>c.first>>c.second))throw std::invalid_argument("missing coordinates");r=astar(g,s,t,coords);}else throw std::invalid_argument("unknown algorithm");if(r.distance==INF)std::cout<<"unreachable\n";else std::cout<<"distance="<<r.distance<<" path="<<path_to_string(r.path)<<'\n';}}
 }catch(const std::exception&e){std::cerr<<"error: "<<e.what()<<'\n';return 1;}
}
