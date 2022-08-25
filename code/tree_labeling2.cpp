#include <bits/stdc++.h>

using namespace std;

// Graph and leafs
int N, L;
vector<vector<int>> G;
vector<int> leafs;
vector<vector<int>> bitLabels;

long long totalWeight(int labels[]){
    long long weight = 0;
    for(int v=0; v<N; ++v){
        for(auto u:G[v]){
            if( labels[v] != labels[u] ) weight++;
        }
    }
    return weight/2;
}

long long minTotalWeight(vector<int>& leafLabels){
    int labels[N];
    memset(labels, -1, sizeof(labels));

    stack<int> s;
    for(int i=0; i<L; ++i){
        labels[leafs[i]] = leafLabels[i]; // Labels are 0 or 1
        // push to stack all neighbors of leafs
        for(auto v:G[leafs[i]])
            s.push(v);
    }

    while( !s.empty() ){

        int v = s.top();
        s.pop();

        if( labels[v]!=-1 )
            continue;

        int c0 = 0;
        int c1 = 0;
        int cTotal = G[v].size();

        for(auto u: G[v]){
            if(labels[u] == 0) c0+=1;
            if(labels[u] == 1) c1+=1;
        }

        if( 2*c0>=cTotal ) labels[v] = 0;
        if( 2*c1>=cTotal ) labels[v] = 1;

        if( labels[v]!=-1 ){
            for(auto u:G[v])
                s.push(u);
        }
    }

    for(int i=0; i<N; ++i){
        if( labels[i] == -1){
            int visited[N] = {};
            vector<int> connectedComponent;
            stack<int> toProcess;
            connectedComponent.push_back(i);
            toProcess.push(i);
            int v;
            int x0 = 0, x1 = 0;
            while( !toProcess.empty() ){
                v = toProcess.top();
                toProcess.pop();
                for(auto u: G[v]){
                    if(labels[u]==1){
                        x1++;
                        continue;
                    }
                    if(labels[u]==0){
                        x0++;
                        continue;
                    }
                    if(!visited[u]){
                        connectedComponent.push_back(u);
                        toProcess.push(u);
                        visited[u] = 1;
                    }
                }
            }
            int color = (x0>=x1) ? 0:1;
            for(auto u: connectedComponent)
                labels[u] = color;
        }
    }

    return totalWeight(labels);
}

void fill_label(string& s){
    int sz = bitLabels[0].size();
    for(auto ch:s){
        if(ch!='$')
            bitLabels[ch-'A'].push_back(1);
    }
    for(int i=0; i<26; ++i){
        if(bitLabels[i].size()==sz)
            bitLabels[i].push_back(0);
    }
}

int main(){
    int x, y;

    scanf("%d %d", &N, &L);
    G.resize(N);
    bitLabels.resize(26);

    for(int i=0; i<N-1; ++i){
        scanf("%d %d", &x, &y);
        G[x-1].push_back(y-1);
        G[y-1].push_back(x-1);
    }

    string leafLabel;
    for(int i=0; i<L; ++i){
        scanf("%d", &x);
        cin >> leafLabel;
        leafs.push_back(x-1);
        fill_label(leafLabel);
    }

    long long ans = 0;
    for(int i=0; i<26; ++i){
        ans += minTotalWeight(bitLabels[i]);
    }

    printf("%lld\n", ans);
    return 0;
}
