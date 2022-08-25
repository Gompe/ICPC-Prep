#include <iostream>

using namespace std;

class Node{

public:
    Node left;
    Node right;
    int value;

    void Node(int v, Node l, Node r){
        left = l;
        right = r;
        value = v;
    }

    void printValue(){
        cout<<value;
    }
};

int main(){

}
