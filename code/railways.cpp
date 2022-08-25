#include<bits/stdc++.h>
using namespace std;

const int INF = 1000*1000*100;
const int MAXN = 60010;

int t[4*MAXN];
int lazy[4*MAXN];

void push(int v) {
    t[v*2] += lazy[v];
    lazy[v*2] += lazy[v];

    t[v*2+1] += lazy[v];
    lazy[v*2+1] += lazy[v];

    lazy[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, int addend) {
    if (l > r)
        return;
    if (l == tl && tr == r) {
        t[v] += addend;
        lazy[v] += addend;
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), addend);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

int query(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return -INF;
    if (l <= tl && tr <= r)
        return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return max(query(v*2, tl, tm, l, min(r, tm)),
               query(v*2+1, tm+1, tr, max(l, tm+1), r));
}


int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c, s, r;
    cin >> c >> s >> r;

    for(int i=0; i<r; ++i){
        int o,d,n;
        cin >> o >> d >> n;

        if( n + query(1, 1, c, o, d-1) <= s ){
            cout << "T\n";
            update(1, 1, c, o, d-1, n);
        }
        else{
            cout << "N\n";
        }
    }

    return 0;
}
