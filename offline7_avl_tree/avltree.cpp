#include <bits/stdc++.h> 
using namespace std;

template<typename Type>
class avl_tree{
    class node{
        public:
        Type value;
        int height;
        node *left;
        node *right;

        node(Type value){
            this->value =value;
            this->height=0;
            this->left=nullptr;
            this->right=nullptr;
        }
        node() {
            this->height=0;
            this->left=nullptr;
            this->right=nullptr;
        }
        ~node(){
            delete left;
            delete right;
            // cout<<"Deleting "<<value<<endl;
        }
    };

    node* root;
    void recalc_height(node *x){
        if( x == nullptr ) return ;
        x->height=1+max(height(x->left),height(x->right));
    }
    void print_(node *x){
        if (x == nullptr)
            return;
        cout << x->value;
        if( x->left == nullptr && x->right==nullptr)
            return ;
        cout << "("; print_(x->left); cout << ")";
        cout << "("; print_(x->right); cout << ")";
    }
    int height(node *x){
        if( x == nullptr ) return -1;
        return x->height ;
    }
    node* insert_(node *x, Type value){
        if( x == nullptr )
            return new node(value);
        
        if( value < x->value )
            x->left = insert_(x->left, value) ;
        else 
            x->right = insert_(x->right, value);
        
        recalc_height(x);
        // cout<<x->height<<endl;
        x = preserve_avl(x);
        return x;
    }
    node* find_(node *x, Type value ){
        if( x == nullptr )
            return nullptr; 
        if( x->value == value ) 
            return x;
        if( value < x->value )
            return find_(x->left,value);
        return find_(x->right,value);
    }
    node* erase_(node *x, Type value){
        if( x == nullptr )
            return x;
        if( x->value == value ){
            if( x->left == nullptr && x->right == nullptr )
                return nullptr; 
            else if( x->left == nullptr )
                x = x->right;
            else if( x->right == nullptr )
                x = x->left; 
            else {
                node* right_min = find_min(x->right);
                x->value = right_min->value ;
                x->right = erase_(x->right,right_min->value);
            }

            recalc_height(x);
            x = preserve_avl(x);
            return x ;
        }

        if( value < x->value )
            x->left = erase_(x->left,value);
        else 
            x->right = erase_(x->right,value);
        
        recalc_height(x);
        x = preserve_avl(x);
        return x ;
    }
    node* find_max(node *x) {
        if( x == nullptr ) return x;

        while( x->right != nullptr )
            x = x->right;
        return x;
    }
    node* find_min(node *x){
        if( x == nullptr ) return x;

        while( x->left != nullptr )
            x = x->left ;
        return x;
    }

    node* right_rotate(node *x){
        if( x == nullptr ) return x ;
        if( x->left == nullptr ) return x ;

        node* y = x->left ;
        x->left = y->right ;
        y->right = x; 
        recalc_height(x);
        recalc_height(y);
        return y ; 
    }
    node* left_rotate(node *x) {
        if( x == nullptr) return x ;
        if( x->right == nullptr ) return x;

        node *y=x->right;
        x->right = y->left ;
        y->left = x;
        recalc_height(x);
        recalc_height(y);
        return y;
    }
    node* preserve_avl(node *x) {
        // cout<<"preserve_avl" <<height(x->left)<<"  "<<height(x->right)<<endl;
        if( x == nullptr || abs(height(x->left)-height(x->right)) <= 1 ){
            return x;   
        }
        cout<<"Height invariant violated.\n";
        cout<<"After rebalancing: ";
        if(height(x->left) > height(x->right)) {
            // cout<<"zig ";
            if( height(x->left->right) > height(x->left->left) ){
                // cout<<"zag"<<endl;
                x->left = left_rotate(x->left);
            }
            // else cout<<"zig"<<endl;
            x = right_rotate(x);
        }
        else {
            // cout<<"zag ";
            if( height(x->right->left) > height(x->right->right) ){
                // cout<<"zig"<<endl;
                x->right = right_rotate(x->right);
            }
            // else cout<<"zag"<<endl;
            x = left_rotate(x);
        }
        return x;
    }
    public: 
    avl_tree(){
        root = nullptr;
    }
    ~avl_tree(){
        delete root;
    }
    void print(){
        print_(root);
        cout<<endl;
    }
    void insert(Type value){
        root = insert_(root,value);
    }
    void erase(Type value){
        if(root == nullptr )
            throw underflow_error("empty tree!!");
        root = erase_(root,value);
    }
    bool find(Type value){
        return (find_(root,value) != nullptr);
    }
};


void test(){
    avl_tree<int> tree; 

    tree.insert(30);
    tree.print();
    tree.insert(15);
    tree.print();
    tree.insert(10);
    tree.print();
}