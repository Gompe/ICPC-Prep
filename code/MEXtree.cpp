#include<iostream>
#include<algorithm>
#include<vector>
#include<mem.h>

using namespace std;

const int nmax = 2*1e5 + 100;
const long long INF = 1e11;

struct Cluster{
    int s, t;
    long long clmin;
    long long clsize;

    Cluster(int xs, int xt, long long xclmin, long long xclsize){
        s = xs;
        t = xt;
        clmin = xclmin;
        clsize = xclsize;
    }
};

int n;
vector< vector<int> > adj;

long long end0, end1;
long long min0, min1;

long long minout = INF;
long long mexp[nmax];
long long dim[nmax];

vector< vector<Cluster> > g;
vector<int> pt;

pair<long long, long long> clustering(int s, int p){
    long long minx = s;
    long long sizex = 1;

    for(int index=0; index<adj[s].size(); ++index){

        int t = adj[s][index];
        if(t==p)
            continue;

        pair<long long, long long> cpair = clustering(t, s);
        g[s].push_back( Cluster(s, t, cpair.first, cpair.second) );

        if(cpair.first < minx)
            pt[s] = index;

        minx = min(minx, cpair.first);
        sizex += cpair.second;
    }

    dim[s] = sizex;
    if(s==0)
        dim[0] -= g[0][pt[0]].clsize;

    return make_pair(minx, sizex);
}

void resizing(){
    adj.clear(); g.clear(); pt.clear();
    adj.resize(n); g.resize(n); pt.resize(n);

    memset(mexp, 0, sizeof(mexp));
    memset(dim, 0, sizeof(dim));

    minout = INF;
}

void read(){
    scanf("%d", &n);
    resizing();

    for(int i=0; i<n-1; ++i){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void mexbuild(int v){

    if(v==n){
        return;
    }

    if(v==0){
        long long mex0 = 0;
        for(auto cl: g[0])
            mex0 += cl.clsize*(n-1-cl.clsize);
        mex0 = mex0>>1;
        mex0 += n-1;
        mexp[0] = mex0;

        end0 = 0;
        end1 = 0;

        min0 = 1;
        min1 = INF;

        //computing min1
        for(int i=0; i<g[0].size(); ++i){
            if(i != pt[0])
                min1 = min( min1, g[0][i].clmin );
        }

        return mexbuild(1);
    }

    //printf("v=%d e0=%d e1=%d m0=%lld m1=%lld\n",v, end0, end1, min0, min1);

    if(minout <= v){
        mexp[v] = 0;
        return mexbuild(v+1);
    }

    if(min1 < min0){
        swap(end0, end1);
        swap(min0, min1);
    } // min0 = v

    while(end0 != v){

        if(end0 == 0 && min0 == 1){
            for(int it=0; it<g[0].size(); ++it){
                if(it == pt[0] || g[0][it].clmin == min1)
                    continue;
                minout = min( minout, (long long) g[end0][it].clmin );
            }
            end0 = g[end0][pt[end0]].t;
        }
        else if(end0 == 0 && min0 != 1){
            for(int it=0; it<g[0].size(); ++it){
                if( g[0][it].clmin == min0 ){
                    end0 = g[end0][it].t;
                    break;
                }
            }
        }
        else{
            for(int it=0; it<g[end0].size(); ++it){
                if(it == pt[end0])
                    continue;
                minout = min( minout, (long long) g[end0][it].clmin );
            }
            end0 = g[end0][pt[end0]].t;
        }
        // Be careful to see if this is the end of the path
        if(g[end0].size()==0)
            min0 = INF;
        else
            min0 = g[end0][pt[end0]].clmin;
    }

    // Now we build mexp[v]
    mexp[v] = dim[end0]*dim[end1];
    return mexbuild(v+1);
}

void test_case(){
    read();
    clustering(0, -1);

    mexbuild(0);
    long long last = (long long) n*(n-1)/2;

    /*
    printf("MAXP: \n");
    for(int i=0; i<n; ++i){
        printf("%lld ", mexp[i]);
    }
    printf("\n");
    */

    for(int i=0; i<=n; ++i){
        printf("%lld ", last-mexp[i]);
        last = mexp[i];
    }
    printf("\n");
    //printf("NEXT TEST\n");
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        test_case();
    }
    return 0;
}
