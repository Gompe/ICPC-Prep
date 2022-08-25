#include<bits/stdc++.h>
using namespace std;

#define DEBUG true

// N <= 50,000
// Ne[v] = Neighbours of v
vector< vector<int> > Ne;

// Number of Vertices
int num_vertices;

// List of leaves
vector<int> L;
int num_leaves;

void minCostColoring(vector<int>& labels){

    stack<int> to_process;
    for(auto l: L){
        for(auto v : Ne[l])
            to_process.push(v);
    }

    // STEP 1
    while(!to_process.empty()){

        int v = to_process.top();
        to_process.pop();

        if(labels[v]!= -1) continue;

        long long n0 = 0, n1 = 0;
        for(auto u: Ne[v]){
            if(labels[u]==0) n0++;
            if(labels[u]==1) n1++;
        }

        if(2*n0 >= Ne[v].size()) labels[v] = 0;
        if(2*n1 >= Ne[v].size()) labels[v] = 1;

        if(labels[v]!=-1){
            for(auto u: Ne[v]){
                if(labels[u] == -1) to_process.push(u);
            }
        }
    }

    // STEP 2
    for(int v=0; v<num_vertices; ++v){

        if(labels[v] != -1) continue;

        vector<bool> visited(num_vertices);
        vector<int> component;
        stack<int> dfs;

        dfs.push(v);

        long long n0 = 0, n1 = 0;
        while( !dfs.empty() ){

            int u = dfs.top();
            dfs.pop();

            assert(labels[u]==-1);
            assert(!visited[u]);

            visited[u] = true;
            component.push_back(u);

            for(auto x : Ne[u]){

                if(labels[x] == -1 && !visited[x]){
                    dfs.push(x);
                }
                if(labels[x]==0) n0++;
                if(labels[x]==1) n1++;
            }
        }

        if( n0 >= n1 ){
            for(auto u: component)
                labels[u] = 0;
        }
        else{
            for(auto u: component)
                labels[u] = 1;
        }
    }
}

long long costColoring(const vector<int>& labels){
    long long cost = 0;
    for(int v=0; v<num_vertices; ++v){
        assert(labels[v]!=-1);
        for(auto u: Ne[v]){
            if(labels[v] != labels[u])
                cost++;
        }
    }
    assert(cost%2==0);
    return cost/2;
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> num_vertices >> num_leaves;
    Ne.resize(num_vertices);

    vector<vector<int>> char_labels(26);
    for(int i=0; i<26; ++i){
        char_labels[i].resize(num_vertices);
        fill(char_labels[i].begin(), char_labels[i].end(), -1);
    }

    int x,y;
    string leaf_label;

    for(int i=0; i<num_vertices-1; ++i){
        cin >> x >> y;
        // 0-indexed
        Ne[x-1].push_back(y-1);
        Ne[y-1].push_back(x-1);
    }

    for(int i=0; i<num_leaves; ++i){

        cin >> x;
        cin >> leaf_label;
        // push to the leaves list
        L.push_back(x-1);

        for(int j=0; j<26; ++j){
            char_labels[j][x-1] = 0;
        }
        for(char ch:leaf_label){
            if(ch == '$') break;
            char_labels[ch-'A'][x-1] = 1;
        }
    }

    long long result = 0;
    for(int i=0; i<26; ++i){
        minCostColoring(char_labels[i]);
        result += costColoring(char_labels[i]);
    }

    cout << result;

    return 0;
}
