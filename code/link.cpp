#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000000
const int inf = 1000000000;

int n, k;
int link[MAXN];
int connected[MAXN];

vector< vector<int> > predecessors;
vector< vector<int> > Cycles;

int result = 0;

void find_cicles() {

    vector<int> time_visited(n, 0);
    int time = 0;

    for(int i = 0; i < n; ++i){

        if(time_visited[i]) continue;
        int a, b;

        ++time;
        time_visited[i] = time;

        for(a = link[i]; !time_visited[a]; a = link[a]){
            ++time;
            time_visited[a] = time;
        }

        if( time_visited[a] < time_visited[i] ) continue;

        Cycles.push_back( vector<int> (1,a) );

        for(b = link[a]; b != a; b = link[b]){
            Cycles.back().push_back(b);
        }
    }
}

int rec( int a ) {
    int range = 0;

    for(auto t : predecessors[a]){
        range = max(range, rec(t));
    }

    if(a == 0) range = k+1;

    connected[a] = 1;
    if( range == 0 ) {
        range = k;
        ++result;
    }

    return range-1;
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;

    predecessors.resize(n);

    for( int i = 0; i < n; ++i ) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        link[a] = b;
        predecessors[b].push_back(a);
    }

    find_cicles();

    for( vector<int>& cycle : Cycles){

        int m = cycle.size();

        int range = 0;
        int prev = cycle[m-1];

        for(int i = 0; i < 2*m; ++i) {
            int curr = cycle[i%m];

            if(i<m){
                for(auto pred : predecessors[curr]){
                    // Makes sure that all trees rooted at the cycle
                    // are connected in the end.

                    if(pred == prev) continue;
                    range = max(range, rec( pred ));
                }

                if(curr == 0) range = k+1;
            }
            if(range > 0) connected[curr] = 1;
            --range;

            prev = curr;
        }


        // connecting the remaining nodes
        // of the cycle


        // distance to the next_ node that is not connected
        vector<int> next(m, inf);

        prev = 0;
        for(int i = 2*m-1; i >= 0; --i) {
            int curr = i%m;

            next[curr] = next[prev]+1;
            if( !connected[cycle[curr]] ) next[curr] = 0;

            prev = curr;
        }


        if( next[0] >= inf ) continue;

        int best = inf;
        for(int start = 0, next_start; start < min(k, m); start = next_start){

            int cost = 0;

            int i = start + next[start];
            next_start = start + 1;

            while(i - start < m) {
                // Greedy: connects the origin to i
                ++cost;
                i += k;
                i += next[i%m];
            }
            best = min(best, cost);
        }
        result += best;
    }

    cout << result;

    return 0;
}
