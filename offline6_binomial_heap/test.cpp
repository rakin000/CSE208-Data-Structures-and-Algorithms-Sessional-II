#include <iostream>
#include "binomial_heap.cpp"
using namespace std;
int main(){
    binomial_heap bh;
    bh.insert(3);
    bh.insert(4);
    bh.insert(5);
    bh.insert(6);
    bh.insert(9);
    bh.insert(10);
    bh.insert(11);
    bh.insert(12);
    bh.insert(1);
    bh.insert(2);
    bh.insert(13);
    bh.insert(14);
    bh.insert(15);
    bh.insert(16);
    bh.insert(17);
    bh.insert(18);
    bh.delete_max();
    bh.print();
  
    bh.delete_max();
    bh.print();

    bh.delete_max();
    bh.print();

    bh.delete_max();
    bh.print();

    bh.delete_max();
    bh.print();

    bh.delete_max();
    bh.print();

     bh.delete_max();
    bh.print();

     bh.delete_max();
    bh.print();

     bh.delete_max();
    bh.print();

     bh.delete_max();
    bh.print();

     bh.delete_max();
    bh.print();

     bh.delete_max();
    bh.print();

     bh.delete_max();
    bh.print();

    

    bh.insert(323);
    bh.print();

    bh.increase_key(3,50);
    bh.print();
    bh.increase_key(2,400);
    bh.print();
    bh.increase_key(1,500);
    bh.print();

    bh.erase(50);
    bh.print();

    bh.erase(2344);
    bh.print();

    bh.erase(400);
    bh.print();

    bh.erase(500);
    bh.print();

    bh.erase(500);
    bh.print();

    bh.erase(323);
    bh.print();
    bh.erase(343);
    bh.print();
}