#include<bits/stdc++.h>
using namespace std;

#define DEBUG false

int N, T;

vector< bool > fail_move;

vector< pair<int,int> > arrows;
vector< int > S_match, T_match;

inline int other_match(int v, int t){
    if(t == arrows[v].first) return arrows[v].second;
    return arrows[v].first;
}

inline int make_match(int v, int t){

    int v1 = T_match[t];
    int t1 = S_match[v];

    S_match[v] = t;
    T_match[t] = v;

    if(v1 != -1) S_match[v1] = -1;
    if(t1 != -1) T_match[t1] = -1;

    return v1;
}

void perform_move(int v){

    int t = S_match[v];
    do{
        t = other_match(v,t);
        v = make_match(v,t);
    } while(v!=-1);
}

bool try_move(int v){

#if DEBUG
    cout << "enter try move "<<v << " " << S_match[v] << endl;

#endif // DEBUG

    if( fail_move[v] ){
#if DEBUG
    cout << "leave try move fail " << endl;
#endif // DEBUG
        return false;
    }

    vector<bool> visited;
    visited.resize(T);

    vector<int> path;
    path.push_back(v);

    int v0 = v;
    int t = S_match[v];

    while( !visited[t] ){

        visited[t] = true;

        t = other_match(v, t);
        v = T_match[t];

        if( v==-1 ){
            perform_move(v0);
#if DEBUG
    cout << "leave try move "<<v <<" " << t << endl;

#endif // DEBUG
            return true;
        }
        path.push_back(v);
    }

    for(auto u: path)
        fail_move[u] = true;

#if DEBUG
    cout << "leave try move "<<v << endl;

#endif // DEBUG

    return false;
}

bool simple_match(int v){
    int t1 = arrows[v].first, t2 = arrows[v].second;

    if(T_match[t1]==-1){
        make_match(v, t1);
        return true;
    }

    if(T_match[t2]==-1){
        make_match(v, t2);
        return true;
    }

    return false;
}

void append(int v){

#if DEBUG
    cout << "enter append " << v << endl;
#endif // DEBUG

    //try to add v to the matching
    if( simple_match(v) ) return;

    int t1 = arrows[v].first, t2 = arrows[v].second;

    if( try_move(T_match[t1]) ){
        make_match(v,t1);
        return;
    }

    if( try_move(T_match[t2]) ){
        make_match(v,t2);
        return;
    }
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> T;

    fail_move.resize(N);

    T_match.resize(T);
    fill(T_match.begin(), T_match.end(), -1);

    S_match.resize(N);
    fill(S_match.begin(), S_match.end(), -1);

    arrows.resize(N);
    for(int i=0; i<N; ++i){
        cin >> arrows[i].first >> arrows[i].second;
        arrows[i].first -= 1;
        arrows[i].second -= 1;
    }

    for(int i=0; i<N; ++i){
        append(i);
#if DEBUG
        cout << i << " appended to " << S_match[i] << endl;
#endif // DEBUG

    }

#if DEBUG
    cout << "Arrows" << endl;
    for(int i=0; i<N; ++i){
        cout << i << " " << arrows[i].first << " " <<arrows[i].second << endl;
    }
    cout << "End Arrows"<<endl;

    cout << "Match"<<endl;
    for(int i=0; i<N; ++i){
        cout << i << " " << S_match[i] << endl;
    }
    cout << "End Match"<<endl;
#endif // DEBUG

    int res = 0;
    for(int i=0; i<N; ++i){
        if(S_match[i] != -1) res++;
    }

    cout << res << "\n";

    return 0;
}
