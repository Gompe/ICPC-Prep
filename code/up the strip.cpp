#include<iostream>

using namespace std;

long long dp[4*1000*1000+10] = {};

int main(){
    long long n,m;
    scanf("%lld %lld", &n, &m);

    dp[1] = 1;
    dp[2] = 2;

    for(long long k=2; k<=n; ++k){
        if(k!=2)
            dp[k] = (dp[k]+2*dp[k-1]+1)%m;
        for(long long d=2; d*k<=n; ++d){
            dp[d*k] = (dp[d*k]+dp[k]-dp[k-1])%m;
            if(dp[d*k]<0)
                dp[d*k] = (dp[d*k]+m)%m;
            }
    }

    printf("%lld\n", dp[n]);
    return 0;
}
