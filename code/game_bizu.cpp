#include<bits/stdc++.h>
using namespace std;

int N1, N2;
int A1[2001], A2[2001];

long long dp[2001][2001];
long long PartialSums1[2001], PartialSums2[2001];

long long getSum(int x, int y, long long* a){
    if(x==0){
        return a[y];
    }
    else{
        return a[y]-a[x-1];
    }
}

long long getSum1(int x, int y){ return getSum(x,y,PartialSums1); }
long long getSum2(int x, int y){ return getSum(x,y,PartialSums2); }

long long min_of_3(long long a, long long b, long long c){
    return min(a, min(b,c));
}

long long iterative(){

    int sum, x, y;
    for(sum = N1+N2-2; sum >= 0; sum-=1){
        for(x = max(0, sum-N2+1) ; x<=min(N1-1, sum); ++x){
            y = sum-x;
            if( x == N1-1 ){
                dp[x][y] = A1[x]*getSum2(y, N2-1);
            }
            else if( y == N2-1 ){
                dp[x][y] = A2[y]*getSum1(x, N1-1);
            }
            else{
                dp[x][y] = A1[x]*A2[y];
                dp[x][y] += min_of_3(dp[x+1][y], dp[x][y+1], dp[x+1][y+1]);
            }
        }
    }

    return dp[0][0];
}

/*

long long DP(int x, int y){
    if(dp[x][y]!=-1) return dp[x][y];

    if(x == N1-1){
        //dp[x][y] = A1[x]*(A2[y]+...+A2[N2-1]);
        dp[x][y] = A1[x]*getSum2(y, N2-1);
        return dp[x][y];
    }

    else if(y == N2-1){
        //dp[x][y] = A2[y]*(A1[x]+...+A1[N1-1]);
        dp[x][y] = A2[y]*getSum1(x, N1-1);
        return dp[x][y];
    }

    else{
        dp[x][y] = A1[x]*A2[y];
        dp[x][y] += min_of_3(DP(x+1,y), DP(x,y+1), DP(x+1,y+1));
        return dp[x][y];
    }
}

*/

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N1 >> N2;

    long long prefix = 0;
    for(int i=0; i<N1; ++i){
        cin >> A1[i];
        A1[i]--;

        prefix += A1[i];
        PartialSums1[i] = prefix;
    }

    prefix = 0;
    for(int i=0; i<N2; ++i){
        cin >> A2[i];
        A2[i]--;

        prefix += A2[i];
        PartialSums2[i] = prefix;
    }

    cout << iterative();

    //memset(dp,-1,sizeof(dp));
    //cout << DP(0,0);

    return 0;
}
