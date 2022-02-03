#include <bits/stdc++.h>
using namespace std;


struct flow_edge {
    int u,v;
    double capacity;
    double flow;

    flow_edge(int u,int v,double capacity){
        if( capacity < 0.0 ) throw invalid_argument("capacity is negative!!");
        this->u = u;
        this->v = v;
        this->capacity=capacity;
        this->flow=0.0;
    }
    flow_edge(int u,int v,double capacity,double flow){
        if( capacity < 0.0 ) throw invalid_argument("capacity is negative");
        if( flow < 0.0 || flow > capacity ) throw invalid_argument("invalid flow: "+to_string(flow));
        this->u = u;
        this->v = v;
        this->capacity=capacity;
        this->flow=flow;
    }
    flow_edge(const flow_edge &fe)
        :flow_edge(fe.u,fe.v,fe.capacity,fe.flow)
    {
    }
    flow_edge()
        :flow_edge(0,0,0.0,0.0)
    {}

    flow_edge& operator=(const flow_edge& fe){
        this->u = fe.u;
        this->v = fe.v;
        this->capacity = fe.capacity;
        this->flow = fe.flow;

        return *this;
    }
    
    friend ostream& operator<<(ostream& out, flow_edge& fe){
        out<<fe.u<<"--->>"<<fe.v<<" capacity:"<<fe.capacity;
        return out;
    }
    int from() { return u; }
    int to() { return v; }
    int other(int vv){
        if( vv == v ) return u;
        else if( vv == u) return v;
        else{ 
            cout<<*this;
            throw invalid_argument("other(vv): "+ to_string(vv)+" is not in this edge.");
        }
    }

    double residual_capacity_to(int w){
        if( w == u) return flow;
        if( w == v) return capacity-flow;

        cout<<*this;
        throw invalid_argument("residual_capacity_to(w) "+to_string(w)+" doesn't belong to this edge");
    }

    void add_residual_flow_to(int w, double change){
        if( w == v ){
            flow += change;
        }
        else if( w == u){
            flow -= change;
        }
        else{
            cout<<*this;
            throw invalid_argument(to_string(w)+" doesn't belong to this edge");
        }

        if( flow < 0.0 || flow > capacity ) 
            throw invalid_argument("invalid flow after adding the change!! flow: " + to_string(flow) + " capacity: " + to_string(capacity) + " change: " + to_string(change) );
    }
};

struct flow_network{
    int V;
    vector<flow_edge*> edges;
    vector<flow_edge*> *adj;

    flow_network(int V){
        if( V < 0 ) throw invalid_argument(to_string(V)+" number of vertices cannot be negative");
        this->V = V;
        edges.clear();// this->E = 0;
        adj = new vector<flow_edge*>[V];
    } 

    flow_network(const flow_network &rhs){
        this->V = rhs.V;
        adj = new vector<flow_edge*> [V];
        for(int u=0;u<V;u++){
            for(flow_edge* fe: rhs.adj[u])
                add_edge(*fe);
        }
    }   

    ~flow_network(){
        delete [] adj;
        for(auto fl: edges)
            delete fl;
    }
    

    friend ostream& operator<<(ostream& out,flow_network &G){
        out<<G.V<<endl;
        for(int v = 0;v<G.V;v++){
            out<<v<<": ";
            for(flow_edge* fe: G.adj[v]){
                out<<*fe<<" ";
            }
            out<<endl;
        }

        for(flow_edge* fl: G.edges){
            out<<*fl<<endl;
        }
        return out;
    }
    void validate_vertex(int v){
        if( v < 0 || v >= V ) throw invalid_argument(to_string(v));
    }
    void add_edge(flow_edge &e){
        validate_vertex(e.u);
        validate_vertex(e.v);
        
        edges.push_back( new flow_edge(e) );

        adj[e.u].push_back( (*edges.rbegin()) );
        adj[e.v].push_back( (*edges.rbegin()) );
    }
};