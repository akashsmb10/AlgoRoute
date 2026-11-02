#include "algoroute/graph.hpp"
#include <chrono>
#include <iostream>
#include <random>
using namespace algoroute;
int main(){std::mt19937 rng(42);for(int n:{100,1000,5000}){Graph g(n);std::uniform_int_distribution<int> v(0,n-1),w(1,100);for(int i=0;i<n*5;++i){int a=v(rng),b=v(rng);if(a!=b)g.add_edge(a,b,w(rng));}auto start=std::chrono::steady_clock::now();auto r=dijkstra(g,0,n-1);auto ms=std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-start).count();std::cout<<"vertices="<<n<<" edges="<<g.edges().size()<<" dijkstra_ms="<<ms<<" distance="<<r.distance<<'\n';}}
