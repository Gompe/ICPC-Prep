#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

#define NAX 100010

long long l[NAX];
long long r[NAX];

vector<vector<int>> edges;

pair<long long, long long> partial_best(int v, int par){
    long long av=0, bv=0;
    for( auto u: edges[v] ){
        if(u==par)
            continue;
        pair<long long, long long> p = partial_best(u, v);
        long long au=p.first, bu=p.second;
        av+=max(abs(l[v]-l[u])+au, abs(l[v]-r[u])+bu);
        bv+=max(abs(r[v]-l[u])+au, abs(r[v]-r[u])+bu);
    }
    return make_pair(av, bv);
}

void test_case(){
    int n;
    scanf("%d", &n);

    for(int i=1; i<=n; i++){
        scanf("%lld %lld", &l[i], &r[i]);
    }

    edges.clear();
    edges.resize(n+1);

    for(int i=1; i<n; ++i){
        int u, v;
        scanf("%d %d", &u, &v);
        if(u>v)
            swap(u,v);
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    pair<long long, long long> p = partial_best(1, 0);
    long long answer = max(p.first, p.second);
    printf("%lld\n", answer);
    return;
}


int main(){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        test_case();
    }
    return 0;

}
