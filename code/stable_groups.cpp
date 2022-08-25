#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

long long min_groups(long long n,long long k,long long x,long long a[]){
    sort(a, a+n);

    long long numg = 1;
    long long c;
    vector< long long > cost;

    for( int i=0; i<n-1; i++ ){
        if( a[i+1] - a[i] > x){
            numg++;
            if( (a[i+1] - a[i])%x == 0){
                c = (a[i+1]-a[i])/x - 1;
            }
            else{
                c = (a[i+1] -a[i])/x;
            }
            cost.push_back(c);
        }
    }

    sort( cost.begin(), cost.end() );

    int i=0;
    while (k>0 & i<cost.size()){
        if( k >= cost[i] ){
            k -= cost[i];
            numg -= 1;
            i++;
        }
        else{
            break;
        }
    }

    return numg;
}

int main(){
    long long n, k, x;
    scanf("%lld %lld %lld", &n, &k, &x);

    long long a[n];
    for (int i=0; i<n; i++){
        scanf("%lld", &a[i]);
    }

    printf("%lld", min_groups(n, k, x, a) );

    return 0;
}
