#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("input1.txt","r",stdin);
    int n,m;
    cin>>n>>m;
    double w[n][n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) 
            w[i][j] = (i==j) ? 0:INFINITY;

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        double ww;
        cin>>ww;
        --u,--v;
        w[u][v] = ww;
    }
 
    double sp[n][n],sp_t[n][n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            sp[i][j] = sp_t[i][j] = w[i][j];
    
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                sp[i][j] = min(sp_t[i][j],sp_t[i][k]+sp_t[k][j]);
            }
        }

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                sp_t[i][j] = sp[i][j];
    }

    cout<<"Shortest distance matrix: \n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<sp[i][j]<<"\t";
        }
        cout<<endl;
    }
}