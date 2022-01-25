#include <bits/stdc++.h>
using namespace std;


struct binomial_heap{
    struct node {
        int value=0;
        node *parent = NULL;
        node *next = NULL;
        node *child = NULL;
        int size=0;

        node(){
            value = size = 0;
            child = parent = next = NULL;
        }
        node(int value){
            this->value = value;
            this->size = 1;
            child=parent=next = NULL;
        }
        ~node(){
            delete child;
            delete next;
            // cout<<"deleted "<<value<<endl;
        }

        node* find(int val){
            if( this->value == val )
                return this;
            node *found_node = (child != NULL ) ? child->find(val):NULL;
            if( found_node != NULL )    return found_node;
            found_node = (next != NULL) ? next->find(val):NULL;
            return found_node;
        }
        node* merge(node* node2){
            if( node2 == NULL ) 
                throw invalid_argument("NULL node received");
            if( size != node2->size )
                throw invalid_argument("cannot merge!!") ;
            
            node2->parent = this;
            node2->next = this->child;
            this->child = node2;
            this->size = this->size+node2->size;
            return this;
        }

        void print(){
            queue<node*> qq,qq2;
            int level = 0;
            cout<<"Level "<<level<<": "<<this->value<<endl;
            if( this->child != NULL ) qq.push(this->child);
            while( !qq.empty() ){
                qq2 = queue<node*> (); 
                cout<<"Level "<<++level<<": ";   
                while( !qq.empty() ){
                    node* head = qq.front() ;
                    while( head != NULL ){
                        cout<<head->value<<" ";
                        if( head->child != NULL ) qq2.push(head->child);
                        head = head->next;
                    }
                    qq.pop();
                }
                cout<<endl;
                qq = qq2;
            } 
        }
    };
    node *head;
    binomial_heap(){
        head = NULL;
    }  
    ~binomial_heap(){
        delete head;
    }
    void print2(){
        int sz = size();
        cout<<"Heap size: "<<sz<<endl;
        string s;
        while( sz ){
            s += char( '0'+(sz&1) );
            sz >>=1;
        }
        std::reverse(s.begin(),s.end());
        cout<<s<<endl;
        if( head != NULL ) head->print();
    }

    void print(){
        int sz = size();
        node *h = head;
        int i=0;
        while( sz ){
            if( sz&1 ){
                cout<<"Binomial Tree: B"<<i<<endl;
                h->print();
                h = h->next;
            }

            i++;
            sz >>= 1;
        }
    }
    int size(node* head){
        int sz=0;
        while( head != NULL ){
            sz += head->size;
            head = head->next;
        }
        return sz;
    }
    node* reverse(node *h){
        if( h == NULL ) 
            return NULL;
        if( h->next == NULL)
            return h;
        reverse(h->next)->next = h;
        h->next = NULL;
        return h;
    }
    node* reverse_list(node *h){
        if( h == NULL ) return h;
        node* new_head = h;
        while( new_head->next != NULL)
            new_head = new_head->next;
        
        reverse(h);
        return new_head;
    }
    node* merge(node *node1, node *node2){
        int size1=size(node1),size2=size(node2);
   
        node *carry = NULL;
        node *merge_head = NULL;
        node *merge_tail = NULL;
        node *next1 =NULL,*next2 = NULL;

        while( size1 || size2 ){
            int sum = (size1&1)+(size2&1)+(carry!=NULL);
            next1 = node1;
            next2 = node2;
            if( sum&1 ){
                if( carry != NULL ) {
                    if( merge_head == NULL ){
                        merge_head = carry;
                        merge_tail = merge_head;
                    }
                    else {
                        merge_tail->next = carry;
                        merge_tail = merge_tail->next;
                    }
                    carry = NULL;
                }
                else if( size1&1 ){
                    next1 = node1->next;
                    if( merge_head == NULL ){
                        merge_head = node1;
                        merge_tail = merge_head;
                    }
                    else {
                        merge_tail->next = node1;
                        merge_tail = merge_tail->next;
                    }
                }
                else if( size2&1 ){
                    next2 = node2->next;
                    if( merge_head == NULL ){
                        merge_head = node2;
                        merge_tail = merge_head;
                    }
                    else {
                        merge_tail->next = node2;
                        merge_tail = merge_tail->next;
                    }
                }                
            }
            if( sum&2 ){
                if( (size1&1) && (size2&1) ){
                    next1 = node1->next;
                    next2 = node2->next;
                    if( node1->value > node2->value )
                        carry = node1->merge(node2);
                    else carry = node2->merge(node1);
                }
                else if( (size1&1) && (carry!=NULL) ){
                    next1 = node1->next;
                    if( node1->value > carry-> value )
                        carry = node1->merge(carry);
                    else carry = carry->merge(node1);
                }
                else if( (size2&1) && (carry!=NULL) ){
                    next2 = node2->next;
                    if( node2->value > carry->value){
                        carry = node2->merge(carry);
                    }
                    else carry = carry->merge(node2);
                }
            }
            node1 = next1;
            node2 = next2;
            size1 >>= 1;
            size2 >>= 1;
        }

        if( carry != NULL ){
            if( merge_head == NULL ){
                merge_head = carry;
                merge_tail = merge_head;
            }
            else {
                merge_tail->next = carry;
                merge_tail = merge_tail->next;
            }
        }
        if( merge_tail != NULL) merge_tail->next = NULL;

        if( merge_head != NULL ){
            node* h = merge_head;
            while( h!=NULL){
                h->parent=NULL;
                h = h->next;
            }
        }
        return merge_head;
    }

