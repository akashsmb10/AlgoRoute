#include "algoroute/graph.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <utility>
namespace algoroute {
namespace {
void validate_vertex(const Graph& g,int v) { if(v<0||v>=g.size()) throw std::out_of_range("invalid vertex"); }
std::vector<int> reconstruct(const std::vector<int>& parent,int s,int t) {
 std::vector<int> p; for(int v=t;v!=-1;v=parent[v]) {p.push_back(v);if(v==s)break;}
 if(p.empty()||p.back()!=s) return {};
 std::reverse(p.begin(),p.end());
 return p;
}
struct DSU {std::vector<int> p,r;explicit DSU(int n):p(n),r(n,0){std::iota(p.begin(),p.end(),0);}int find(int x){return p[x]==x?x:p[x]=find(p[x]);}bool join(int a,int b){a=find(a);b=find(b);if(a==b)return false;if(r[a]<r[b])std::swap(a,b);p[b]=a;if(r[a]==r[b])++r[a];return true;}};
}
Graph::Graph(int vertices,bool directed):n_(vertices),directed_(directed),adj_(vertices<0?0:vertices){if(vertices<=0)throw std::invalid_argument("vertex count must be positive");}
void Graph::add_edge(int u,int v,Weight w){validate_vertex(*this,u);validate_vertex(*this,v);if(w<=-INF||w>=INF)throw std::invalid_argument("weight out of supported range");adj_[u].push_back({v,w});if(!directed_)adj_[v].push_back({u,w});edges_.push_back({u,v,w});}
std::vector<int> bfs(const Graph& g,int s){validate_vertex(g,s);std::vector<int> out,seen(g.size());std::queue<int> q;q.push(s);seen[s]=1;while(!q.empty()){int u=q.front();q.pop();out.push_back(u);for(auto [v,w]:g.adjacency()[u]){(void)w;if(!seen[v]){seen[v]=1;q.push(v);}}}return out;}
std::vector<int> dfs(const Graph& g,int s){validate_vertex(g,s);std::vector<int> out,seen(g.size()),st{s};while(!st.empty()){int u=st.back();st.pop_back();if(seen[u])continue;seen[u]=1;out.push_back(u);const auto& a=g.adjacency()[u];for(auto it=a.rbegin();it!=a.rend();++it)if(!seen[it->first])st.push_back(it->first);}return out;}
PathResult dijkstra(const Graph& g,int s,int t){validate_vertex(g,s);validate_vertex(g,t);for(const auto& e:g.edges())if(e.weight<0)throw std::invalid_argument("Dijkstra requires nonnegative weights");std::vector<Weight>d(g.size(),INF);std::vector<int>p(g.size(),-1);using Q=std::pair<Weight,int>;std::priority_queue<Q,std::vector<Q>,std::greater<Q>>q;d[s]=0;q.push({0,s});while(!q.empty()){auto [du,u]=q.top();q.pop();if(du!=d[u])continue;if(u==t)break;for(auto [v,w]:g.adjacency()[u])if(du<=INF-w&&du+w<d[v]){d[v]=du+w;p[v]=u;q.push({d[v],v});}}return {d[t],d[t]==INF?std::vector<int>{}:reconstruct(p,s,t)};}
PathResult bellman_ford(const Graph& g,int s,int t){validate_vertex(g,s);validate_vertex(g,t);std::vector<Weight>d(g.size(),INF);std::vector<int>p(g.size(),-1);d[s]=0;for(int i=1;i<g.size();++i){bool change=false;for(int u=0;u<g.size();++u)if(d[u]!=INF)for(auto [v,w]:g.adjacency()[u]){if((w>0&&d[u]>INF-w)||(w<0&&d[u]<-INF-w))throw std::overflow_error("path weight overflow");if(d[u]+w<d[v]){d[v]=d[u]+w;p[v]=u;change=true;}}if(!change)break;}for(int u=0;u<g.size();++u)if(d[u]!=INF)for(auto [v,w]:g.adjacency()[u])if(d[u]+w<d[v])throw std::domain_error("reachable negative cycle");return {d[t],d[t]==INF?std::vector<int>{}:reconstruct(p,s,t)};}
PathResult astar(const Graph& g,int s,int t,const std::vector<std::pair<double,double>>& coords){validate_vertex(g,s);validate_vertex(g,t);if(coords.size()!=static_cast<size_t>(g.size()))throw std::invalid_argument("coordinate count mismatch");for(auto [x,y]:coords)if(!std::isfinite(x)||!std::isfinite(y))throw std::invalid_argument("coordinates must be finite");for(int u=0;u<g.size();++u)for(auto [v,w]:g.adjacency()[u]){if(w<0)throw std::invalid_argument("A* requires nonnegative weights");double euclid=std::hypot(coords[u].first-coords[v].first,coords[u].second-coords[v].second);if(euclid>static_cast<double>(w)+1e-9)throw std::invalid_argument("Euclidean heuristic not admissible: edge cost below geometric distance");}
 auto h=[&](int v){return std::hypot(coords[v].first-coords[t].first,coords[v].second-coords[t].second);};std::vector<Weight>d(g.size(),INF);std::vector<int>p(g.size(),-1);using Q=std::pair<double,int>;std::priority_queue<Q,std::vector<Q>,std::greater<Q>>q;d[s]=0;q.push({h(s),s});while(!q.empty()){auto [f,u]=q.top();q.pop();if(f>static_cast<double>(d[u])+h(u)+1e-9)continue;if(u==t)break;for(auto [v,w]:g.adjacency()[u])if(d[u]<=INF-w&&d[u]+w<d[v]){d[v]=d[u]+w;p[v]=u;q.push({static_cast<double>(d[v])+h(v),v});}}return {d[t],d[t]==INF?std::vector<int>{}:reconstruct(p,s,t)};}
MSTResult kruskal(const Graph& g){if(g.directed())throw std::invalid_argument("MST requires undirected graph");auto edges=g.edges();std::sort(edges.begin(),edges.end(),[](const Edge&a,const Edge&b){return std::tie(a.weight,a.from,a.to)<std::tie(b.weight,b.from,b.to);});DSU d(g.size());MSTResult r{0,{},false};for(auto e:edges)if(d.join(e.from,e.to)){r.total_weight+=e.weight;r.edges.push_back(e);if(static_cast<int>(r.edges.size())==g.size()-1)break;}r.connected=static_cast<int>(r.edges.size())==g.size()-1;return r;}
MSTResult prim(const Graph& g){if(g.directed())throw std::invalid_argument("MST requires undirected graph");using Q=std::tuple<Weight,int,int>;std::priority_queue<Q,std::vector<Q>,std::greater<Q>>q;std::vector<bool>used(g.size());MSTResult r{0,{},false};for(int root=0;root<g.size();++root){if(used[root])continue;q.push({0,-1,root});while(!q.empty()){auto [w,from,u]=q.top();q.pop();if(used[u])continue;used[u]=true;if(from!=-1){r.total_weight+=w;r.edges.push_back({from,u,w});}for(auto [v,weight]:g.adjacency()[u])if(!used[v])q.push({weight,u,v});}}r.connected=static_cast<int>(r.edges.size())==g.size()-1;return r;}
std::string path_to_string(const std::vector<int>& p){if(p.empty())return "unreachable";std::ostringstream os;for(size_t i=0;i<p.size();++i){if(i)os<<" -> ";os<<p[i];}return os.str();}
}
