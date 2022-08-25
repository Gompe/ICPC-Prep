#include<bits/stdc++.h>

using namespace std;

const long long len_max = 16*1000*1000;
long long L;
long long res = 0;

// pi[i] is the largest prefix ending at i
// pi[i]<=i for it to be useful
long long pi[len_max];
string lword;

vector<vector<int>> child;
vector<vector<string>> road_text;

inline void pi_compute(int i, int idx, string& txt){
    long long t = pi[i-1];
    while( t != 0 && lword[t] != txt[i-idx] ){
            t = pi[t-1];
    }
    if( lword[t] == txt[i-idx] )
        pi[i] = t+1;
    else
        pi[i] = 0;
}

void word_count(int v, int idx){
    for(int i=0; i<child[v].size(); ++i){
        for(int j=idx; j<idx+road_text[v][i].size(); ++j){
            pi_compute(j, idx, road_text[v][i]);
            if( pi[j] == L ) res++;
        }
        word_count(child[v][i], idx+road_text[v][i].size());
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    child.resize(N);
    road_text.resize(N);

    int a, b;
    string s;
    for(int i=0; i<N-1; ++i){
        cin >> a >> b;
        cin >> s;
        child[a].push_back(b);
        road_text[a].push_back(s);
    }

    cin >> lword;
    L = lword.size();
    lword+="#";

    pi[0] = 0;
    for(int i=1; i<=L; ++i)
        pi_compute(i, 0, lword);

    word_count(0, L+1);
    cout << res;

    return 0;
}

