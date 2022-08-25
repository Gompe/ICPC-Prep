#include<bits/stdc++.h>
using namespace std;

vector<int> weights;
vector<long long> C;
int K;

struct Totoro{
    vector<long long> features;

    Totoro(const vector<long long>& FEATURES){
        assert( FEATURES.size() == K );
        features = FEATURES;
    }
};

long long eval(const Totoro& a){

    assert(weights.size()==K);
    assert(C.size()==K);
    assert( (a.features).size() == K );

    long long res = 0;
    for(int i=0; i<K; ++i){
        res += (weights[i]*C[i]*a.features[i]);
    }
    return res;
}

bool operator< (const Totoro& a, const Totoro& b){
    return eval(a)<eval(b);
}

long long friendliness(const Totoro& a, const Totoro& b){

    assert( (a.features).size() == K);

    long long res = 0;
    for(int i=0; i<K-1; ++i){
        res += C[i]*abs(a.features[i]-b.features[i]);
    }
    res -= C[K-1]*abs(a.features[K-1]-b.features[K-1]);
    return res;
}

void get_extremes(vector<Totoro>& V, vector<Totoro>& record, int s){

    if(s == K-1){
        weights.push_back(1);

        sort(V.begin(), V.end());

        weights.pop_back();

        // get largest and smallest
        record.push_back(V[0]);
        record.push_back(V[V.size()-1]);

        return;
    }

    weights.push_back(1);
    get_extremes(V,record,s+1);
    weights.pop_back();

    weights.push_back(-1);
    get_extremes(V,record, s+1);
    weights.pop_back();

    return;
}

int main(){

    long long N;
    scanf("%lld %lld", &N, &K);

    C.resize(K);
    for(int i=0; i<K; ++i) scanf("%lld", &C[i]);

    vector<Totoro> V;
    for(int i=0; i<N; ++i){
        vector<long long> features;
        features.resize(K);

        for(int j=0; j<K; ++j) scanf("%lld", &features[j]);

        V.push_back(Totoro(features));
    }

    vector<Totoro> to_check;
    get_extremes(V, to_check, 0);

    long long max_friendliness=0;
    for(int i=0; i<to_check.size(); ++i){
        for(int j=i+1; j<to_check.size(); ++j){
            max_friendliness = max(max_friendliness,
                                friendliness(to_check[i],to_check[j]));
        }
    }

    printf("%lld\n", max_friendliness);

    return 0;
}



