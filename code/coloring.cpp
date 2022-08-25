#include <bits/stdc++.h>

using namespace std;

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

const int nmax = 10+1e6;
const int mod = 998244353;

int n,m;

unordered_map< pair<int, int>, int, hash_pair > Table;

int num_col_0[nmax];
int num_col_1[nmax];
int num_row_0[nmax];
int num_row_1[nmax];

int rows_type_0 = 0;
int rows_type_1 = 0;
int cols_type_0 = 0;
int cols_type_1 = 0;

int chess_sim_0 = 0;
int chess_sim_1 = 0;

int wrong_rows = 0;
int wrong_cols = 0;

long long bpow[nmax];

long long binpow(int e){
    if(bpow[e])
        return bpow[e];

    long long tmp = binpow(e/2);
    tmp = tmp*tmp%mod;

    if(e%2==0){
        bpow[e] = (tmp+mod)%mod;
        return bpow[e];
    }
    else{
        bpow[e] = ((2*tmp%mod)+mod)%mod;
        return bpow[e];
    }
}

void delete_entry(int x, int y){
    if( Table.count({x,y}) == 0 )
        return;
    int previous = Table[{x,y}];
    Table.erase({x,y});

    if( (y+previous)%2==0){
        num_row_0[x]--;
        if(num_row_0[x] == 0){
            rows_type_0--;
            if(num_row_1[x]>0)
                wrong_rows--;
        }
    }
    else{
        num_row_1[x]--;
        if(num_row_1[x]==0){
            rows_type_1--;
            if(num_row_0[x]>0)
                wrong_rows--;
        }
    }

    if( (x+previous)%2==0){
        num_col_0[y]--;
        if(num_col_0[y]==0){
            cols_type_0--;
            if(num_col_1[y]>0)
                wrong_cols--;
        }
    }
    else{
        num_col_1[y]--;
        if(num_col_1[y]==0){
            cols_type_1--;
            if(num_col_0[y]>0)
                wrong_cols--;
        }
    }

    if( (x+y+previous)%2 == 0)
        chess_sim_0--;
    else
        chess_sim_1--;

    return;
}

void process_query(int x, int y, int t){
    if(t==-1){
        delete_entry(x,y);
        return;
    }
    if( Table.count({x,y})==1 && Table[{x,y}]==t )
        return;

    if( Table.count({x,y})==1 && Table[{x,y}]!=t )
        delete_entry(x,y);

    Table[{x,y}] = t;
    if( (y+t)%2==0){
        if(num_row_0[x]==0){
            rows_type_0++;
            if(num_row_1[x] > 0)
                wrong_rows++;
        }
        num_row_0[x]++;
    }
    else{
        if(num_row_1[x]==0){
            rows_type_1++;
            if(num_row_0[x] > 0)
                wrong_rows++;
        }
        num_row_1[x]++;
    }
    if( (x+t)%2==0){
        if(num_col_0[y]==0){
            cols_type_0++;
            if(num_col_1[y] > 0)
                wrong_cols++;
        }
        num_col_0[y]++;
    }
    else{
        if(num_col_1[y]==0){
            cols_type_1++;
            if(num_col_0[y] > 0)
                wrong_cols++;
        }
        num_col_1[y]++;
    }

    if( (x+y+t)%2==0)
        chess_sim_0++;
    else
        chess_sim_1++;

    return;
}

void compute_quantity(){
    long long R_ALT = 0;
    long long C_ALT = 0;

    if( wrong_rows==0 ){
        R_ALT = binpow(n-rows_type_0-rows_type_1);
    }

    if( wrong_cols==0 ){
        C_ALT = binpow(m-cols_type_0-cols_type_1);
    }

    long long TOTAL = (R_ALT+C_ALT) % mod;

    if(chess_sim_0==0)
        TOTAL=(TOTAL-1)%mod;
    if(chess_sim_1==0)
        TOTAL=(TOTAL-1)%mod;

    TOTAL = (TOTAL + mod)%mod;
    printf("%lld\n", TOTAL);
}

int main(){
    bpow[0] = 1;
    bpow[1] = 2;

    int k;
    scanf("%d %d %d", &n, &m, &k);

    int x,y,t;
    while(k--){
        scanf("%d %d %d", &x, &y, &t);
        process_query(x-1,y-1,t);
        compute_quantity();
    }
    return 0;
}
