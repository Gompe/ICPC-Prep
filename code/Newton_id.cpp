#include <iostream>
#include <algorithm>

using namespace std;

const int maxK = 210;
const long long M = 1000000007;
long long n;

long long bin[maxK][maxK];
long long P[maxK];
long long E[maxK];

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

long long frac(long long x, long long d){
    return (x * inv(d))%M;
}

long long binomial(int a, int b){

    if(b>a)
        return 0;

    if(b==0 || b==a)
        return 1;

    if(b>(a>>1))
        b = a-b;

    if(bin[a][b] != 0)
        return bin[a][b];

    bin[a][b] = frac(a, a-b)*binomial(a-1,b)%M;
    return bin[a][b];
}

long long power_sum(int k){
    if(k==0)
        return n;
    if(P[k]!=0)
        return P[k];

    long long res = binexp(n, k+1);
    for(int i=0; i<=k-1; ++i){
        res = (res - (binomial(k+1, i)*power_sum(i))%M)%M;
    }
    res = frac(res, k+1);
    res = (res%M + M)%M;
    P[k] = res;
    return res;
}

long long symmetric_sum(int k){
    if(k==0)
        return 1;
    if(E[k]!=0)
        return E[k];

    long long res = 0;
    for(int i=1; i<=k; ++i){
        int sign = (i%2==1) ? 1:-1;
        res = (res + (power_sum(i)*symmetric_sum(k-i)*sign)%M)%M;
    }
    res = frac(res, k);
    res = (res%M +M)%M;

    E[k] = res;
    return res;
}


int main(){
    int k;
    scanf("%lld %d", &n, &k);

    long long even=1;
    long long odd=0;

    for(int i=1; i<=k; ++i){
        if( i<n ){
            if(i%2==1)
                odd = (odd+symmetric_sum(i))%M;
            else
                even = (even+symmetric_sum(i))%M;
        }
        printf("%lld ", (i%2==1) ? odd:even );
    }

    return 0;
}
