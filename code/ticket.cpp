#include<iostream>
#include<algorithm>
#include<unordered_set>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int m,l,n;
    cin>>m>>l>>n;
    unordered_set<int> st;
    int x;
    for(int i=0; i<n; i++){
        cin>>x;
        st.insert(x);
    }

    int val[m+2] = { };
    int t[m+2] = { };
    for(int i=m-l+1; i>=1; i--){
        int val_on, val_off;

        if(st.count(i)){
            val_on = 2+val[i+l];
        }
        else{
            val_on = 1+val[i+l];
        }
        val_off = val[i+1];

        if(val_on > val_off){
            val[i] = val_on;
            t[i] = t[i+l] + 1;
        }
        else{
            val[i] = val_off;
            t[i] = t[i+1];
        }
    }
    cout << val[1] - max(t[1]-n, 0);
    return 0;
}
