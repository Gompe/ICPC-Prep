#include<bits/stdc++.h>
using namespace std;

string X, Y, Z;
int m, n, k;
int dp[510][510][510];
bool done[510][510][510];

int solve(int x, int y, int z){

    assert( z<=k );

    if(x>=m || y>=n)
        return (z!=k) ? -1:0;

    if(done[x][y][z] == true)
        return dp[x][y][z];

    int ans = (z!=k) ? -1:0;
    ans = max(ans, max(solve(x+1,y,z), solve(x,y+1,z)));

    if(X[x]==Y[y]){
        if(solve(x+1,y+1,z) != -1){
            ans = max(ans,1+solve(x+1,y+1,z));
        }
        if(X[x]==Z[z] && z!=k && solve(x+1,y+1,z+1)!=-1){
            ans = max(ans,1+solve(x+1,y+1,z+1));
        }
    }

    done[x][y][z] = true;
    dp[x][y][z] = ans;

    return ans;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    memset(dp, -1, sizeof(dp));
    memset(done, false, sizeof(done));

    cin >> X;
    cin >> Y;
    cin >> Z;

    m = X.size();
    n = Y.size();
    k = Z.size();

    int outcome = solve(0,0,0);

    if(outcome==-1){
        cout << "NO SOLUTION";
    }

    else{
        cout << outcome;
    }

    return 0;
}