    int size(){
        return size(head);
    }
    void insert(int value){
        node *head2 = new node(value);
        head = merge(head,head2);
    }

 
    node* max_node(){
        if( size() == 0 )
            throw underflow_error("heap is empty!!");
        
        node* h = head;
        node* m_node = head;
        h = h->next;

        while( h != NULL ){
            if( m_node->value < h->value ){
                m_node = h;
            }
            h = h->next;
        }
        return m_node;
    }
    int find_max(){
        return max_node()->value ;
    }
    void delete_max(){
        node* m_node = max_node();
        
        node* h = head ;
        if( m_node == head )
            head = m_node->next;
        else {
            while( h->next != m_node ){
                h = h->next;
            }
            h->next = m_node->next;
        }
       
        m_node->next = NULL;
        node* ch = reverse_list(m_node->child);
     
        head = merge(head,ch);
        m_node->child = NULL;

        delete m_node ;
    }
    int extract_max(){
        int mx = find_max();
        delete_max();
        return mx;
    }

    void increase_key(int val,int new_val){
        if( size() == 0 )
            throw underflow_error("heap is empty!!");

        node* fnd= head->find(val);
        if( fnd == NULL)            
            throw invalid_argument("increase_key: key not found!");
    
        if( new_val< val )
            throw invalid_argument("increase_key: new value must be bigger than pervious one");
        
        fnd->value = new_val;
        while( fnd->parent != NULL && (fnd->parent)->value < new_val ){
            int temp = (fnd->parent)->value ;
            (fnd->parent)->value = fnd->value;
            fnd->value = temp;
            
            fnd = fnd->parent;
        }
    }

    void erase(int val){
        if( size() == 0 )
            throw underflow_error("heap is empty!!");

        node *fnd = head->find(val);
        if( fnd == NULL )
            return ;
        
        while( fnd->parent != NULL ){
            int temp = (fnd->parent)->value;
            (fnd->parent)->value = fnd->value;
            fnd->value = temp;

            fnd = fnd->parent;
        }

        node *h = head;
        if( head == fnd )
            head = head->next;
        else {
            while( h->next != fnd ){
                h = h->next;
            }
            h->next = fnd->next;
        }

        fnd->next = NULL;
        node* ch = reverse_list(fnd->child);
        head = merge(head,ch);
        fnd->child = NULL;
        delete fnd;
    }
};