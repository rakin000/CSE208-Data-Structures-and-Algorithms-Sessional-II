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
            cout<<"deleted "<<value<<endl;
        }

        node* find(int value){
            if( this->value == value )
                return this;
            if( this->value < value) 
                return NULL;

            node *found_node = child->find(value);
            if( found_node != NULL )
                return found_node;
            found_node = next->find(value);
            return found_node;
        }
        node* merge(node* node2){
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
            qq.push(this);
           // cout<<this->value<<endl;
            while( !qq.empty() ){
                qq2 = queue<node*> ();    
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
    void print(){
        int sz = size();
        cout<<"Heap size: "<<sz<<endl;
        string s;
        while( sz ){
            s += char( '0'+(sz&1) );
            sz >>=1;
        }
        std::reverse(s.begin(),s.end());
        cout<<s<<endl;
        head->print();
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
        // h->next = NULL;
        return new_head;
    }
    node* merge(node *node1, node *node2 ){
        int size1=size(node1),size2=size(node2);

        node *carry = NULL;
        node *merge_head = NULL, *merge_tail = NULL;
        node *next1 =NULL,*next2 = NULL;

        while( size1 || size2 ){
            int b1=size1&1,b2=size2&1,b3=carry!=NULL;
            int sum = b1+b2+b3;

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


        merge_tail->next = NULL;
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
    int extract_max(){
        if( size() == 0 ){
            throw underflow_error("heap is empty!!");
        }
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
};