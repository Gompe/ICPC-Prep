#include<bits/stdc++.h>
#include<chrono>

using namespace std;

#define DEBUG true
#define RUN false

int N1, N2;
int A1[2001], A2[2001];

long long PartialSums1[2001], PartialSums2[2001];
long long dp[2001][2001];

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

/*

inline void update(long long& best, long long cost){
    if(best==-1 || best>cost)
        best = cost;
}

long long minCost(int i, int j){

    int *arr1 = A1, *arr2 = A2;

    if(dp[i][j] != -1) return dp[i][j];

    if(i==0 || j==0){
        long long T1 = getSum1(0,i), T2 = getSum2(0,j);
        dp[i][j] = (T1-(i+1))*(T2-(j+1));
        return dp[i][j];
    }

    long long best = -1;

    if( false && (arr1[i]>=arr1[i+1] || arr1[i]>arr1[i-1]) ){
        update(best,
               minCost(i-1,j-1)+(arr1[i]-1)*(arr2[j]-1)
               );

    }else{
        for(int j0=0; j0<j; ++j0)
            update(best,
                   minCost(i-1,j0)+(arr1[i]-1)*(getSum2(j0+1,j)-(j-j0))
                   );
    }

    if( false && (arr2[j]>=arr2[j+1] || arr2[j]>arr2[j-1])){
        update(best,
               minCost(i-1,j-1)+(arr1[i]-1)*(arr2[j]-1)
               );

    }else{
        for(int i0=0; i0<i; ++i0)
            update(best,
                   minCost(i0,j-1)+(getSum1(i0+1,i)-(i-i0))*(arr2[j]-1)
                   );
    }
    dp[i][j] = best;
    return dp[i][j];
}

*/

void randint(int& a){
    a = 1 + (rand()%1000);
    //a = 1000;
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //srand(time(0));
    srand(0);

    while(1){

    int N;
    cin >> N;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    N1 = N;
    N2 = N;

    long long prefix = 0;

    /*
    for(int i=0; i<N1; ++i){
        randint( A1[i] );
        prefix += A1[i];
        PartialSums1[i] = prefix;
    }

    prefix = 0;
    for(int j=0; j<N2; ++j){
        randint( A2[j] );
        prefix += A2[j];
        PartialSums2[j] = prefix;
    }

    memset(dp, -1, sizeof(dp));
    cout << "Result 1: " << minCost(N1-1, N2-1) << "\n";
    */

    prefix = 0;
    for(int i=0; i<N1; ++i){
        randint(A1[i]);

        A1[i]--;
        prefix += A1[i];
        PartialSums1[i] = prefix;
    }

    prefix = 0;
    for(int j=0; j<N2; ++j){
        randint(A2[j]);

        A2[j]--;
        prefix += A2[j];
        PartialSums2[j] = prefix;
    }

    //memset(dp, -1, sizeof(dp));
    //cout << "Result DP: " << DP(0,0) << "\n";
    cout << "Result Iterative: " << iterative() << "\n";


    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << endl;

    }

    return 0;

}
