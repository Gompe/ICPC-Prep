#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1610;

int len_dictionary;
int len_message;

string message;
vector<string> words;

int dp[MAXN];

int DP(int x){

    if(dp[x]!=-1){
        return dp[x];
    }

    if(x >= len_message){
        return 0;
    }

    // delete the character
    int best = 1+DP(x+1);

    // try to find a word
    for(auto w:words){

        if(w[0] != message[x]){
            continue;
        }

        int cost = 0;
        int num_filled = 1;

        int pos;
        for(pos=x+1;
        (pos+w.size()-num_filled <= len_message) && (num_filled < w.size()) && (cost<best);
        ++pos)
        {
            if(w[num_filled] == message[pos]){
                num_filled++;
            }
            else{
                cost++;
            }
        }

        if(num_filled == w.size()){
            cost += DP( pos );
            best = min(cost, best);
        }
    }
    dp[x] = best;
    return best;
}


int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(dp, -1, sizeof(dp));

    cin >> len_dictionary >> len_message;
    cin >> message;

    words.resize(len_dictionary);
    for(int ii=0; ii<len_dictionary; ii++) cin >> words[ii];

    cout << DP(0);

    return 0;
}
