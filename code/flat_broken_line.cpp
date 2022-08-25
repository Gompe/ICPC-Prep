#include<bits/stdc++.h>
using namespace std;

int n;
vector< pair<int,int> > Tpoints;
vector< int > sequence;

int lis(vector<int> const& a){
    // https://cp-algorithms.com/sequences/longest_increasing_subsequence.html

    int n = a.size();
    const int INF = 1e9;
    vector<int> d(n+1, INF);
    d[0] = -INF;

    for (int i = 0; i < n; i++) {
        int j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[j-1] < a[i] && a[i] < d[j])
            d[j] = a[i];
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        if (d[i] < INF)
            ans = i;
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    Tpoints.resize(n);
    sequence.resize(n);

    int x, y;
    for(int i=0; i<n; ++i){
        cin >> x >> y;
        Tpoints[i] = {y-x, -x-y};
    }

    sort(Tpoints.begin(), Tpoints.end());

    for(int i=0; i<n; ++i){
        sequence[i] = -Tpoints[i].second;
    }

    cout << lis(sequence);

    return 0;
}


