import java.util.LinkedList;
import java.util.Queue;
import java.util.NoSuchElementException;

public class BinomialHeap{
    class Node{
        int value;
        int size;
        Node next;
        Node child;
        Node parent;

        public Node(){
            value = size = 0;
            next = child = parent =null;
        }
        public Node(int value){
            this.value = value;
            this.size = 1;
            next =null;
            parent =null;
            child =null;
        }

        public Node merge(Node that){
            if( that ==null ) 
                throw new IllegalArgumentException("cannot merge with anull node");
            if( that.size != this.size )
                throw new IllegalArgumentException("merge error: different size");
        
            that.parent = this;
            that.next = this.child;
            this.child = that;
            this.size = this.size + that.size;
            return this;
        }
        public Node find(int value){
            if( this.value == value )
                return this;
            Node found_node = (child!=null) ? child.find(value):null;
            if( found_node != null ) return found_node;
            found_node = (next!=null) ? next.find(value):null;          
            return found_node;
        }
        public void print(){
            Queue<Node> qq,qq2;
            int level = 0;
            System.out.println("Level "+level+": "+this.value);
            qq = new LinkedList<Node>();
            if( this.child !=null ) qq.add(this.child);
            while( !qq.isEmpty() ){
                qq2 = new LinkedList<>(); 
                System.out.println("Level "+(++level)+": ");   
                while( !qq.isEmpty() ){
                    Node head = qq.remove();
                    while( head !=null ){
                        System.out.print(head.value+" ");
                        if( head.child !=null ) qq2.add(head.child);
                        head = head.next;
                    }
                }
                System.out.println();
                qq = qq2;
            } 
        }
    }

    private Node head;
    public BinomialHeap(){
        head =null;
    }
    public void clear(){
        head =null;
    }
    private int size(Node h){
        int sz = 0;
        while( h !=null ){
            sz += h.size;
            h = h.next;
        }
        return sz;
    }
    public int size(){
        return size(head);
    }
    public void print(){
        int sz = size();
        System.out.print("Heap size: "+sz+"(");
        StringBuffer s = new StringBuffer();
        while( sz != 0 ){
            char ch = ((sz&1) == 1) ? '1':'0' ;
            s.append(ch);
            sz >>=1;
        }
        s = s.reverse();
        System.out.println(s+")");
        int i=0;
        Node h = head;
        sz = size();
        while( sz != 0 ){
            if( (sz&1) == 1 ){
                System.out.println("Binomial Tree: B"+i);
                h.print();
                h = h.next;
            }
            i++;
            sz >>= 1;
        }
        System.out.println();
    }
    private Node reverse(Node h){
        if( h ==null ) 
            return null;
        if( h.next ==null)
            return h;
        reverse(h.next).next = h;
        h.next =null;
        return h;
    }
    private Node reverse_list(Node h){
        if( h ==null ) return h;
        Node new_head = h;
        while( new_head.next !=null)
            new_head = new_head.next;
        
        reverse(h);
        return new_head;
    }

