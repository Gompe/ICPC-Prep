#include <bits/stdc++.h>
using namespace std;

int dp[510][510][510];
string S, T, P;

int conditioned_LCS(){

    int m = S.size();
    int n = T.size();
    int k = P.size();

    memset(dp[k], 0, sizeof(dp[k]));

    // variables
    int iS, iT, z, val;
    bool match;

    for(int sum = m+n-2; sum>=0; sum-=1){
        for(iS=max(0, sum-(n-1)); iS<=min(sum, m-1); iS+=1){

            iT = sum-iS;
            match = (S[iS]==T[iT]);
            // Query to S[is:], T[iT:], P[k:]=""
            val = max(dp[k][iS+1][iT], dp[k][iS][iT+1]);
            if(match) val = max(val, 1+dp[k][iS+1][iT+1]);
            dp[k][iS][iT] = val;

            // Queries to S[iS:], T[iT:], P[z:]
            for(z=min(k-1, min(iS, iT)); z>=0; z-=1){
                val = max(dp[z][iS+1][iT], dp[z][iS][iT+1]);
                if(match && dp[z][iS+1][iT+1]!=-1) val = max(val, 1+dp[z][iS+1][iT+1]);
                if(match && S[iS]==P[z] && dp[z+1][iS+1][iT+1]!=-1) val = max(val, 1+dp[z+1][iS+1][iT+1]);

                dp[z][iS][iT] = val;

                if(val==-1) break;
            }
        }
    }
    return dp[0][0][0];
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    memset(dp, -1, sizeof(dp));

    cin>>S;
    cin>>T;
    cin>>P;

    int outcome = conditioned_LCS();

    if(outcome == -1){
        cout<<"NO SOLUTION";
    }
    else{
        cout<<outcome;
    }

    return 0;
}
