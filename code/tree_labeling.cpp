#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

#define debug true

struct Node{
    int label;
    vector<Node*> neighbors;
    vector<bool> subset;

    Node(int l){
        label = l;
        subset.resize(26);
    }

    void fill_subset(string& s){
        if(s[0] == '$')
            return;
        for(auto ch:s)
            subset[ch-'A'] = true;
    }

    void add_neighbor(Node* node_ptr){
        neighbors.push_back(node_ptr);
    }
};

void debug_info(vector<Node*>& n);

int main(){
    int N, L;
    scanf("%d %d", &N, &L);

    vector<Node*> nodes;
    nodes.resize(N+1);
    for(int i=1; i<=N; ++i)
        nodes[i] = new Node(i);

    int x, y;
    for(int i=0; i<N-1; ++i){
        scanf("%d %d", &x, &y);
        nodes[x]->add_neighbor(nodes[y]);
        nodes[y]->add_neighbor(nodes[x]);
    }

    string subset_labels;
    for(int i=0; i<L; ++i){
        scanf("%d", &x);
        cin >> subset_labels;
        nodes[x]->fill_subset(subset_labels);
    }

    if(debug)
        debug_info(nodes);

    return 0;
}

void debug_info(vector<Node*>& n){
    printf("DEBUG:\n");
    for(auto x: n){
        printf("Node %d\n", x->label);
        printf("Neighbors: ");
        for(auto u: x->neighbors)
            printf("%d ", u->label);
        printf("Vector: ");
        for(auto u: x->subset)
            printf("%d", u ? 1:0);
    }
}
