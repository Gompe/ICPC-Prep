#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

#define debug false

vector< vector<int> > A; // edges
vector< vector<bool> > label; // labels
vector< bool > leaf;

void fill_label(string& s, int x){
    if(s[0] == '$')
        return;
    for(auto ch:s)
        label[x][ch-'A'] = true;
}

int compute_label(int vertex, int parent, int idx){
    if(leaf[vertex])
        return label[vertex][idx] ? 1:0;
    int ones = 0;
    int num_child = 0;
    for(auto u: A[vertex]){
        if(parent == u)
            continue;
        num_child++;
        ones += compute_label(u, vertex, idx);
    }
    if(2*ones >= num_child)
        label[vertex][idx] = true;
    return label[vertex][idx] ? 1:0;
}

void rectify(int vertex, int parent, int idx){
    if(leaf[vertex])
        return;
    int ones = 0;
    int deg = 0;
    for(auto u: A[vertex]){
        deg++;
        if(label[u][idx])
            ones++;
    }
    if(2*ones < deg)
        label[vertex][idx] = false;

    for(auto u: A[vertex]){
        if(parent==u)
            continue;
        rectify(u, vertex, idx);
    }
}

int hamming_distance(int x, int y){
    int result = 0;
    for(int b=0; b<26; ++b){
        if(label[x][b] != label[y][b])
            result++;
    }
    return result;
}

long long count_cost(int vertex, int parent){
    long long result = 0;
    for(auto u:A[vertex]){
        if(u==parent)
            continue;
        result+=count_cost(u, vertex);
        result+=hamming_distance(vertex, u);
    }
    return result;
}

int main(){
    int N, L;
    scanf("%d %d", &N, &L);

    A.resize(N+1);
    label.resize(N+1);
    leaf.resize(N+1);

    for(int i=1; i<=N; ++i)
        label[i].resize(26);

    int x, y;
    for(int i=0; i<N-1; ++i){
        scanf("%d %d", &x, &y);
        A[x].push_back(y);
        A[y].push_back(x);
    }

    string chars_label;
    for(int i=0; i<L; ++i){
        scanf("%d", &x);
        cin >> chars_label;

        leaf[x] = true;
        fill_label(chars_label, x);
    }

    int root = 1;
    while(leaf[root]){
        root++;
    } // root is a non-leaf vertex

    if(debug)
        printf("Root: %d\n", root);

    for(int i=0; i<26; ++i){
        compute_label(root, -1, i);
        rectify(root, -1, i);
    }

    printf("%lld\n", count_cost(root, -1));
    return 0;
}
