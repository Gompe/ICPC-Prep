#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

#define INF 10000

int dp[510][510][2][2];
bool done[510][510][2][2];

int get_dp(int a, int b, int mid, int wait){
    if(b==0)
        wait = 0;
    return dp[a][b][mid][wait];
}

void compute(int a, int b, int mid, int wait){
    if( b==0 )
        wait = 0;

    if( done[a][b][mid][wait] )
        return;

    if( wait==1 ){
        compute(a,b,mid,0);
        done[a][b][mid][wait] = true;
        dp[a][b][mid][wait] = max( -dp[a][b][mid][0], dp[a][b][mid][0] );
        return;
    }

    //printf("Values: a=%d, b=%d, mid=%d \n", a, b, mid);
    // wait is 0 from now on

    /*
    if( b==0 & mid==1 ){
        if( a%2==0 ){
            done[a][b][mid][0] = true;
            dp[a][b][mid][0] = 0;
        }
        else{
            done[a][b][mid][0] = true;
            dp[a][b][mid][0] = -2;
        }
        return;
    }
    */

    int best = -INF;
    if(a>0){
        compute(a-1, b+1, mid, 1);
        //best = max(best, -1-dp[a-1][b+1][mid][1]);
        best = max(best, -1-get_dp(a-1,b+1,mid,1));
    }
    if(b>0){
        compute(a, b-1, mid, 1);
        //best = max(best, -1-dp[a][b-1][mid][1]);
        best = max(best, -1-get_dp(a,b-1,mid,1) );
    }
    if(mid==0){
        compute(a, b, 1, 1);
        //best = max(best, -1-dp[a][b][1][1]);
        best = max(best, -1-get_dp(a,b,1,1));
    }

    done[a][b][mid][0] = true;
    dp[a][b][mid][0] = best;
    return;
}

void print_winner(int a, int b, int mid, int wait){
    int outcome = get_dp(a,b,mid,wait);
    if( outcome==0 )
        printf("DRAW\n");
    if( outcome<0 )
        printf("BOB\n");
    if( outcome>0 )
        printf("ALICE\n");
    return;
}

void test_case(){

    int n;
    scanf("%d", &n);
    string s;
    cin >> s;

    int mid, a=0, b=0;

    if(n%2==1 & s[n/2]=='0')
        mid = 0;
    else
        mid = 1;

    for(int i=0; i<n/2; i++){
        if(s[i]==s[n-1-i] & s[i]=='0')
            ++a;
        else if(s[i]!=s[n-1-i])
            ++b;
    }

    //cout << "STRING: " << s <<"\n";
    //printf("Values: a=%d, b=%d, mid=%d \n", a, b, mid);

    compute(a,b,mid,1);
    print_winner(a,b,mid,1);

    return;
}

int main(){
    done[0][0][0][0] = true;
    dp[0][0][0][0] = -1;

    done[0][0][1][0] = true;
    dp[0][0][1][0] = 0;

    int t;
    scanf("%d", &t);

    for(int i=0; i<t; i++)
        test_case();

    return 0;
}
