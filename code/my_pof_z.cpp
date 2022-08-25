#include<iostream>
#include<stack>

using namespace std;

const int k_max = 1e6;
int k;

char s[k_max];

// z[i] = len of maximum prefix starting at i
int z[k_max];

int main(){
    scanf("%d", &k);
    scanf("%s", s);

    z[0] = k;
    int left=0, right=1;

    for(int i=1; i<k; ++i){
        z[i] = 0;
        if(i < right){
            // We can use that s[0...right-left] = s[left ... right]
            // to make the algorithm faster
            z[i] = min(z[i-left], right-i);
        }
        while( (i+z[i]<k) && (s[z[i]] == s[i+z[i]]) ) z[i]++;

        if( i+z[i] > right){
            left = i;
            right = i+z[i];
        }
    }

    long long sum_of_periods = 0;

    stack<int> max_periods;
    max_periods.push(0);

    for(int p=1; p<=k; ++p){

        max_periods.push(p-1);
        /* If a value n is in max_periods, then there is an m>=n
        such that s[0...n-1] = s[n...m] such that n is the maximal period
        of m.

        The condition z[n]+n >= p, subject to 2n>=p ensures that
        s[0...p-1] is a subword of s[0...n-1]s[0...n-1]
        */

        while( z[max_periods.top()] + max_periods.top() < p ) max_periods.pop();

        if( 2*max_periods.top()<p ){
            while( max_periods.size() > 1) max_periods.pop();
        }

        sum_of_periods += max_periods.top();
    }

    printf("%lld\n", sum_of_periods);

    return 0;
}
