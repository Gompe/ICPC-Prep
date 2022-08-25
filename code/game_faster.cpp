#include<bits/stdc++.h>
#include<chrono>

using namespace std;

const int MAXN = 2010;

long long dp[MAXN][MAXN];

long long arr1[MAXN], arr2[MAXN];
long long prefix_sum1[MAXN], prefix_sum2[MAXN];


long long best_so_far1[MAXN], best_so_far2[MAXN];

int N1, N2;

/* Efficient partial sums */

inline long long get_sum1(int r){
    return prefix_sum1[r];
}

inline long long get_sum1(int l, int r){
    if(l==0) return get_sum1(r);
    return prefix_sum1[r]-prefix_sum1[l-1];
}

inline long long get_sum2(int r){
    return prefix_sum2[r];
}

inline long long get_sum2(int l, int r){
    if(l==0) return get_sum2(r);
    return prefix_sum2[r]-prefix_sum2[l-1];
}

/* ====================== */

inline void update(long long& best, long long cost){
    if(best==-1 || best>cost)
        best = cost;
}


long long directMinCost(){

    for(int sum=0; sum<=N1+N2-2; sum++){
        for(int i=0; i<=max(sum, N1-1); ++i){

            int j = sum-i;
            if(i==0 || j==0){
                long long T1 = get_sum1(i), T2 = get_sum2(j);
                dp[i][j] = (T1-(i+1))*(T2-(j+1));
                continue;
            }

            dp[i][j] = min(best_so_far1[i-1],
                           best_so_far2[j-1]);

            for(int j0=0; j0<j; ++j0)
                update(best,
                       minCost(i-1,j0)+(arr1[i]-1)*(get_sum2(j0+1,j)-(j-j0))
                       );

            for(int i0=0; i0<i; ++i0)
                update(best,
                       minCost(i0,j-1)+(get_sum1(i0+1,i)-(i-i0))*(arr2[j]-1)
                       );

            dp[i][j] = best;

        }
    }
}

long long minCost(int i, int j){

    if(dp[i][j] != -1) return dp[i][j];

    if(i==0 || j==0){
        long long T1 = get_sum1(i), T2 = get_sum2(j);
        dp[i][j] = (T1-(i+1))*(T2-(j+1));
        return dp[i][j];
    }

    long long best = -1;

    for(int j0=0; j0<j; ++j0)
        update(best,
               minCost(i-1,j0)+(arr1[i]-1)*(get_sum2(j0+1,j)-(j-j0))
               );

    for(int i0=0; i0<i; ++i0)
        update(best,
               minCost(i0,j-1)+(get_sum1(i0+1,i)-(i-i0))*(arr2[j]-1)
               );

    dp[i][j] = best;
    return dp[i][j];
}
