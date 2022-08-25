#include <iostream>
#include <algorithm>

using namespace std;

long long m = 1000000000;

bool dp[130][130][130] = { };
long long cache[130][130][130] = { };

void sort_triplet(int& c1, int& c2, int& c3){
    int a1, a2, a3;
    a1 = min( {c1, c2, c3} );
    a3 = max( {c1, c2, c3} );
    a2 = c1+c2+c3 - a1- a3;

    c1 = a1, c2 = a2, c3 = a3;
}

long long solve( int n, int c1, int c2, int c3, int *s ){

    sort_triplet(c1, c2, c3);

    if( dp[c1][c2][c3] )
        return cache[c1][c2][c3];

    long long aout = 0;
    for( int r1=0; r1 <= min(s[n], c1); r1++ ){
        for( int r2 = max(s[n] - r1 - c3, 0) ; r2 <= min(s[n]-r1, c2); r2++ ){
            int r3 = s[n] - r2 - r1;

            if( n==0 )
                aout ++;

            else
                aout = ( aout + solve(n-1, c1-r1, c2-r2, c3-r3, s) ) % m;
        }
    }

    dp[c1][c2][c3] = true;
    cache[c1][c2][c3] = aout;

    return aout;
}

int main(){
    int n, c1, c2, c3;
    scanf("%d %d %d %d", &n, &c1, &c2, &c3);

    int s[n];
    long long sum = 0;

    for( int i=0; i<n; i++ ){
        scanf("%d", &s[i]);
        sum += s[i];
    }

    if( c1+c2+c3 != sum ){
        printf("%d", 0);
        return 0;
    }

    printf( "%d", solve(n-1, c1, c2, c3, s) );
    return 0;
}
