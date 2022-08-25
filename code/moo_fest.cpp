#include<bits/stdc++.h>
using namespace std;

#define DEBUG false

/*
10
1 100
2 2
3 3
4 45
5 15
6 6
7 72
8 8
9 9
10 10

*/

struct FenwickTree {
    /**
    Struct code from
    https://cp-algorithms.com/data_structures/fenwick.html
    */
    vector<long long> bit;  // binary indexed tree
    long long n;

    FenwickTree(long long n) {
        this->n = n;
        bit.assign(n, 0);
    }

    long long sum(long long r) {
        long long ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    void add(long long idx, long long delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};


int main(){

#if DEBUG
    int xx = 20000*20000;
    xx +=15 ;
    printf("%d", xx);
#endif // DEBUG

    long long N;
    scanf("%lld", &N);

    vector< pair< pair<long long, long long>, long long> > cow(N);

    long long volume, x;
    for(int i=0; i<N; ++i){
        scanf("%lld %lld", &volume, &x);
        cow[i].first.first = x;
        cow[i].first.second = volume;
    }

    // sort by x coordinate
    sort(cow.begin(), cow.end());

    // The cow now knows its position relative to the other cows
    for(int i=0; i<N; ++i) cow[i].second = i;


#if DEBUG
    printf("=============================================\n");
    for(int i=0; i<N; ++i)
        printf("%d %d %d \n", cow[i].first.first, cow[i].first.second, cow[i].second);
#endif // DEBUG

    // Swap volume and x-position
    for(int i=0; i<N; ++i) swap(cow[i].first.first, cow[i].first.second);

    // sort by volume
    sort(cow.begin(), cow.end());

#if DEBUG
    printf("=============================================\n");
    for(int i=0; i<N; ++i)
        printf("%d %d %d \n", cow[i].first.first, cow[i].first.second, cow[i].second);
#endif // DEBUG

    FenwickTree xTree(N);
    FenwickTree posTree(N);

    long long total_x = 0,
              before,
              pos;

    long long cost = 0;

    for(int i=0; i<N; ++i){
        pos = posTree.sum(cow[i].second);
        before = xTree.sum(cow[i].second);

        cost += ((2*pos-i)*cow[i].first.second-2*before+total_x)*cow[i].first.first;

        posTree.add(cow[i].second, 1);
        xTree.add(cow[i].second, cow[i].first.second);
        total_x += cow[i].first.second;
    }

    printf("%lld\n", cost);

    return 0;
}
