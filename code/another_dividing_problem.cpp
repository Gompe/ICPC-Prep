#include <bits/stdc++.h>

#define M 1000000000

using namespace std;

vector< long long > primes;

void find_primes(){
    primes.clear();
    primes.push_back(2);

    for( int n=3; n <= sqrt(M); n++){
        bool is_prime = true;
        for(auto p: primes){
            if( n%p == 0){
                is_prime = false;
                break;
            }
        }
        if(is_prime)
            primes.push_back(n);
    }
}

void answer(bool c){
    if(c)
        printf("YES\n");
    else
        printf("NO\n");
}

void test_case(long long a, long long b, long long k){

    /*
    if( a==b ){
        answer( false );
        return;
    }
    */

    if( k==1 ){
        answer( a!=b & (max(a,b)%min(a,b) == 0) );
        return;
    }

    long long ub = 0;
    long long a0, b0;
    int alpha, beta;

    a0 = 1, b0 = 1;

    for(auto p: primes){
        alpha = 0;
        beta = 0;
        long long powp = p;
        long long ra, rb;
        ra = a%p, rb = b%p;

        while( (ra == 0) || (rb == 0)  ){
            powp = p * powp;
            if( ra == 0 ){
                alpha++;
                a0 = a0*p;
                ra = a % powp;
            }
            if( rb == 0 ){
                beta++;
                b0 = b0*p;
                rb = b % powp;
            }
        }
        ub += alpha + beta;
    }

    if( a != a0 )
        ub += 1;
    if( b != b0 )
        ub += 1;

    answer( k<=ub );
    return;
}

int main(){
    find_primes();

    int t;
    scanf("%d", &t);
    long long a, b, k;

    for(int i=0; i<t; i++){
        scanf("%lld %lld %lld", &a,&b,&k);
        test_case(a,b,k);
    }

    return 0;
}
