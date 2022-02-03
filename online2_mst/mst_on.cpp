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


int main(){
    int n,m;
    cin>>n>>m;
    vector<edge> edges[3];
    for(int i=0;i<m;i++){
        int u,v,t;
        cin>>u>>v>>t;
        edges[t-1].push_back({u,v,0.0});
    }

    unionfind uf_men(n+1),uf_women(n+1);
    int not_used  = 0;
    for(edge &e: edges[2]){
        if( uf_men.find(e.u) != uf_men.find(e.v) ){
            uf_men.connect(e.u,e.v);
            uf_women.connect(e.u,e.v);
        }
        else ++not_used;
    }
    for(edge &e: edges[0]){
        if( uf_men.find(e.u) != uf_men.find(e.v) )
            uf_men.connect(e.u,e.v);
        else ++not_used;
    }
    for(edge &e: edges[1]){
        if( uf_women.find(e.u) != uf_women.find(e.v))
            uf_women.connect(e.u,e.v);
        else ++not_used;
    }

    bool connected = 1;

    for(int u=2;u<=n;u++){
        connected &= ( (uf_men.find(u) == uf_men.find(1)) && (uf_women.find(u) == uf_women.find(1)) );
    }

    cout<<(connected?not_used:-1)<<endl;
}