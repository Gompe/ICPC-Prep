#include<bits/stdc++.h>

using namespace std;

struct road{
    int d;
    string s;

    road(int d1, string s1){
       d=d1; s=s1;
    }
};

const long long len_max = 16*1000*1000;
long long L;
long long res = 0;

// pi[i] is the largest prefix ending at i
// pi[i]<=i for it to be useful
long long pi[len_max];
string special_word;

vector< vector<road> > child_roads;

void word_count(int v, string partial_word){
    long long idx = partial_word.size();
    for(auto r: child_roads[v]){
        string new_partial_word = partial_word + r.s;
        cout << "lword == " << new_partial_word << "\n";
        for(int i=idx; i<new_partial_word.size(); ++i){
            long long t = pi[i-1];
            while( t != 0 && new_partial_word[t] != new_partial_word[i] )
                t = pi[t-1];

            if( new_partial_word[t] == new_partial_word[i] )
                pi[i] = t+1;
            else
                pi[i] = 0;

            if( pi[i] == L ) res++;
        }
        word_count( r.d, new_partial_word );
    }
}

int main(){
    int N;
    scanf("%d", &N);

    child_roads.resize(N);

    for(int i=0; i<N-1; ++i){
        int a, b;
        string s;

        scanf("%d %d", &a, &b);
        cin >> s;

        road r = road(b, s);
        child_roads[a].push_back(r);
    }

    cin >> special_word;
    L = special_word.size();

    pi[0] = 0;
    for(int i=1; i<L; ++i){
        long long t = pi[i-1];
        while( t!=0 && special_word[t] != special_word[i] )
            t = pi[t-1];

        if( special_word[t] == special_word[i])
            pi[i] = t+1;
        else
            pi[i] = 0;
    }
    pi[L] = 0;

    word_count(0, special_word+"#");

    printf("%lld\n", res);

    return 0;
}
