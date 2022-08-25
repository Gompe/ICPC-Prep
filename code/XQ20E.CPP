#include<bits/stdc++.h>
using namespace std;



int main()
{
    long long n;
    cin>>n;
    long long cnt = 0;
    long long m = 1;
    long long s = 1;
    while(s<=n){
        if((n-s)%m == 0) cnt++;
        m++;
        s+=m;
    }
    cout<<cnt;
}
