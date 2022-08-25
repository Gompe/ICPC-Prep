#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

int k;
long long pk;
string t;

long long v[1000000];

void build(long long n){
    if(2*n + 1 < pk){
        build( 2*n );
        build( 2*n + 1 );
    }
    else{
        v[2*n] = 1;
        v[2*n+1] = 1;
    }

    if(t[n] == '0')
        v[n] = v[2*n];
    if(t[n] == '1')
        v[n] = v[2*n+1];
    if(t[n] == '?')
        v[n] = v[2*n]+v[2*n+1];

}

void reverse_build(long long n){
    if(t[n] == '0')
        v[n] = v[2*n];
    if(t[n] == '1')
        v[n] = v[2*n+1];
    if(t[n] == '?')
        v[n] = v[2*n]+v[2*n+1];

    if( n>1 )
        reverse_build( (long long) n/2);
}

void rev(char &ch){
    if(ch=='?')
        return;
    if(ch=='1'){
        ch = '0';
        return;
    }
    ch = '1';
}

void query(){
    long long p;
    char c;
    scanf("%lld %c", &p, &c);

    p = pk - p;
    rev(c);

    t[p] = c;

    reverse_build(p);
    printf("%lld\n", v[1]);
    return;
}

int main(){

    scanf("%d", &k);
    pk = pow(2, k);

    string s;
    cin >> s;

    t.append(1, 'x');

    for(int i=2; i<=pk; i++){
        if(s[pk-i] == '1')
            t.append(1, '0');
        else if(s[pk-i] == '0')
            t.append(1, '1');
        else
            t.append(1, '?');
    }
    build(1);

    int q;
    scanf("%d", &q);

    for(int i=0; i<q; i++)
        query();

    return 0;
}
