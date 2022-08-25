#include<bits/stdc++.h>

using namespace std;

struct edge{
    int a, b;
    long double d;
};

bool operator< (edge e1, edge e2){
    return e1.d < e2.d;
}

int P, S;
vector<int> uf;
vector<int> uf_size;
vector<edge> M;

void uf_set_class(int v){
    vector<int> v_list;
    while( v!= uf[v] ){
        v_list.push_back(v);
        v = uf[v];
    }
    for(auto x: v_list)
        uf[x] = v;

}

void uf_merge(int v, int u){

    uf_set_class(v);
    uf_set_class(u);

    v = uf[v];
    u = uf[u];

    if( uf_size[v]>uf_size[u] )
        swap(u,v);

    uf[v] = u;
    uf_size[u] += uf_size[v];
}

long double my_MST(){
    sort(M.begin(), M.end());
    int connected_comps = P;
    long double D = 0;
    int idx = 0;

    while( connected_comps > max(S,1) ){

        int a = M[idx].a, b = M[idx].b;
        D = M[idx].d;
        idx++;

        uf_set_class(a);
        uf_set_class(b);

        if( uf[a]==uf[b] )
            continue;

        uf_merge(a, b);
        connected_comps--;
    }

    return D;
}

void clear_vectors(){
    uf.clear();
    uf_size.clear();
    M.clear();
}

int main(){
    int N;
    scanf("%d", &N);

    while(N--){

        scanf("%d %d", &S, &P);

        clear_vectors();

        int x[P], y[P];
        for(int i=0; i<P; ++i){
            scanf("%d %d", &x[i], &y[i]);
            uf.push_back(i);
            uf_size.push_back(1);
        }

        for(int i=0; i<P; ++i){
            for(int j=i+1; j<P; ++j){
                edge e;
                e.a = i, e.b = j;
                e.d = sqrt( (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) );
                M.push_back(e);
            }
        }
        printf("%.2Lf\n", my_MST());
    }
    return 0;
}

