#include<bits/stdc++.h>
using namespace std;

const int MAXN = 510;
const int inf = 1000*1000*1000;

int n;

vector<int> children[MAXN];

int mother[MAXN];
int milk[MAXN];

int dp[MAXN][MAXN][2];
int size_subtree[MAXN];

void dfs(int x){

    /**

    dp[m1][links][b] =
        Maximum amount of milk that can be made.

        Given that only descendants of m1 can be used.

        Given that we have _links_ relations of
        mother-daugther

        if b == 0:
            m1 not included
        if b == 1:
            m1 included

    */

    for(auto y : children[x]){

        dfs(y);
        size_subtree[x] += (1 + size_subtree[y]);

        for(int j = size_subtree[x]; j>=0; --j){

            // We analyse j links in total
            // The maximum amount of links is the number of edges
            // in x's subtree

            for(int k=0; k<=j; ++k){

                // We assume that k of those links come
                // from y's subtree

                // best with x:
                if( k>=1 ){
                    dp[x][j][1] = max(dp[x][j][1], dp[x][j-k][1] + dp[y][k-1][1]);
                }

                dp[x][j][1] = max(dp[x][j][1], dp[x][j-k][1] + dp[y][k][0]);


                // best without x:
                dp[x][j][0] = max(dp[x][j][0],
                                  dp[x][j-k][0] + max(dp[y][k][0], dp[y][k][1]));

            }
        }
    }
}


int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int x;
    cin >> n >> x;

    for(int i=1; i<=n; ++i){
        int mil, mom;
        cin >> mil >> mom;

        milk[i] = mil;
        mother[i] = mom;

        children[mom].push_back(i);
    }

    for(int m=0; m<=n; ++m){

        dp[m][0][0] = 0;
        dp[m][0][1] = milk[m];

        for(int l=1; l<=n; ++l){
            dp[m][l][0] = dp[m][l][1] = -inf;
        }
    }

    size_subtree[0] = n;
    dfs(0);

    for(int i = n-1; i >= 0; --i){
        if(dp[0][i][0] >= x){
            cout << i;
            return 0;
        }
    }

    cout << -1;

    return 0;

}
