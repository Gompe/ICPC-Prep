#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;


const long long NAX = 1000010;
long long d[NAX] = { }; // Number of divisors

long long m = 998244353;

void construct_divisors(){

    const int sr = (int) sqrt(NAX);

    for(int a=1; a<= sr; ++a){
        long long b = a;
        while( b<NAX ){
            ++d[b]; // a|b
            if( b > a*sr )
                ++d[b];
            b+=a;
        }
    }
}

long long compute( long long n ){

    long long b = 1;
    for(int i=2; i<=n; i++)
        b = (2*b+d[i]-d[i-1])%m;
    return b;
}

int main(){
    construct_divisors();

    long long n;
    scanf("%lld", &n);
    printf("%lld\n", compute(n));

    return 0;
}
