#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include "unionfind.hpp"
using namespace std;

struct edge{
    int u,v;
    double w;

    int other(int s){
        if( s != u && s != v )
            throw invalid_argument("the vertex do not match either of u of v.. s = " + to_string(s) + ",u = " + to_string(u)+",v = "+to_string(v));
        return (s==u) ? v:u;
    }
    friend int operator<(const edge &e1,const edge &e2){
        return e1.w<e2.w;
    }
    friend bool operator>(const edge &e1,const edge &e2){
        return e1.w>e2.w;
    }
    friend bool operator==(const edge &e1,const edge &e2){
        return e1.w==e2.w;
    }
    friend ostream& operator<<(ostream& out,edge &e){
        out<<"("<<e.u<<"<------"<<e.w<<"------>"<<e.v<<")"<<endl;
        return out;
    }
};

struct weighted_graph{
    int V;
    vector<edge> *adj;

    weighted_graph(int n){
        if( n<=0 ) throw invalid_argument("invalid arg");
        V = n;
        adj = new vector<edge>[V];
    }
    ~weighted_graph(){
        delete [] adj;
    }
    vector<edge> E(){
        vector<edge> edges;
        for(int u=0;u<V;u++){
            for(edge &e: adj[u] )
                edges.push_back(e);
        }
        return edges;
    }
    void add_edge(int u,int v,double w){
        if( u<0 || v<0 || u>=V || v>=V )
            throw invalid_argument("invalid value for u or v");
        adj[u].push_back({u,v,w});
        adj[v].push_back({v,u,w});
    }
};

vector<edge> kruskal_mst(weighted_graph &g){
    unionfind uf(g.V);
    vector<edge> mst;
    vector<edge> edges = g.E();
    sort(edges.begin(),edges.end());
    
    for(edge &e: edges){
        if( uf.find(e.u) != uf.find(e.v) ){
            uf.connect(e.u,e.v);
            mst.push_back(e);
        }
    }
    return mst;
}

void visit_prim(weighted_graph &g, vector<bool> &marked, priority_queue<edge,vector<edge>,greater<edge>> &pq, int s){
    marked[s] = 1;
    for(edge &e : g.adj[s] ){
        if( !marked[e.other(s)] )
            pq.push(e);
       
    }
}
vector<edge> prim_mst(weighted_graph &g){
    vector<bool> marked(g.V,0);
    priority_queue<edge,vector<edge>,greater<edge>> pq;
    vector<edge> mst;
    
    for(int u=0;u<g.V;u++){
        if( marked[u] ) continue ;

        visit_prim(g,marked,pq,u);
        while( !pq.empty() ){
            edge e = pq.top();
            pq.pop();
            if( !marked[e.u] ){
                mst.push_back(e);
                visit_prim(g,marked,pq,e.u);
            }
            else if( !marked[e.v]) {
                mst.push_back(e);
                visit_prim(g,marked,pq,e.v);
            }
        }
    }
    return mst;
}

int main(){
    fstream in("mst.in",ios_base::in);
    int n,m;
    in>>n>>m;
    weighted_graph g(n);
    for(int i=0;i<m;i++){
        int u,v;
        double w;
        in>>u>>v>>w;
        g.add_edge(u,v,w);
    }
    in.close();

    vector<edge> k_mst = kruskal_mst(g);
    vector<edge> p_mst = prim_mst(g);
    double mst_weight = 0.0;
    for(auto &e : k_mst)
        mst_weight += e.w;
    
    cout<<"Cost of the minimum spanning tree: "<<mst_weight<<endl;
    cout<<"List of edges selected by Prim's:{";
    if( !p_mst.empty()) cout<<"("<<p_mst[0].u<<","<<p_mst[0].v<<")"; 
    for(int i=1;i<p_mst.size();i++)
        cout<<",("<<p_mst[i].u<<","<<p_mst[i].v<<")";
    cout<<"}"<<endl;

    cout<<"List of edges selected by Kruskal's:{";
    if( !k_mst.empty()) cout<<"("<<k_mst[0].u<<","<<k_mst[0].v<<")"; 
    for(int i=1;i<k_mst.size();i++)
        cout<<",("<<k_mst[i].u<<","<<k_mst[i].v<<")";
    cout<<"}"<<endl;
}