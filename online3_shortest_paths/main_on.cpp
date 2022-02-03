#include <bits/stdc++.h>
#include "graph.cpp"
using namespace std;

void print_path(int v, int *parent){
    if( parent[v] == -1 ) {  cout<<v; return ; }
    print_path(parent[v],parent);
    cout<<"-->"<<v;
}
void relax(edge& e, double *distance, int *parent){
    if( distance[e.to()] < distance[e.from()]*e.w ){
        distance[e.to()] = distance[e.from()]*e.w;
        parent[e.to()] = e.from();
    }
}
bool shortestpath_bellman_ford(weighted_digraph& g,int source,double* distance,int* parent){
    for(int u=0;u<g.V;u++)
        distance[u] = 0.0;
    distance[source] = 1.0;
    parent[source] = -1;

    vector<edge> edges = g.E();

    for(int i=1;i<g.V;i++){
        for(edge &e: edges)
            relax(e,distance,parent);
    }
    bool neg_cycle = 0;
    for(edge &e: edges){
        if( distance[e.from()]*e.w-distance[e.to()] > 0.00001){
           // distance[e.to()] = distance[e.from()]*e.w;
            neg_cycle = 1;
            break;
        }
    }

    return neg_cycle;
}

int main(){
    int n;
    cin>>n;
    int m;
    cin>>m;
    weighted_digraph g(n);
    for(int i=0;i<m;i++){
        int u,v;
        double w;
        cin>>u>>v>>w;
        g.add_edge(u,v,w);
    }
    int source,dest;
    cin>>source>>dest;
    
    int parent[n];
    double exch_rate[n];

   
    if( shortestpath_bellman_ford(g,source,exch_rate,parent) ){
        cout<<"There is an anomaly\n";
    }
    else {
        cout<<"There are no anomalies\n";
        cout<<"Best exchange rate: "<<exch_rate[dest]<<endl;
        print_path(dest,parent);
        cout<<endl;
        
    }
 /*
    shortestpath_dijkstra(g,source,distance,parent);
    cout<<"Shortest path cost: "<<distance[dest]<<endl;
    print_path(dest,parent);
    cout<<endl;*/
}