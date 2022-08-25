#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

void answer(bool c){
    if(c)
        printf("Alice\n");
    else
        printf("Bob\n");
}

pair< bool, int > is_power2(long long n){
    int exponent = 0;
    while( n>1 ){
        if( n%2 != 0){
            return make_pair(false, 0);
        }
        n = n/2;
        exponent++;
    }
    return make_pair( true, exponent );
}

void test_case(){
    long long n;
    scanf("%lld", &n);

    if( n%2 != 0 ){
        answer(false);
        return;
    }

    pair< bool, int> p = is_power2(n);

    if( !p.first ){
        answer(true);
        return;
    }

    if( p.second%2 == 0 ){
        answer(true);
        return;
    }

    answer(false);
    return;

}

int main(){
    int t;
    scanf("%d", &t);

    for( int i = 0; i<t; i++)
        test_case();
    return 0;
}
