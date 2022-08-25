#include<bits/stdc++.h>
using namespace std;



int main()
{
    int n;
    cin>>n;
    int cnt = 0;
    int m = 1;
    int s = 1;
    while(s<=n){
        if((n-s)%m == 0) cnt++;
        m++;
        s+=m;
    }
    cout<<cnt;
}
