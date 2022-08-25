#include <iostream>
#include <algorithm>
#include <cstdio>
#include <set>

using namespace std;

int main(){
    long long n;
    scanf("%lld", &n);

    bool ok = false;

    long long p[n];
    pair<long long, long long> px[n];

    long long h;
    for(int i=0; i<n; ++i){
        long long a;
        scanf("%lld", &a);

        if(a==-1){
            ok = true;
            h=i;
            p[i] = -1;
            px[i] = make_pair(-1, i);
            continue;
        }

        if(ok){
            p[i] = a;
            px[i] = make_pair(a, i);
        }
        else{
            p[i] = 0;
            px[i] = make_pair(0, i);
        }
    }

    sort(px, px+n);
    set<long long> missing;

    for(int i=0; i<n; ++i)
        missing.insert(i);

    long long cost = 0;

    long long best = n-1;
    long long sz = n>>1;
    long long pos = n-1;

    while( best > h ){

        long long it = 1;
        cost += p[best];
        missing.erase(best);

        while(it<sz){
            if( !missing.count(px[pos].second) ){
                --pos;
                continue;
            }
            ++it;
            missing.erase(px[pos].second);
            --pos;
        }
        best = *(--missing.end());
        sz = sz>>1;
    }

    printf("%lld\n", cost);

    return 0;
}
