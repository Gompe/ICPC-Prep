#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>


using namespace std;

long long min_cost(int n, vector< pair<long long, long long> >& p){
    sort( p.begin(), p.end() ); //sort in increasing order of b[i]

    int left = 0;
    int right = p.size() - 1;
    long long b = 0;
    long long cost = 0;

    while( right >= left){
        if( b >= p[left].first ){
            cost += p[left].second;
            b += p[left].second;
            left += 1;
        }
        else{
            long long delta = p[left].first - b;

            if( delta >= p[right].second ){
                cost += 2*p[right].second;
                b += p[right].second;
                right -= 1;
            }
            else{
                cost += 2*delta;
                p[right].second -= delta;
                b += delta;
            }
        }
    }

    return cost;
}

int main(){
    int n;
    scanf("%d", &n);
    vector< pair<long long, long long> > p;

    for (int i=0; i<n; i++){
        p.push_back( make_pair(0, 0) );
        scanf("%lld %lld", &p[i].second, &p[i].first); // p[i] = (b[i], a[i])
    }

    printf( "%lld", min_cost(n, p) );

    return 0;
}
