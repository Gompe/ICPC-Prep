#include<bits/stdc++.h>
using namespace std;

#define BIG_SIZE 70
#define SMALL_SIZE 22

#define DEBUG false
#define RUN false

#define TEST_SPEED false

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

int SOLVE(){
    memset(dp, -1, sizeof(dp));
    memset(done, false, sizeof(done));
    return solve(0,0,0);
}

int conditioned_LCS(){

    const string& S = X;
    const string& T = Y;
    const string& P = Z;

    memset(dp, -1, sizeof(dp));
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
            for(z = min(k-1,min (iS,iT)); z>=0; z-=1){
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

void random_string(string& str, bool big){
    str = "";
    if(big){
        for(int i=0; i<BIG_SIZE; ++i)
            str += char('a'+rand()%2);
    }
    else{
        for(int i=0; i<SMALL_SIZE; ++i)
            str += char('a'+rand()%2);
    }
}

int main(){

    srand( time(0) );

#if TEST_SPEED

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    ios::sync_with_stdio(0);
    cin.tie(0);

    random_string(X,1); random_string(Y,1); random_string(Z,0);
    n = X.size(); m=Y.size(); k=Z.size();

    cout << conditioned_LCS() << "\n";

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;

#endif // TEST_SPEED

    ios::sync_with_stdio(0);
    cin.tie(0);

#if RUN
    cin>>X;
    cin>>Y;
    cin>>Z;

    m = X.size(); n = Y.size(); k = Z.size();

    cout << conditioned_LCS() <<endl;

    while(1){}

#endif // RUN

    int tests;
    cout << "NUM TESTS:"<<endl;
    cin >> tests;
    cout << endl;

    for(int i=0; i<tests; ++i){
        random_string(X,1);
        random_string(Y,1);
        random_string(Z,0);

        cout <<"=================================================\n";
        cout <<X<<endl;
        cout <<Y<<endl;
        cout <<Z<<endl;

        m = X.size();
        n = Y.size();
        k = Z.size();

        int outcome1 = SOLVE();
#if DEBUG
        cout << "FIRST RUN DONE"<<endl;
#endif // DEBUG

        int outcome2 = conditioned_LCS();

#if DEBUG
        cout << "SECOND RUN DONE"<<endl;
#endif // DEBUG

        if(outcome1==outcome2){
            cout << "SUCCESS:\n";
            if(outcome1==-1)
                cout << "NO SOLUTION \n";
            else
                cout << outcome1 << endl;
        }
        else{
            cout << "FAILURE\n:";
            cout << outcome1 << " ... " << outcome2 <<endl;
        }
    }

    return 0;
}
