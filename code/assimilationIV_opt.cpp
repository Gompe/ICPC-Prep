#include <iostream>
#include <mem.h>

using namespace std;

const long long mod = 998244353;

int n, m;
long long n_fact;
long long lb_dists[50010][25]; // arr[m][n]

long long factorial(int x){
    long long aout = 1;
    for(int i=2; i<=x; ++i)
        aout = (aout*i)%mod;
    return aout;
}

long long mod_pow(long long x, long long alpha){
    if(alpha==0)
        return 1;
    if(alpha==1)
        return x%mod;
    if(alpha%2==0)
        return mod_pow( (x*x)%mod, alpha>>1);
    return (mod_pow( (x*x)%mod, alpha>>1 )*x)%mod;
}

long long fraction_mod(long long x, long long y){
    return (x*mod_pow(y, mod-2))%mod;
}

long long update(int i){
    long long num=1;
    for(int j=n+1; j>=2; --j){
            num = (num*lb_dists[i][j])%mod;
            if( num==0 )
                break;
            lb_dists[i][j-1] += (lb_dists[i][j]-1);
    }
    return (mod + ((n_fact-num)%mod))%mod;
}

int main(){

    scanf("%d %d", &n, &m);
    n_fact = factorial(n);

    int dist;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            scanf("%d", &dist);
            if(dist >= n+1)
                ++lb_dists[j][n+1];
            else if(dist >= 1)
                ++lb_dists[j][dist];
        }
    }

    long long E_num = 0;
    for(int i=0; i<m; ++i)
        E_num = (E_num + update(i))%mod;

    printf("%lld\n", fraction_mod(E_num, n_fact));
    return 0;
}

