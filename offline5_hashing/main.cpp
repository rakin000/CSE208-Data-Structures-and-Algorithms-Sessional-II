#include <bits/stdc++.h>
#include "hash_table.cpp"

using namespace std;


string random_word(int len){
    string s = "";
    for(int i=0;i<len;i++)
        s += char ( rand()%('z'-'a'+1)+'a' );
    return s;
}


double values[] = {0,0,0,0,0,0};
void run(int seed){
     //generate unique words;
    srand(seed);
    int N = 10000;
    map<string,int> mp;
    vector<string> words;
    int i = 0;
    while( i<N ){
        string ran_w = random_word(7);
        if( mp.count(ran_w) ){
            continue ;
        }
        else {
            mp[ran_w] = 31;
            words.push_back(ran_w);
            i++;
        }
    }

    separate_chaining_HT scht(N,hash2);
    double_hash_HT dhht(2*N,hash2,hash4);
    custom_hashing_HT chht(2*N,hash2,hash4);


    for(int i=0;i<N;i++){
        scht.insert(words[i],i+1);
        dhht.insert(words[i],i+1);
        chht.insert(words[i],i+1);
    }

   
    values[0] += scht.collisions;
    values[1] += dhht.collisions;
    values[2] += chht.collisions;

    // randomize first M entries;
    const int M = 1000;
    for(int i=0;i<M;i++){
        int r = i+rand()%(M-i);
        swap(words[i],words[r]);
    }

    for(int i=0;i<M;i++){
        if( scht.search(words[i]) == -1 ) cout<<"error\n";
        if( dhht.search(words[i]) == -1 ) cout<<"error\n";
        if( chht.search(words[i]) == -1 ) cout<<"error\n";
    }

   

    values[3] += scht.probes;
    values[4] += dhht.probes;
    values[5] += chht.probes;
}

int main(){
    for(int i=0;i<10;i++){
        run(i);
    }

    cout<<"Collisions in separate chaining: " << values[0]/10.0<<endl;
    cout<<"Collisions in double hashing: " << values[1]/10.0<<endl;
    cout<<"Collisions in custom hashing: "<< values[2]/10.0<<endl;

    cout<<"Probes for separate chaining: "<< values[3]/10.0 <<endl;
    cout<<"Probes for double hashing: "<< values[4]/10.0 <<endl;
    cout<<"Probes for custom hashing: "<< values[5]/10.0 <<endl;

}