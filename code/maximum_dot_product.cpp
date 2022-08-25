#include <iostream>
#include <algorithm>

using namespace std;

#define NAX 5010

int n;
long long a[NAX];
long long b[NAX];
long long p[NAX];
long long STD = 0;
long long MAX = 0;

void product_table(){

    for(int i=0; i<n; ++i)
        p[i] = a[i]*b[i];
}

void point_inversion(int i){
    int l = i-1, r=i+1;
    long long current = STD;
    while(l>=0 & r<n){
        current += a[r]*b[l] - p[l];
        current += a[l]*b[r] - p[r];
        MAX = max( MAX, current );
        ++r;
        --l;
    }
}

void segment_inversion(int i){
    int l = i, r=i+1;
    long long current = STD;
    while(l>=0 & r<n){
        current += a[r]*b[l] - p[l];
        current += a[l]*b[r] - p[r];
        MAX = max( MAX, current );
        ++r;
        --l;
    }
}

void find_best(){
    STD = 0;
    for(int i=0; i<n; ++i)
        STD += p[i];
    MAX = STD;
    for(int i=0; i<n; ++i)
        point_inversion(i);
    for(int i=0; i<n-1; ++i)
        segment_inversion(i);
}

int main(){
    scanf("%d", &n);
    for(int i=0; i<n; ++i)
        scanf("%lld", &a[i]);
    for(int i=0; i<n; ++i)
        scanf("%lld", &b[i]);
    product_table();
    find_best();
    printf("%lld\n", MAX);
    return 0;
}


