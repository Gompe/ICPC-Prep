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
vector<vector<string*>> road_text;

void pi_compute(int i){
    long long t = pi[i-1];
    while( t != 0 && lword[t] != lword[i] ){
            t = pi[t-1];
    }
    if( lword[t] == lword[i] )
        pi[i] = t+1;
    else
        pi[i] = 0;
}

void word_count(int v){
    long long idx = lword.size();
    for(int i=0; i<child[v].size(); ++i){
        lword += *road_text[v][i];
        //cout << "lword == " << lword << "\n";
        for(int i=idx; i< lword.size(); ++i){
            pi_compute(i);
            if( pi[i] == L ) res++;
        }
        word_count(child[v][i]);
        lword.erase(idx);
    }
}

int main(){
    int N;
    scanf("%d", &N);

    child.resize(N);
    road_text.resize(N);

    int a, b;
    string s[N-1];
    for(int i=0; i<N-1; ++i){
        scanf("%d %d", &a, &b);
        cin >> s[i];
        child[a].push_back(b);
        road_text[a].push_back(&s[i]);
    }

    cin >> lword;
    L = lword.size();
    lword+="#";

    pi[0] = 0;
    for(int i=1; i<=L; ++i)
        pi_compute(i);

    word_count(0);
    printf("%lld\n", res);

    return 0;
}

