#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

int MAXnum = 0;
int LIM = 0;

struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

unordered_map<vector<int>,bool,VectorHasher> gCache;

bool update(int a,int b,int c,int n,int val){
    vector<int> v{a,b,c,n};
    gCache[v] = val;
    return val;
}

bool gSearch(int a,int b,int c,int n){
    vector<int> key{a, b, c, n};
    return ( gCache.find(key) != gCache.end() );
}

int refreshMax(int a, int b, int c){
    int m = max(max(a,b), c);
    return m;
}

bool done(int a,int b,int c,int n){

    int numMax = refreshMax(a,b,c);

    if( gSearch(a,b,c,n) ){
        vector<int> v{a,b,c,n};
        return gCache[v];
    }

    if( n==1 ){
        if( b==c ){
            return update(a,b,c,n,true);
        }
        else{
            return update(a,b,c,n,false);
        }
    }

    if( n==2 && a==c){
        return update(a,b,c,n,true);
    }

    if( n==3 && a==b){
        return update(a,b,c,n,true);
    }

    if( done(a,b,c,n-1) ){
        return update(a,b,c,n,true);
    }

    // More complex cases
    if( n%3==1 && a==numMax){
        //A plays
        int a0 = max(b,c) - min(b,c);
        if( b==c || done(a0,b,c,n-1) ){
            return update(a,b,c,n,true);
        }
    }

    if( n%3==2 && b==numMax){
        //B plays
        int b0 = max(a,c) - min(a,c);
        if( a==c || done(a,b0,c,n-1) ){
            return update(a,b,c,n,true);
        }
    }

    if( n%3==0 && c==numMax){
        //C plays
        int c0 = max(a,b) - min(a,b);
        if( a==b || done(a,b,c0,n-1) ){
            return update(a,b,c,n,true);
        }
    }
    return update(a,b,c,n,false);
}

int query(int a, int b, int c){
    int i=1;
    while(!done(a,b,c,i)){
        i++;
    }
    return i;
}

void test(int N, int M, vector< array<int,3> > *pcases, int *p){
    for(int i=1; i < M; i++){
        if( query(M, i, M-i) == N){
            pcases->push_back( array<int, 3>{M, i, M-i} );
            (*p)++;
        }
        if( query(i, M, M-i) == N){
            pcases->push_back( array<int, 3>{i, M, M-i} );
            (*p)++;
        }
        if( query(i, M-i, M) == N){
            pcases->push_back( array<int, 3>{i, M-i, M} );
            (*p)++;
        }
    }
}

void printQuery(int *p, vector< array<int, 3> > *pcases){
    sort(pcases->begin(), pcases->end());
    printf("%d \n", *p);
    for(auto t:*pcases){
        printf("%d %d %d \n", t[0], t[1], t[2]);
    }
}

int main(){

    while(true){
        int N, M;
        cin >> N >> M;
        LIM = 2*M;
        if(N==-1 && M==-1)
            break;
        int p = 0;
        vector< array<int, 3> > pcases;
        test(N, M, &pcases, &p);
        printQuery(&p, &pcases);
    }

    return 0;
}
