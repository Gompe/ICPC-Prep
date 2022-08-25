#include<bits/stdc++.h>
using namespace std;

// 10^9+7 is prime

/*
Implement own +, -, *, /
*/

const int N = 60;
long long p;
long long dp[N][N];
long long factorial[N];
long long inv_factorial[N];

inline long long binexp(long long a, long long b){
    long long res = 1;
    while( b>0 ){
        if( b&1 ){
            res = (res*a)%p;
        }
        a = (a*a)%p;
        b >>= 1;
    }
    return res;
}

long long inverse_mod_p(long long a){
    return binexp(a, p-2);
}

void build_factorial(){
    factorial[0] = 1; inv_factorial[0] = 1;
    factorial[1] = 1; inv_factorial[1] = 1;
    for(int i=2; i<N; ++i){
        factorial[i] = (i*factorial[i-1])%p;
        inv_factorial[i] = inverse_mod_p(factorial[i]);
    }
}

inline long long binom(int n, int k){
    return (factorial[n]*inv_factorial[n-k]%p)*inv_factorial[k]%p;
}

long long DP(int n, int c){

    if(dp[n][c] != -1){
        return dp[n][c];
    }

    // base cases
    if( n==0 || c==0 || c>n ){
        dp[n][c] =0;
        return 0;
    }

    if(n==c){
        dp[n][c] = 1;
        return dp[n][c];
    }
    if(c==1){
        dp[n][c] = factorial[n-1];
        return dp[n][c];
    }

    // general formula
    long long val = 0;
    for(int k=0; k<=n-c; ++k){
        val = ( (binom(n-1,k)*DP(n-k-1, c-1)%p)*factorial[k]%p + val )%p;
    }
    dp[n][c] = val;
    return val;
}

long long polya(int n, int m){
    long long val = 0;
    for(int c=1; c<=n; ++c){
        val = ( DP(n,c)*binexp(m, c)%p + val )%p;
    }
    val = inv_factorial[n]*val %p;
    return val;
}

void DEBUG(){
    for(int i=1; i<55; ++i){
        if( factorial[i]<0 || factorial[i]>=p )
            printf("Wrong factorial: %d\n", i);
        if(inv_factorial[i]<0 || inv_factorial[i]>=p)
            printf("Wrong inv_factorial: %d\n", i);
        for(int j=1; j<1000; ++j){
            if( i>=j && (binom(i,j)<0 || binom(i,j)>=p ))
                printf("Wrong binom: %d %d\n", i, j);
            if( polya(i,j)<0 || polya(i,j)>=p )
                printf("Wrong polya!: %d %d\n", i ,j);
        }
        printf("%d done\n", i);
    }
}

int main(){
    int n, m;
    scanf("%d", &n);

    bool debug = false;
    if(n == 0){
        debug = true;
    }

    if(!debug){
        scanf("%d %lld", &m, &p);
    }
    else{
        n = 1;
        m = 1;
        p = -1;
    }

    if(p==-1){ p = 1000*1000*1000+7; }

    // dependencies
    memset(dp, -1, sizeof(dp));
    build_factorial();

    if(debug){

        for(int k=1; k<N; ++k){
            long long val = 0;
            for(int c=1; c<=k; ++c){
                val = (val+DP(k,c))%p;
            }
            printf("Expected: %lld Got: %lld\n", factorial[k], val);
        }

        //DEBUG();
    }

    printf("%lld\n", polya(n,m));
    return 0;
}
