#include<bits/stdc++.h>
#include "binomial_heap.cpp"
using namespace std;


int main(){
    string cmd;
    int val1,val2;
    binomial_heap bh;

    while(cin>>cmd){
        if( cin.eof() )
            break;
        if( cmd == "INS"){
            cin>>val1;
            bh.insert(val1);
            cout<<"Inserted "<<val1<<endl;
        }
        else if( cmd == "PRI"){
            cout<<"Printing binomial heap..."<<endl;
            cout<<"-----------------------------------\n";
            bh.print();
        }
        else if( cmd == "INC"){
            cin>>val1>>val2;
            try{
                bh.increase_key(val1,val2);
                cout<<"Increased "<<val1<<". The updated value is "<<val2<<endl;

            }
            catch( exception &e ){
                cerr<<e.what()<<endl;
            }
        }
        else if( cmd == "FIN" ){
            try{
                cout<<"FindMax returned "<<bh.find_max()<<endl;
            }catch( exception &e){
                cerr<<e.what()<<endl;
            }
        }
        else if( cmd == "EXT" ){
            try{
                cout<<"ExtractMax returned "<<bh.extract_max()<<endl;
            }
            catch( exception &e){
                cerr<<e.what()<<endl;
            }
        }
    }
}