#include<bits/stdc++.h>
using namespace std;


// limits 0<=A<=B<=2*1000*1000*1000
// All numbers < 2*10**9 can be written as
// b30 2**30 + b29 2**29 + ... + b0 2**0

int MAX_BITS = 30;

int N, P;
int K[101];

vector<vector< pair<long long, long long> >> expressions;

long long result = 0;

void erase_large_bits(long long& n, int p){
    n &= ((1<<p)-1);
}

void manipulate_bit(int p){

    bool success = true;

    for(int i=0; i<P; ++i){

        if(expressions[i].size()==0) continue;

        bool expression_ok = false;

        for(auto interval : expressions[i]){
            if( interval.first & (1<<p)){
                expression_ok = true;
                break;
            }
        }

        if( !expression_ok ){
            success = false;
            break;
        }
    }

    if(success){

        result |= (long long) (1<<p);

        for(int i=0; i<P; ++i){

            if(expressions[i].size() == 0) continue;

            int num_set_p = 0;
            int num_set_others = 0;

            for(auto interval : expressions[i]){
                if(interval.first & (1<<p)){
                    num_set_p++;
                    if( !(interval.second & (1<<p)) ){
                       num_set_others++;
                    }
                }
            }

            if(num_set_p >= 2 && num_set_others>=1){
                expressions[i].clear();
            }
        }
    }

    else{
        for(int i=0; i<P; ++i){

            bool clear_expression = false;

            for(int j=0; j<expressions[i].size(); ++j){
                if( (expressions[i][j].first & (1<<p)) && !(expressions[i][j].second & (1<<p)) ){
                    clear_expression = true;
                    break;
                }
            }

            if(clear_expression){
                expressions[i].clear();
            }
        }
    }

    for(int i=0; i<P; ++i){
        for(int j=0; j<expressions[i].size(); ++j){

            if( expressions[i][j].first & (1<<p) ){
                if( expressions[i][j].second & (1<<p) ){
                    erase_large_bits(expressions[i][j].first, p);
                    erase_large_bits(expressions[i][j].second, p);
                }
                else{
                    erase_large_bits(expressions[i][j].first, p);
                    expressions[i][j].second = 0;
                }
            }
        }
    }
}



int main(){


    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> P;

    expressions.resize(P);

    for(int i=0; i<P; ++i){
        cin >> K[i];
        expressions[i].resize(K[i]);
    }

    for(int i=0; i<P; ++i){
        for(int j=0; j<K[i]; ++j){
            cin >> expressions[i][j].second >>
                    expressions[i][j].first;
        }
        sort(expressions[i].begin(), expressions[i].end());
    }

    for(int i=30; i>=0; i-=1){
        manipulate_bit(i);
    }

    cout << result;

    return 0;
}
