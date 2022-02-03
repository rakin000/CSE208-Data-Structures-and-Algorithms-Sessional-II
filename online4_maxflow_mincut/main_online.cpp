#include <bits/stdc++.h>
#include "flow_network.cpp"
using namespace std;


int m,n;
int n_X;
int n_Y;

vector<bool> marked;
vector<flow_edge*> edge_to;

bool has_augmenting_path_bfs(flow_network &G,int source, int terminal){
    marked = vector<bool> (G.V,0);
    edge_to = vector<flow_edge*> (G.V);

    queue<int> q;
    q.push(source);
    marked[source] = 1;

    while( !q.empty() && !marked[terminal]){
        int v = q.front();
        q.pop();

        for(flow_edge* fl: G.adj[v]){
            int w = fl->other(v);
            if( !marked[w] && fl->residual_capacity_to(w) > 0.0 ){
                marked[w] = 1;
                q.push(w);
                edge_to[w] = fl;
            }
        }
    }

    return marked[terminal];
}


int main(){
    cin>>m>>n;
    cin>>n_X>>n_Y;

    int pair_cnt;
    cin>>pair_cnt;

    int V = n_X+n_Y+3;
    flow_network g(V);
    int source = V-1;
    int terminal = V-2;
    // and first n_X -> boys after that n_Y -> girls;

    for(int u=0;u<n_X;u++){
        flow_edge fl(source,u,n); 
        g.add_edge(fl);
    }
    for(int u=n_X;u<n_X+n_Y;u++){
        flow_edge fl(u,terminal,n);
        g.add_edge(fl);
    }

    for(int i=0;i<pair_cnt;i++){
        int x,y;
        cin>>x>>y;

        int v_x = x;
        int v_y = n_X+y;
        flow_edge fl(v_x,v_y,m);
        g.add_edge(fl);
    }


    double max_flow = 0.0;
    
    while( has_augmenting_path_bfs(g,source,terminal) ){
        double min_edge_capacity = INFINITY;

        for(int u=terminal;u!=source; u=edge_to[u]->other(u) ){
            min_edge_capacity = min(min_edge_capacity,edge_to[u]->residual_capacity_to(u));
        }

        for(int u=terminal;u!=source; u=edge_to[u]->other(u) ){
            flow_edge *fl = edge_to[u];
            fl->add_residual_flow_to(u,min_edge_capacity);
        }

        // int y = edge_to[terminal]->other(terminal);
        // int x = edge_to[y]->other(y);

        // int dance_cnt = min_edge_capacity;
        
        max_flow += min_edge_capacity;
    }
    
    for(int x=0;x<n_X;x++){
        for( flow_edge* fl: g.adj[x] ){
            int cap = fl->residual_capacity_to(x);
            int y = fl->other(x)-n_X;

            if( y<n_Y) 
                while( cap-- )
                cout<<"("<<x<<","<<y<<")\n";
        }
    }

    // cout<<"Maxflow: "<<max_flow<<endl;
}