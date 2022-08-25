#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    int a[n];
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    sort(a, a+n);
    int j=n-1;
    long long aout=0;
    for(int i=n-1; i>=0; i=i-2){
        if(i>0){
            aout += 2*a[j];
        }
        else{
            aout += a[j];
        }
        j = j-1;
    }
    cout << aout;
}
