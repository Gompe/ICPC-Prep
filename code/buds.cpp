#include<iostream>
#include<vector>
#include<stack>
#include<set>
#include<mem.h>
#include<queue>

using namespace std;

const int nmax = 2*1e5 + 100;
const int INF = 2*nmax;

int n;

vector<int> p;
vector<vector<int>> A;
queue<int> leaves;

void build(){
    p.clear();
    p.resize(n+1);
    p[1] = -1;

    stack<int> to;
    to.push(1);

    while(!to.empty()){
        int x = to.top(); to.pop();
        bool is_leave = true;

        for(auto y:A[x]){
            if(p[y]==0){
                is_leave = false;
                p[y] = x;
                to.push(y);
            }
        }
        if(is_leave && x!=1)
            leaves.push(x);
    }
}

void read_input(){
    scanf("%d", &n);
    A.clear();
    A.resize(n+1);

    int x,y;
    for(int i=0; i<n-1; ++i){
        scanf("%d %d",&x,&y);
        A[x].push_back(y);
        A[y].push_back(x);
    }
    build();
}

int answer(){
    bool condition = false;
    int num_buds = 0;

    vector<bool> inside;
    inside.resize(n+1);

    vector<int> parity;
    parity.resize(n+1);

    vector<int> distances;
    distances.assign(n+1, INF);

    queue<int> aux;
    while(!leaves.empty()){
        int leave = leaves.front(); leaves.pop();

        aux.push(leave);
        distances[leave] = 0;
    }

    while(!aux.empty()){
        int v = aux.front();
        aux.pop();
        if(v==1)
            continue;
        if(distances[p[v]] > 1+distances[v]){
            distances[p[v]] = 1+distances[v];
            if(!inside[p[v]]){
                aux.push(p[v]);
                inside[p[v]] = true;
            }
        }
    }

    for(int i=2; i<=n; ++i){
        parity[i] = (distances[i]%2==0) ? 0:1;
        if(p[i]==1 && parity[i]==0)
            condition = true;
        if(parity[i])
            num_buds++;
    }

    if(condition)
        return n-1-2*num_buds;
    else
        return n-2*num_buds;
}

void print_output(){
    printf("%d\n", answer());
}

int main(){
    int t;
    scanf("%d", &t);
    for(int i=0;i<t;++i){
        read_input();
        print_output();
    }
}

