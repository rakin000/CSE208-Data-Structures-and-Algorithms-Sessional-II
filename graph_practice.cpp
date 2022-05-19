#include <bits/stdc++.h>
using namespace std;


vector<int> ordering;

void dfs(int s, vector<int> *adj, bool *vis){
    vis[s] = 1;
    for( int v: adj[s] ){
        if( !vis[v] )
            dfs(v, adj, vis);
    }
    ordering.push_back(s);
    return ;
}

bool detect_cycle(int s,vector<int> *adj, bool *vis, bool *onstack){
    vis[s] = 1;
    onstack[s] = 1;
    bool cycle = false ;
    for(int v: adj[s] ){
        if( !vis[v] ){
            cycle |= detect_cycle(v,adj,vis,onstack);
        }
        else if( onstack[v] )
            return 1;
        
    }
    onstack[s] = 0;
    return cycle ;
}

int main(){
    int n;
    int d;
    cin>>n>>d;

    vector<int> adj[n+1];
    bool vis[n+1],onstack[n+1];
    for(int i=0;i<=n;i++)
        vis[i] = onstack[i] = 0;

    for(int i=0;i<d;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }

    bool cycle = 0;
    for(int u=1;u<=n;u++){
        if( !vis[u] )
            cycle |= detect_cycle(u,adj,vis,onstack);
    }
    if( cycle ){
        cout<<"Not Possible\n";
        return 0;
    }

    ordering.clear();

    for(int u=0;u<=n;u++)
        vis[u] = 0;
    
    for(int u=1;u<=n;u++){
        if( !vis[u] )
            dfs(u,adj,vis);
    }
    cout<<"Possible\n";
    for(int u: ordering )
        cout<<u<<" "; cout<<endl;
}