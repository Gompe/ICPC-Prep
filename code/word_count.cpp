#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

#define POW_SIZE 1100

int p = 53;
long long m = 1e9 + 53;

long long powers[POW_SIZE];

string word;
vector<long long> word_hashes;

void compute_powers(){
    powers[0] = 1;
    for(int i=1; i<POW_SIZE; i++){
        powers[i] = (powers[i-1]*p)%m;
    }
}

int chnum(char ch){
    return int(ch) - int('a') + 1;
}

void make_hashes(string s, vector<long long>& hash_list){
    hash_list.push_back(0);
    for(int i=0; i<s.size(); i++){
        long long new_hash = ( hash_list.back() + powers[i]*chnum(s[i]) )%m;
        hash_list.push_back(new_hash);
    }
}

struct road{
    int endr;
    string s;
    vector<long long> hash_list;

    road(int end_node, string road_string){
        endr = end_node;
        s = road_string;
        make_hashes(s, hash_list);
    }
};

long long word_count( vector< vector<road> >& a, int start, vector< pair<int, long long> >& carries ){

    long long aout = 0;

    for(auto r: a[start]){
        vector< pair<int, long long> > next_carries;

        for(int i=0; i<r.s.size(); i++){
            if( r.s.size() - i >= word.size() ){
                if( (r.hash_list[i + word.size()] - r.hash_list[i])%m == (powers[i]*word_hashes[ word.size() ])%m ){
                    aout++;
                    //cout << "CASE 1: "<< start << " " << i << " " << r.endr << "\n";
                }
            }
            else{
                if( (r.hash_list[r.s.size()]- r.hash_list[i])%m == (powers[i]*word_hashes[ r.s.size()-i ])%m){
                    next_carries.push_back( make_pair( r.s.size()-i ,word_hashes[ r.s.size()-i ] ) );
                }
            }
        }

        for(auto carry : carries){
            int seg0 = carry.first;
            int seg1 = r.s.size() + seg0;

            long long hash0 = carry.second;
            long long hash1;

            if( seg1 >= word.size() ){
                if( (hash0 + powers[seg0]*r.hash_list[word.size()-seg0])%m == word_hashes[word.size()]){
                    aout++;
                    //cout << "CASE 2: "<< start  << "\n";

                }
            }
            else{
                hash1 = (hash0 + powers[seg0]*r.hash_list[r.s.size()])%m;

                if( hash1 == word_hashes[seg1] )
                    next_carries.push_back( make_pair( seg1, hash1 ) );
            }
        }

        aout += word_count(a, r.endr, next_carries);
    }
    return aout;
}

int main(){
    compute_powers();

    int N;
    cin >> N;

    vector< vector<road> > a;
    a.resize(N);

    for(int i=0; i<N-1; i++){
        int I, J;
        string s;
        cin >> I >> J >> s;

        road r = road(J, s);
        a[I].push_back(r);
    }

    cin>> word;
    make_hashes(word, word_hashes);

    vector< pair<int, long long> > c;
    cout <<word_count(a, 0, c)<<"\n";

    return 0;
}
