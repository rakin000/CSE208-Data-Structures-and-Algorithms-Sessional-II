#include <bits/stdc++.h>
#include "graph.cpp"
using namespace std;


void print_path(int v, int *parent){
    if( parent[v] == -1 ) {  cout<<v; return ; }
    print_path(parent[v],parent);
    cout<<"-->"<<v;
}
void relax(edge& e, double *distance, int *parent){
    if( distance[e.to()] > distance[e.from()] + e.w ){
        distance[e.to()] = distance[e.from()] + e.w;
        parent[e.to()] = e.from();
    }
}
bool shortestpath_bellman_ford(weighted_digraph& g,int source,double* distance,int* parent){
    for(int u=0;u<g.V;u++)
        distance[u] = INFINITY;
    distance[source] = 0.0;
    parent[source] = -1;

    vector<edge> edges = g.E();

    for(int i=1;i<g.V;i++){
        for(edge &e: edges)
            relax(e,distance,parent);
    }
    bool neg_cycle = 0;
    for(edge &e: edges){
        if( distance[e.to()] > distance[e.from()]+e.w ){
            neg_cycle = 1;
            break;
        }
    }

    return neg_cycle;
}
void shortestpath_dijkstra(weighted_digraph& g,int source,double *distance, int *parent){
    for(int u=0;u<g.V;u++)
        distance[u] = INFINITY;
    distance[source] = 0.0;
    parent[source] = -1;

    set<pair<double,int>> q;
    for(int u=0;u<g.V;u++)
        q.insert(make_pair(distance[u],u));

    while( !q.empty()) {
        int v = (*q.begin()).second;
        q.erase(q.begin());
        for(edge &e: g.adj[v] ){
            if( distance[e.to()] > distance[e.from()] + e.w ){
                set<pair<double,int>>::iterator it = q.find(make_pair(distance[e.to()],e.to()));
                if( it != q.end() )
                    q.erase(it);
                distance[e.to()] = distance[e.from()] + e.w;
                parent[e.to()] = e.from();
                q.insert(make_pair(distance[e.to()],e.to()));
            }
        }
    }

    
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
    double distance[n];

   
    if( shortestpath_bellman_ford(g,source,distance,parent) ){
        cout<<"The graph contains a negative cycle\n";
    }
    else {
        cout<<"The graph doesn't contain a negative cycle\n";
        cout<<"Shortest path cost: "<<distance[dest]<<endl;
        print_path(dest,parent);
        cout<<endl;
    }
 /*
    shortestpath_dijkstra(g,source,distance,parent);
    cout<<"Shortest path cost: "<<distance[dest]<<endl;
    print_path(dest,parent);
    cout<<endl;*/
}