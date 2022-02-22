#include<bits/stdc++.h>
#include "avltree.cpp"
using namespace std;


int main(){
   // freopen("inp.txt","r",stdin);
    avl_tree<int> tree;
    string cmd;
    int val; 
    while(cin>>cmd){
        if( cin.eof() )
           break;
        if( cmd == "F"){
            cin>>val;
            cout<<(tree.find(val)?"True":"False")<<endl;
        }
        else if( cmd == "I"){
            cin>>val;
            tree.insert(val);
            tree.print();
        }
        else if( cmd == "D"){
            cin>>val;
            tree.erase(val);
            tree.print();
        }
    }
}