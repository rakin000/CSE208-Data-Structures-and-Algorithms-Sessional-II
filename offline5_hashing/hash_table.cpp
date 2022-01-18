#include <bits/stdc++.h>
using namespace std;


uint64_t hash1(string key, uint64_t mod = UINT64_MAX){
    uint64_t hash = 537;

    for(char c: key){
        hash = ( ((hash<<5)-hash) + c  )%mod;
    }
    return hash;
}

uint64_t hash2(string key, uint64_t mod = UINT64_MAX){
    uint64_t hash = 0;

    for(char c: key){
        hash = ( (hash<<3)-hash+c )%mod;
    }
    return hash;
}

uint64_t hash3(string key,uint64_t mod = UINT64_MAX){
    return 3-hash2(key)%3;
}

uint64_t hash4(string key,uint64_t mod = UINT64_MAX){
    return 5-hash1(key)%5;
}


struct separate_chaining_HT {
    struct element {
        string key;
        int value;
    };
    int N;
    int64_t collisions = 0;
    int64_t probes = 0;
    vector<list<element>> T;
    uint64_t (*hash_func)(string, uint64_t);

    
    separate_chaining_HT(int capacity, uint64_t (*hash_f)(string, uint64_t ) ){
        N = capacity;
        T.resize(N);
        this->hash_func = hash_f;
    }

    friend ostream& operator<<(ostream &out, separate_chaining_HT &scht){
        for(int i=0;i<scht.N;i++){
            out<<i<<": ";
            list<element>::iterator head = scht.T[i].begin();
            while( head != scht.T[i].end() ){
                out<<"("<<head->key<<", "<<head->value<<")"<<" ";
                head++;
            }
            out<<endl;
        }
        return out;
    }
 
    int search(string k){
        int hsh = hash_func(k, UINT64_MAX)%N;

        list<element>::iterator head = T[hsh].begin();
        while( head != T[hsh].end() && head->key != k ){
            probes++;
            head++;
        }
        probes += (head!=T[hsh].end());

        return (head == T[hsh].end()) ? -1:head->value;
    }

    void insert(string key,int value){
        int hsh = hash_func(key, UINT64_MAX)%N;

        list<element>::iterator head = T[hsh].begin();

        while( head != T[hsh].end() ){
            if( head->key == key ){
                head->value = value ;
                return ; 
            }
            ++collisions;
            ++head;
        }
        T[hsh].push_back({key,value});
        return ;
    }

    void erase(string key){
        int hsh = hash_func(key, UINT64_MAX)%N;

        list<element>::iterator head = T[hsh].begin();
        while( head != T[hsh].end() && head->key != key ){
            head++;
        }
        
        if( head != T[hsh].end()) 
            T[hsh].erase(head);
    }

};


struct double_hash_HT{
    struct element {
        string key;
        int value;
    };
    int N;
    int64_t collisions = 0;
    int64_t probes = 0;
    uint64_t (*hash_func1)(string, uint64_t);
    uint64_t (*hash_func2)(string, uint64_t);
    vector<element> T;
    
    double_hash_HT(int size, uint64_t (*hash_f1)(string, uint64_t ), uint64_t (*hash_f2)(string, uint64_t )){
        N = size;
        hash_func1 = hash_f1;
        hash_func2 = hash_f2;
        T.resize(N);
        for(int i=0;i<N;i++)
            T[i].key = "", T[i].value = -1;
    }
    uint64_t calc_hash(string key,int i){
        return (hash_func1(key,UINT64_MAX) + i*hash_func2(key,UINT64_MAX) )%N ;
    }
    friend ostream& operator<<(ostream &out, double_hash_HT &dhht ){
        for(int i=0;i<dhht.N;i++){
            out<<"("<<dhht.T[i].key<<", "<<dhht.T[i].value<<")"<<endl; 
        }
        return out;
    }

    void insert(string key, int value){
        int i = 0;
        int hash = calc_hash(key,i);// doubleHash(k, i) = (Hash(k) + i × auxHash(k)) % N

        if( T[hash].key == "" ){
            T[hash].key = key;
            T[hash].value = value;
            return ;
        }

        
        while( i<N && T[hash].key != "" ){
            if( T[hash].key == key){
                T[hash].value = value ;
                return ;
            }
            ++collisions;
            ++i;
            hash = calc_hash(key,i);
        }

        T[hash].key = key;
        T[hash].value = value;
    }

    int search(string key){
        int i = 0;
        int hash = calc_hash(key,i);

        while( i<N && T[hash].key != "" ){
            ++probes;
            if( T[hash].key == key ){
                return T[hash].value;
            }
            i++;
            hash = calc_hash(key,i);
        }

        return -1;
    }

    void erase(string key){
        int i = 0;
        int hash = calc_hash(key,i);

        while( i<N && T[hash].key != "" ){
            if( T[hash].key == key ){
                T[hash].value = -1;
                return ;
            }
            i++;
            hash = calc_hash(key,i);
        }
    }
};

