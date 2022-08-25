#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const long long NAX = 210;
const long long M = 1000000007;

int n;
int g[NAX][NAX];
vector<int> paths[NAX][NAX];
vector< vector <int> > adj;

long long f[NAX][NAX];

long long binexp(long long x, long long alpha){
    long long res = 1;
    while(alpha!=0){
        if(alpha%2==1){
            res = x*res%M;
            alpha -= 1;
        }
        else{
            x = x*x%M;
            alpha = alpha >> 1;
        }
    }
    return res;
}

long long inv(long long x){
    return binexp(x, M-2);
}

long long fracMod(long long x, long long d){
    return (x * inv(d))%M;
}

long long compute_f(long long l, long long r){
    if( l==0 )
        return 1;
    if( r==0 )
        return 0;
    if( f[l][r] != 0)
        return f[l][r];

    f[l][r] = fracMod( compute_f(l-1,r), 2 );
    f[l][r] = (f[l][r] + fracMod( compute_f(l, r-1), 2 ))%M;

    return f[l][r];
}

int build(int v, int p){
    int res = 1;
    for(int u:adj[v]){
        if(u==p)
            continue;
        g[v][u] = build(u, v);
        res += g[v][u];
    }
    if(p!=-1)
        g[v][p] = n-res;
    return res;
}

vector<int> path(int v, int u, int p){

    if( paths[v][u].size() > 0 && (v==u || paths[v][u][1]!=p))
        return paths[v][u];

    vector<int> res;
    res.push_back(v);

    if(v==u){
        paths[v][v] = res;
        return res;
    }

    for(int w:adj[v]){
        if(w==p)
            continue;

        vector<int> trial_path = path(w, u, v);
        if( trial_path[0] == -1)
            continue;

        for(int x: trial_path)
            res.push_back(x);
    }

    if(res.size()==1){
        res[0] = -1;
        return res;
    }

    paths[v][u] = res;

    reverse(res.begin(), res.end());
    paths[u][v] = res;

    return paths[v][u];
}

long long p_inversion(int v, int u){
    //assume v<u

    vector<int> walk = path(v, u, -1);

    long long res = fracMod(n-g[v][walk[1]],n);

    for(int x=1; x<walk.size()-1; ++x){
        int weight = fracMod(n-g[walk[x]][walk[x-1]]-g[walk[x]][walk[x+1]], n);
        res = (res + (weight*f[x][walk.size()-1-x])%M)%M;
    }
    return (1+M-res)%M;
}

int main(){

    compute_f(NAX-1, NAX-1);

    scanf("%d", &n);
    adj.resize(n+1);

    for(int i=0; i<n-1; ++i){
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    build(1, -1);

    long long res = 0;
    for(int i=1; i<=n; ++i){
        for(int j=i+1; j<=n; ++j){
            res = (res + p_inversion(i, j))%M;
            //printf("i,j = %d, %d 6res = %lld \n",i ,j, 6*res%M);
        }
    }

    printf("%lld\n", res);

    return 0;
}
