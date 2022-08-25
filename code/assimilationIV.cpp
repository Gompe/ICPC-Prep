#include <iostream>
#include <cmath>

using namespace std;

const long long mod = 998244353;

long long factorial(int n){
    long long aout = 1;
    for(int i=2; i<=n; ++i)
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

long long multinverse(long long x){
    return mod_pow(x, mod-2);
}

long long fraction_mod(long long x, long long y){
    return (x*multinverse(y))%mod;
}

int main(){

    int n, m;
    scanf("%d %d", &n, &m);

    long long d[n][m];
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j)
            scanf("%lld", &d[i][j]);

    long long E_num = 0;
    long long n_fact = factorial(n);

    for(int i=0; i<m; ++i){
        long long lb_dists[n+2] = { };
        for(int j=0; j<n; ++j)
            ++lb_dists[ d[j][i] ];

        long long num=1;
        for(int i=n+1; i>1; --i){ // used same i here lol
            num = (num*lb_dists[i])%mod;
            lb_dists[i-1] += (lb_dists[i]-1);
        }
        E_num = (E_num + n_fact - num)%mod;
    }

    // The Expected Value (mod) is E_num/n_fact
    printf("%lld\n", fraction_mod(E_num, n_fact));
    return 0;

}