    private Node merge(Node node1, Node node2){
        int size1=size(node1),size2=size(node2);
   
        Node carry =null;
        Node merge_head =null;
        Node merge_tail =null;
        Node next1 =null,next2 =null;

        while( size1!=0 || size2!=0 ){
            int sum = (size1&1) + (size2&1) + ((carry!=null) ? 1:0);
            next1 = node1;
            next2 = node2;
            if( (sum&1) == 1 ){
                if( carry !=null ) {
                    if( merge_head ==null ){
                        merge_head = carry;
                        merge_tail = merge_head;
                    }
                    else {
                        merge_tail.next = carry;
                        merge_tail = merge_tail.next;
                    }
                    carry =null;
                }
                else if( (size1&1) == 1 ){
                    next1 = node1.next;
                    if( merge_head ==null ){
                        merge_head = node1;
                        merge_tail = merge_head;
                    }
                    else {
                        merge_tail.next = node1;
                        merge_tail = merge_tail.next;
                    }
                }
                else if( (size2&1) == 1 ){
                    next2 = node2.next;
                    if( merge_head ==null ){
                        merge_head = node2;
                        merge_tail = merge_head;
                    }
                    else {
                        merge_tail.next = node2;
                        merge_tail = merge_tail.next;
                    }
                }                
            }
            if( (sum&2) != 0 ){
                if( (size1&1) == 1 && (size2&1) == 1 ){
                    next1 = node1.next;
                    next2 = node2.next;
                    if( node1.value > node2.value )
                        carry = node1.merge(node2);
                    else carry = node2.merge(node1);
                }
                else if( (size1&1) == 1 && (carry!=null) ){
                    next1 = node1.next;
                    if( node1.value > carry. value )
                        carry = node1.merge(carry);
                    else carry = carry.merge(node1);
                }
                else if( (size2&1) == 1 && (carry!=null) ){
                    next2 = node2.next;
                    if( node2.value > carry.value){
                        carry = node2.merge(carry);
                    }
                    else carry = carry.merge(node2);
                }
            }
            node1 = next1;
            node2 = next2;
            size1 >>= 1;
            size2 >>= 1;
        }

        if( carry !=null ){
            if( merge_head ==null ){
                merge_head = carry;
                merge_tail = merge_head;
            }
            else {
                merge_tail.next = carry;
                merge_tail = merge_tail.next;
            }
        }
        if( merge_tail !=null) merge_tail.next =null;

        if( merge_head !=null ){
            Node h = merge_head;
            while( h!=null){
                h.parent=null;
                h = h.next;
            }
        }
        return merge_head;
    }

    public void insert(int value){
        Node head2 = new Node(value);
        head = merge(head,head2);
    }

    Node max_node(){
        if( size() == 0 )
            throw new NoSuchElementException("heap is empty!!");
        
        Node h = head;
        Node m_node = head;
        h = h.next;
        while( h !=null ){
            if( m_node.value < h.value ){
                m_node = h;
            }
            h = h.next;
        }
        return m_node;
    }
    int find_max(){
        return max_node().value ;
    }
    void delete_max(){
        Node m_node = max_node();
        Node h = head ;
        if( m_node == head )
            head = m_node.next;
        else {
            while( h.next != m_node ){
                h = h.next;
            }
            h.next = m_node.next;
        }
       
        m_node.next =null;
        Node ch = reverse_list(m_node.child);
     
        head = merge(head,ch);
        m_node.child =null;
    }
    int extract_max(){
        int mx = find_max();
        delete_max();
        return mx;
    }
    void increase_key(int val,int new_val){
        if( size() == 0 )
            throw new NoSuchElementException("heap is empty!!");

        Node fnd= head.find(val);
        if( fnd ==null)            
            throw new IllegalArgumentException("increase_key: key not found!");
    
        if( new_val< val )
            throw new IllegalArgumentException("increase_key: new value must be bigger than pervious one");
        
        fnd.value = new_val;
        while( fnd.parent !=null && (fnd.parent).value < new_val ){
            int temp = (fnd.parent).value ;
            (fnd.parent).value = fnd.value;
            fnd.value = temp;
            
            fnd = fnd.parent;
        }
    }

    void erase(int val){
        if( size() == 0 )
            throw new NoSuchElementException("heap is empty!!");

        Node fnd = head.find(val);
        if( fnd ==null )
            return ;
        
        while( fnd.parent !=null ){
            int temp = (fnd.parent).value;
            (fnd.parent).value = fnd.value;
            fnd.value = temp;

            fnd = fnd.parent;
        }

        Node h = head;
        if( head == fnd )
            head = head.next;
        else {
            while( h.next != fnd ){
                h = h.next;
            }
            h.next = fnd.next;
        }

        fnd.next =null;
        Node ch = reverse_list(fnd.child);
        head = merge(head,ch);
        fnd.child =null;
    }
}