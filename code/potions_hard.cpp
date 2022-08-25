#include <iostream>
#include <algorithm>

using namespace std;

struct Node{
    long long h, k;
    Node * down = nullptr;

    Node(long long kc, long long hc){
        k = kc;
        h = hc;
    }
};

Node* top = new Node(0,0);

void insertion(long long a){

    if(top->h+a>=0){
        Node* new_top = new Node(top->k+1, top->h+a);
        new_top->down = top;
        top = new_top;
    }

    Node* qnode = top;
    while(qnode->down != nullptr){
        if(qnode->k-1 == (qnode->down)->k){
            qnode->h = max(qnode->h, (qnode->down)->h + a);
            qnode = qnode->down;
        }
        else{
            if(a+ (qnode->down)->h > qnode->h){
                Node* new_node = new Node(1+qnode->down->k,a+ (qnode->down)->h);
                new_node->down = qnode->down;
                qnode->down = new_node;
                qnode = new_node->down;
            }
        }
    }
    qnode = top;
    while(qnode->down != nullptr){
        if(qnode->down->h <= qnode->h){
            if(qnode->down->down == nullptr){
                delete(qnode->down);
                qnode->down = qnode->down->down;
                continue;
            }
        }
        qnode = qnode->down;
    }
    return;
}

void answer(){
    printf("%lld\n", top->k);
}

int main(){
    long long n;
    scanf("%lld", &n);

    long long a;
    for(int i=0; i<n; ++i){
        scanf("%lld", &a);
        insertion(a);
    }

    answer();
    return 0;
}
