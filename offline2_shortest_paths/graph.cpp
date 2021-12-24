#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

struct edge{
    int u,v;
    double w;

    int other(int s){
        if( s != u && s != v )
            throw invalid_argument("the vertex do not match either of u of v.. s = " + to_string(s) + ",u = " + to_string(u)+",v = "+to_string(v));
        return (s==u) ? v:u;
    }
    int to(){ return v; }
    int from(){ return u; }
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
        out<<"("<<e.u<<"-------("<<e.w<<")------>"<<e.v<<")"<<endl;
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

struct weighted_digraph: public weighted_graph {
    weighted_digraph(int n):
        weighted_graph(n)
    {}

    void add_edge(int u,int v,double w){
        if( u<0 || v<0 || u>=V || v>=V )
            throw invalid_argument("invalid value for u or v");
        adj[u].push_back({u,v,w});
    }
};