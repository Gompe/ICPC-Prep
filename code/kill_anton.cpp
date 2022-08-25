#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Node{
    // DLinked list
    char ch;
    Node* right = nullptr;

    Node( char c ){
        ch = c;
    }
};

struct DNA{
    Node* lastA = nullptr;
    Node* lastT = nullptr;
    Node* lastO = nullptr;
    Node* lastN = nullptr;

    Node* firstNode=nullptr;

    void appendGene(char c){
        Node* nodeptr = new Node(c);
        if( firstNode == nullptr ){
            firstNode = nodeptr;
            if(c=='A')
                lastA = nodeptr;
            if(c=='T')
                lastT = nodeptr;
            if(c=='O')
                lastO = nodeptr;
            if(c=='N')
                lastN = nodeptr;
            return;
        }

        if( c=='A' ){
            if(lastA == nullptr){
                lastA = nodeptr;
                nodeptr->right = firstNode;
                firstNode = nodeptr;
            }
            else{
                nodeptr->right = lastA->right;
                lastA->right = nodeptr;
                lastA = nodeptr;
            }
        }

        if( c=='T' ){
            if(lastT == nullptr){
                lastT = nodeptr;
                nodeptr->right = firstNode;
                firstNode = nodeptr;
            }
            else{
                nodeptr->right = lastT->right;
                lastT->right = nodeptr;
                lastT = nodeptr;
            }
        }

        if( c=='O' ){
            if(lastO == nullptr){
                lastO = nodeptr;
                nodeptr->right = firstNode;
                firstNode = nodeptr;
            }
            else{
                nodeptr->right = lastO->right;
                lastO->right = nodeptr;
                lastO = nodeptr;
            }
        }

        if( c=='N' ){
            if(lastN == nullptr){
                lastN = nodeptr;
                nodeptr->right = firstNode;
                firstNode = nodeptr;
            }
            else{
                nodeptr->right = lastN->right;
                lastN->right = nodeptr;
                lastN = nodeptr;
            }
        }
    }

    void print_DNA(){
        Node* nodeptr = firstNode;

        //TO REMOVE
        //printf("\nANSWER: \n");

        while( nodeptr != nullptr ){
            printf("%c", nodeptr->ch);
            nodeptr = nodeptr->right;
        }
        printf("\n");

        //TO REMOVE
        //printf("\n");
    }
};

//TAAATTTTATTT
//AAAATTTTTTTT
//

void test_case(){
    string a;
    cin >> a;

    DNA* testDNA = new DNA();
    for(char ch:a){
        testDNA->appendGene(ch);
    }
    testDNA->print_DNA();
    delete(testDNA);
}

int main(){
    int t;
    scanf("%d", &t);

    for(int i=0; i<t; ++i)
        test_case();

    return 0;
}
