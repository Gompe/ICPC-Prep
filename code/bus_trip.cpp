#include<bits/stdc++.h>
using namespace std;


const int INF = 1000*1000*100;
const int MAXN = 10010;

int t[4*MAXN];
int lazy[4*MAXN];

// Parameters
int K,N,C;

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

long long solve(vector<pair<pair<int,int>, int>>& trip){

    memset(t, 0, sizeof(t));
    memset(lazy, 0, sizeof(lazy));

    long long res = 0;
    for(auto p : trip){
        int s = -p.first.second,
            e = p.first.first,
            m = p.second;

        int taken = query(1, 1, N, s, e-1);
        res += min(m, C-taken);
        update(1, 1, N, s, e-1, min(m,C-taken));
    }

    return res;
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> K >> N >> C;

    vector< pair< pair<int,int>, int > > trip_east, trip_west;
    int s,e,m;
    for(int i=0; i<K; ++i){
        cin >> s >> e >> m;
        if(s<e){
            trip_east.push_back( {{e,-s},m} );
        } else{
            s = N+1-s;
            e = N+1-e;
            trip_west.push_back( {{e,-s},m} );
        }
    }

    sort(trip_east.begin(), trip_east.end());
    sort(trip_west.begin(), trip_west.end());

    long long res = 0;
    res += solve(trip_east);
    res += solve(trip_west);

    cout << res;

    return 0;

}


/*
    int N = 10;

    while(1){
        int qtype;

        cout << "NEW QUERY: ";
        cin >> qtype;
        cout << endl;

        if(qtype == 1){
            int l, r, addend;
            cin >> l >> r >> addend;
            update(1, 1, N, l, r, addend);
            cout << endl;
            cout << "update completed" << endl;
        }
        else if(qtype == 2){
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, N, l, r) << endl;
        }
        else{
            return 0;
        }
    }
*/