struct custom_hashing_HT{
    struct element {
        string key;
        int value;
    };
    int N;
    int64_t collisions = 0;
    int64_t probes = 0;
    uint64_t (*hash_func1)(string, uint64_t);
    uint64_t (*hash_func2)(string, uint64_t);
    vector<element> T;
    
    custom_hashing_HT(int size, uint64_t (*hash_f1)(string, uint64_t ), uint64_t (*hash_f2)(string, uint64_t )){
        N = size;
        hash_func1 = hash_f1;
        hash_func2 = hash_f2;
        T.resize(N);
        for(int i=0;i<N;i++)
            T[i].key = "", T[i].value = -1;
    }
    uint64_t calc_hash(string key,int i){
        uint64_t c1 = 5;
        uint64_t c2 = 3;
        return (hash_func1(key,UINT64_MAX) + c1*i*hash_func2(key,UINT64_MAX) + c2*i*i)%N ; //customHash(k, i) = (Hash(k) + C1 × i × auxHash(k) + C2 × i2) % N
    }
    friend ostream& operator<<(ostream &out, custom_hashing_HT &chht ){
        for(int i=0;i<chht.N;i++){
            out<<"("<<chht.T[i].key<<", "<<chht.T[i].value<<")"<<endl; 
        }
        return out;
    }

    void insert(string key, int value){
        int i = 0;
        int hash = calc_hash(key,i);// doubleHash(k, i) = (Hash(k) + i × auxHash(k)) % N

        if( T[hash].key == "" ){
            T[hash].key = key;
            T[hash].value = value;
            return ;
        }

        
        while( i<N && T[hash].key != "" ){
            if( T[hash].key == key){
                T[hash].value = value ;
                return ;
            }
            ++collisions;
            ++i;
            hash = calc_hash(key,i);
        }

        T[hash].key = key;
        T[hash].value = value;
    }

    int search(string key){
        int i = 0;
        int hash = calc_hash(key,i);

        while( i<N && T[hash].key != "" ){
            ++probes;
            if( T[hash].key == key ){
                return T[hash].value;
            }
            i++;
            hash = calc_hash(key,i);
        }

        return -1;
    }

    void erase(string key){
        int i = 0;
        int hash = calc_hash(key,i);

        while( i<N && T[hash].key != "" ){
            if( T[hash].key == key ){
                T[hash].value = -1;
                return ;
            }
            i++;
            hash = calc_hash(key,i);
        }
    }
};


struct linear_probing_HT{
    struct element {
        string key;
        int value;
    };
    int N;
    int64_t collisions = 0;
    int64_t probes = 0;
    uint64_t (*hash_func1)(string, uint64_t);
    uint64_t (*hash_func2)(string, uint64_t);
    vector<element> T;
    
    linear_probing_HT(int size, uint64_t (*hash_f1)(string, uint64_t ), uint64_t (*hash_f2)(string, uint64_t )){
        N = size;
        hash_func1 = hash_f1;
        hash_func2 = hash_f2;
        T.resize(N);
        for(int i=0;i<N;i++)
            T[i].key = "", T[i].value = -1;
    }
    uint64_t calc_hash(string key,int i){
        return (hash_func1(key,UINT64_MAX)+i)%N; //customHash(k, i) = (Hash(k) + C1 × i × auxHash(k) + C2 × i2) % N
    }
    friend ostream& operator<<(ostream &out, linear_probing_HT &chht ){
        for(int i=0;i<chht.N;i++){
            out<<"("<<chht.T[i].key<<", "<<chht.T[i].value<<")"<<endl; 
        }
        return out;
    }

    void insert(string key, int value){
        int i = 0;
        int hash = calc_hash(key,i);// doubleHash(k, i) = (Hash(k) + i × auxHash(k)) % N

        if( T[hash].key == "" ){
            T[hash].key = key;
            T[hash].value = value;
            return ;
        }

        while( i<N && T[hash].key != "" ){
            if( T[hash].key == key){
                T[hash].value = value ;
                return ;
            }
            ++collisions;
            ++i;
            hash = calc_hash(key,i);
        }

        T[hash].key = key;
        T[hash].value = value;
    }

    int search(string key){
        int i = 0;
        int hash = calc_hash(key,i);

        while( i<N && T[hash].key != "" ){
            ++probes;
            if( T[hash].key == key ){
                return T[hash].value;
            }
            i++;
            hash = calc_hash(key,i);
        }

        return -1;
    }

    void erase(string key){
        int i = 0;
        int hash = calc_hash(key,i);

        while( i<N && T[hash].key != "" ){
            if( T[hash].key == key ){
                T[hash].value = -1;
                return ;
            }
            i++;
            hash = calc_hash(key,i);
        }
    }
};
