#include<iostream>
#include<algorithm>
using namespace std;

int main()
{

    ios::sync_with_stdio(0);
    cin.tie(0);

    int m,l,n;
    cin>>m>>l>>n;
    int a[n];

    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    sort(a, a+n);

    int good = 0;
    int bad = 0;
    int last = 0;
    int st = 0;

    for(int i=1; i<=m; i++){
        while(st<n && a[st]<=last) st++;
        if(st == n) break;
        //a[st] > last, thus st can seat where they want

    }
}
