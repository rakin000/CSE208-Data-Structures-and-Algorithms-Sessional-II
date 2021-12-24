class unionfind{
    int n;
    int *id ;
    int *size_ ;
    public:
    unionfind(int n){
        this->n = n;
        id = new int[n];
        size_ = new int[n];
        for(int i=0;i<n;i++){
            id[i] = i;
            size_[i] = 1;
        }
    }
    ~unionfind(){
        delete [] id;
        delete [] size_;
    }
    int find(int u){
        if(u < 0 || u >= n)
            throw "Out of range!!";
        while(id[u] != u){
            id[u] = id[id[u]];
            u = id[u] ;
        }
        return u;
    }
    void connect(int u,int v){
        int pu = find(u);
        int pv = find(v);

        if(pu == pv) return ;
        else if( size_[pu] > size_[pv] ){
            id[pv] = pu ;
            size_[pu] += size_[pv] ;
        }else {
            id[pu] = pv;
            size_[pv] += size_[pu] ;
        }
        return ;
    }
    int size(int u){
        if(u < 0 || u >= n)
            throw "Out of range!!";
        return size_[find(u)];
    }
};
