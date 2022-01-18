#include <bits/stdc++.h>
#include "flow_network.cpp"
using namespace std;



int N;
vector<int> l,w,rem_g;
vector<vector<int>> g;
vector<bool> eliminated;
vector<string> team_name;
vector<vector<int>> eliminated_by;

void check_inp(){
    cout<<N<<endl;
    for(int i=0;i<N;i++){
        cout<<team_name[i]<<"\t\t\t"<<w[i]<<"\t"<<l[i]<<"\t"<<rem_g[i]<<"\t";
        for(int j=0;j<N;j++)
            cout<<g[i][j]<<" ";
        cout<<endl;
    }  
}


double max_flow;
vector<bool> marked;
vector<flow_edge*> edge_to;

bool has_augmenting_path_bfs(flow_network &G, int s, int t){
    marked = vector<bool> (G.V,0);
    edge_to = vector<flow_edge*> (G.V);

    queue<int> q;
    q.push(s);
    marked[s] = true;

    while( !q.empty() && !marked[t] ){
        int v = q.front();
        // cout<<v<<" ";
        q.pop();

        for(flow_edge* fe: G.adj[v]){
            if( !marked[fe->other(v)] && fe->residual_capacity_to(fe->other(v)) > 0.0 ){
                edge_to[fe->other(v)] = fe;
                marked[fe->other(v)] = 1;
                q.push(fe->other(v));
            }
        }
    }   
    return marked[t];
}

void max_flow_ford_fulkerson(flow_network &G, int s,int t){
    max_flow = 0.0;

    while( has_augmenting_path_bfs(G,s,t) ){
        double min_edge_capacity = INFINITY;

        for(int u=t;u!=s;u=edge_to[u]->other(u) ){
            min_edge_capacity = min(min_edge_capacity,edge_to[u]->residual_capacity_to(u));
        }

        for(int u=t;u!=s;u=edge_to[u]->other(u)){
            flow_edge* fl = edge_to[u];
            fl->add_residual_flow_to(u,min_edge_capacity);
        }

        max_flow+=min_edge_capacity;
    }
}


void take_input(char *filename = NULL){
    if( filename ){
        fstream in;
        try{
            in = fstream(filename,ios_base::in);
        }
        catch( exception &e ){
            cerr<<e.what()<<endl;
        //    cout<<argv[1]<<" doesn't exist"<<endl;
        }

        in>>N;
        l.resize(N);
        w.resize(N);
        rem_g.resize(N);
        team_name.resize(N);
        g = vector<vector<int>> (N,vector<int>(N));

        for(int i=0;i<N;i++){
            in>>team_name[i];
            in>>w[i]>>l[i]>>rem_g[i];
            for(int j=0;j<N;j++)
                in>>g[i][j];
        } 

        try{
            in.close();
        }
        catch( exception &e){
            cerr<<e.what()<<endl;
        }
    }
    else {
        cin>>N;
        l.resize(N);
        w.resize(N);
        rem_g.resize(N);
        team_name.resize(N);
        g = vector<vector<int>> (N,vector<int>(N));

        for(int i=0;i<N;i++){
            cin>>team_name[i];
            cin>>w[i]>>l[i]>>rem_g[i];
            for(int j=0;j<N;j++)
                cin>>g[i][j];
        } 
    }
}

int main(int argc,char **argv){
    take_input( argc>=2 ? argv[1]: NULL) ;
    // check_inp();

    eliminated = vector<bool> (N,0);
    eliminated_by = vector<vector<int>> (N);
    int maxwin=w[0],maxwin_id=0;
    for(int i=1;i<N;i++){
        if( maxwin < w[i] ){
            maxwin = w[i];
            maxwin_id = i;
        }
    }

    //trivial elimination 
    for(int i=0;i<N;i++){
        if( w[i]+rem_g[i] < maxwin ){
            eliminated[i] = 1;
            eliminated_by[i].push_back(maxwin_id);
        }
    }


    for(int x=0;x<N;x++){
        if( eliminated[x] ) continue ;

        int V = N+(N*(N+1))/2+6;
        int source = V-1;
        int terminal = V-2;
        flow_network el_network(V);

        for(int team=0;team<N;team++){
            if( eliminated[team] ) continue ;

            flow_edge fl(team,terminal,double(w[x]+rem_g[x]-w[team]) );
            el_network.add_edge(fl);
        }

        int game_vertex = N-1 ;
        for(int team1=0;team1<N;team1++){
            for(int team2=team1+1;team2<N;team2++){
                game_vertex++;
                if( eliminated[team1] || eliminated[team2] ) continue ;

                flow_edge s_g(source,game_vertex,g[team1][team2]);
                flow_edge g_t1(game_vertex,team1,INFINITY);
                flow_edge g_t2(game_vertex,team2,INFINITY);
                el_network.add_edge(s_g); // source to gamevertex;
                el_network.add_edge(g_t1) ;
                el_network.add_edge(g_t2) ;
            }
        }


        // cout<<el_network<<endl;
        max_flow_ford_fulkerson(el_network,source,terminal);

        for(flow_edge* fe: el_network.adj[source]){
            if( fe->flow < fe->capacity )
                eliminated[x] = true;
        }

        has_augmenting_path_bfs(el_network,source,terminal);

        for(int u=0;u<N;u++){
            if( u == x ) continue ;

            if( marked[u] )
                eliminated_by[x].push_back(u);
        }
    }

    // output 
    cout<<endl;
    for(int team=0;team<N;team++){
        if( !eliminated[team] ) continue ;

        cout<<team_name[team]<<" is eliminated"<<endl;
        cout<<"They can win at most "<<w[team]<<" + "<<rem_g[team]<<" = " << w[team]+rem_g[team]<<" games"<<endl;
        cout<<team_name[eliminated_by[team][0]];
        int total_win_eliminates= w[eliminated_by[team][0]];
        for(int j=1;j<eliminated_by[team].size()-1;j++){
            cout<<","<<team_name[ eliminated_by[team][j] ];
            total_win_eliminates += w[ eliminated_by[team][j] ];
        }
        if( eliminated_by[team].size() > 1 ){
            int last = eliminated_by[team].size()-1;
            total_win_eliminates += w[ eliminated_by[team][last] ];
            cout<<" and "<<team_name[eliminated_by[team][last]]<<" have won a total of "<< total_win_eliminates <<" games"<<endl;

        }
        else {
            cout<<" has won total of "<< total_win_eliminates <<" games."<<endl;
        }
        int total_rem_games = 0;
        for(int i=0;i<eliminated_by[team].size();i++){
            for(int j=i+1;j<eliminated_by[team].size();j++){
                total_rem_games += g[ eliminated_by[team][i] ][ eliminated_by[team][j] ];
            }
        }
        cout<<"They play each other " << total_rem_games << " times"<<endl;
        // cout<<fixed<<setprecision(3);
        cout<<"So on average, each of the teams wins "  << (total_rem_games+total_win_eliminates)<<"/"<<eliminated_by[team].size()<<" = " << double(total_rem_games+total_win_eliminates)/double(eliminated_by[team].size()) << " games."<<endl;
        cout<<endl;
    }
}