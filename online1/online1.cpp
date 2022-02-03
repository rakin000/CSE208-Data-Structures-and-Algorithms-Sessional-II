#include <bits/stdc++.h>
using namespace std;

vector<vector<int> > adj;
vector<bool> vis;
vector<int> topological_order;

void dfs_toposort(int s){
    vis[s] = 1;
    for(int v: adj[s]){
        if( !vis[v] )
            dfs_toposort(v);
    }

    topological_order.push_back(s);
}

void dfs(int s){
    vis[s] = 1;
    for(int v: adj[s] ){
        if( !vis[v] ){
            dfs(v);
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    if( n <= 0 || m<0 ){
        cout<<"Invalid Input\n";
        return -1;
    }
    adj.resize(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        if( u>=n || v>= n || u<0 || v<0 ){
            cout<<"Invalid Input\n";
            return -1;
        }
        adj[u].push_back(v);
    }

    vis.assign(n,0);
    topological_order.clear();

    for(int u=0;u<n;u++){
        if( !vis[u] ){
            dfs_toposort(u);
        }
    }

    int v = topological_order[(int)topological_order.size()-1];
    vis.assign(n,0);
    dfs(v);

    bool si = 1;

    for(int u=0;u<n && si;u++)
        if( !vis[u] )
            si = 0;
    cout<<(si?v:-1)<<endl;
}
