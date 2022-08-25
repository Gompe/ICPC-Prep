#include<iostream>
#include<algorithm>
#include<vector>
#include<mem.h>

using namespace std;

const int nmax = 2*1e5 + 100;
const long long INF = 1e11;

long long n;
vector< vector<long long> > adj;

long long end0, end1;
long long minout;

long long mexp[nmax];
long long dim[nmax];
long long to_go[nmax];

vector< long long > min_list;
vector< long long > sec_min_list;
vector<long long> par;

void build(long long s){

    long long p = par[s];

    long long min_cl = INF;
    long long sec_min_cl = INF;

    long long size_cl = 1;

    for(long long t: adj[s]){
        if(t==p)
            continue;

        size_cl += dim[t];
        if( min(t, min_list[t]) < min_cl ){
            swap(min_cl, sec_min_cl);
            min_cl = min(t, min_list[t]);
            to_go[s] = t;
        }
        else if( min(t, min_list[t]) < sec_min_cl ){
            sec_min_cl = min(t, min_list[t]);
        }

    }

    min_list[s] = min_cl;
    sec_min_list[s] = sec_min_cl;

    dim[s] = size_cl;
}

void clustering(){

    //build dfs order
    vector<bool> visited;
    visited.assign(n, false);
    visited[0] = true;

    vector<long long> dfs;
    dfs.push_back(0);

    par.clear();
    par.resize(n);
    par[0] = -1;

    int it = 0;
    while(it<n){
        long long v = dfs[it];
        for(long long x: adj[v]){
            if( !visited[x] ){
                visited[x] = true;
                par[x] = v;
                dfs.push_back(x);
            }
        }
        ++it;
    }

    reverse(dfs.begin(), dfs.end());

    for(long long s: dfs)
        build(s);

}

void mexbuild(long long v){

    if(v == 0){
        for(long long x: adj[0])
            mexp[0] += dim[x]*(n-1-dim[x]);
        mexp[0] = mexp[0]>>1;
        mexp[0] += n-1;

        end0 = to_go[0];
        end1 = 0;

        dim[0] = 1;
        min_list[0] = INF;
        sec_min_list[0] = INF;

        for(long long x: adj[0]){
            if( x==end0 )
                continue;
            dim[0] += dim[x];
            if( min_list[0] > min(x, min_list[x]) ){
                to_go[0] = x;
                sec_min_list[0] = min_list[0];
                min_list[0] = min(x, min_list[x]);
            }
            else
                sec_min_list[0] = min(sec_min_list[0], min(x, min_list[x]));
        }

        minout = sec_min_list[0];
        return;
    }

    if( minout<=v ){
        mexp[v] = 0;
        return;
    }

    if(end0!=v && min_list[end1]<min_list[end0])
        swap(end1, end0);

    while( end0 != v){
        minout = min(minout, sec_min_list[end0]);
        end0 = to_go[end0];
    }

    mexp[v] = dim[end0]*dim[end1];
}

void resizing(){

    adj.clear();
    adj.resize(n);

    min_list.clear(); sec_min_list.clear();
    min_list.assign(n, INF);
    sec_min_list.assign(n, INF);

    memset(to_go, 0, sizeof(to_go));
    memset(mexp, 0, sizeof(mexp));
    memset(dim, 0, sizeof(dim));

    minout = INF;
}

void read(){

    scanf("%lld", &n);
    resizing();

    for(int i=0; i<n-1; ++i){
        long long u, v;
        scanf("%lld %lld", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

}

void test_case(){
    read();
    clustering();

    for(long long it=0; it<n; ++it)
        mexbuild(it);

    long long last = (long long) n*(n-1)/2;

    for(int i=0; i<=n; ++i){
        printf("%lld ", last-mexp[i]);
        last = mexp[i];
    }
    printf("\n");
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        test_case();
    }
    return 0;
}
