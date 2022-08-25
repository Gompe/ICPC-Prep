#include<bits/stdc++.h>
using namespace std;

namespace uf{

/**
From uf.cpp file.
*/

const int nmax = 1e5+10;

// should be init such that rep[n] = n
int rep[nmax];

// should be init to 1
int uf_pre_size[nmax];

inline void adjust(int a){

    if(rep[a]==a) return;

    int p = a;
    stack<int> path;

    while(rep[p]!=p){
        path.push(p);
        p = rep[p];
    }

    while(!path.empty()){
        rep[path.top()] = p;
        path.pop();
    }
}

inline void adjust(int a, int b){
    adjust(a);
    adjust(b);
}

inline void uf_merge(int a, int b){

    adjust(a,b);

    a = rep[a];
    b = rep[b];

    if(uf_pre_size[a]<uf_pre_size[b]) swap(a,b);

    uf_pre_size[a] += uf_pre_size[b];
    rep[b] = a;

}

inline bool uf_same(int a, int b){

    adjust(a,b);

    return rep[a] == rep[b];
}

inline int uf_size(int a){
    adjust(a);
    uf_pre_size[a] = uf_pre_size[rep[a]];
    return uf_pre_size[a];
}

}



using namespace uf;
typedef p2i3 pair< pair<int, int>, int >;

vector<vector<int>> rooted_tree;
int mex;

void tarjan_dfs( vector<p2i3>& queries, int v ){

}

vector<int> tarjan_LCA( vector<p2i3>& queries ){
    mex = 0;
    tarjan_dfs(queries, 0);
}

int main(){

}
