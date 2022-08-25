#include<bits/stdc++.h>
using namespace std;

class Totoro{
public:

    Totoro(const vector<int>& features){
        assert(K == features.size());
        F = features;
    }

    vector<int> F; // features

    static int K; // num features

    static vector<int> C; // friendliness consts

    // weights is a vector of +1s and -1s
    static vector<int> weights; // for comparison

    long long eval() const{
        assert(K == weights.size());
        assert(K == F.size());
        assert(K == C.size());

        long long res = 0;

        for(int i=0; i<K; ++i){
            res += weights[i]*C[i]*F[i];
        }

        return res;
    }

    bool operator< (const Totoro& other) const{
        return (this->eval()) < (other.eval());
    }
};

vector<int> Totoro::weights;
vector<int> Totoro::C;
int Totoro::K;

long long friendliness(const Totoro& a, const Totoro& b){

    int K = Totoro::K;

    long long res=0;
    for(int i=0; i<K-1; ++i){
        res += Totoro::C[i]*abs(a.F[i]-b.F[i]);
    }
    res -= Totoro::C[K-1]*abs(a.F[K-1]-b.F[K-1]);

    return res;
}

void get_extremes(vector<Totoro>& V, vector<Totoro>& record, int s){

    if(s==Totoro::K - 1){
        Totoro::weights.push_back(1);

        sort(V.begin(), V.end());

        Totoro::weights.pop_back();

        // get largest and smallest
        record.push_back(V[0]);
        record.push_back(V[V.size()-1]);


        return;
    }

    Totoro::weights.push_back(1);
    get_extremes(V,record,s+1);
    Totoro::weights.pop_back();

    Totoro::weights.push_back(-1);
    get_extremes(V, record, s+1);
    Totoro::weights.pop_back();

    return;
}



int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N >> Totoro::K;

    Totoro::C.resize(Totoro::K);
    for(int i=0; i<Totoro::K; ++i){
        cin >> Totoro::C[i];
    }

    vector<Totoro> V;
    for(int i=0; i<N; ++i){
        vector<int> features;
        features.resize(Totoro::K);

        for(int j=0; j<Totoro::K; ++j)
            cin >> features[j];

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

    cout << max_friendliness << "\n";

    return 0;
}
