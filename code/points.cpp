#include<bits/stdc++.h>
using namespace std;

int k;

vector< pair<long long, long long> > main_pattern;
vector< pair<long long, long long> > query_pattern;

vector< pair<long long, pair< long long, long long> > > characteristic_main;
vector< pair<long long, pair< long long, long long> > > characteristic_query;

long long gcd( long long a, long long b ){

    if( a < 0 ){ a = abs(a); }
    if( b < 0 ){ b = abs(b); }

    if( a < b ) swap(a,b);
    // a>=b

    if( b == 0 ) return a;

    return gcd( b, a%b );
}

long long lcm( long long a, long long b ){

    return a*b/gcd(a,b);
}

long long norm_squared(pair<long long, long long>& pt){
    return pt.first*pt.first+pt.second*pt.second;
}

long long dot(pair<long long, long long>& pt1, pair<long long, long long>& pt2){
    return pt1.first*pt2.first + pt1.second*pt2.second;
}

long long cross(pair<long long, long long>& pt1, pair<long long, long long>& pt2){
    return pt1.second*pt2.first - pt1.first*pt2.second;
}

int quadrant( pair<long long, long long>& pt ){

    if(pt.first >= 0 && pt.second >=0) return 1;
    if(pt.first < 0 && pt.second >=0) return 2;
    if(pt.first < 0 && pt.second < 0) return 3;
    return 4;

}

bool compare_by_arg(pair<long long, long long>& pt1, pair<long long, long long>& pt2){

    int q1 = quadrant(pt1);
    int q2 = quadrant(pt2);

    if( q1 < q2 ) return true;
    if( q1 > q2 ) return false;

    long long xcross = cross(pt1, pt2);

    if( xcross < 0 ) return true;
    if( xcross > 0 ) return false;

    return norm_squared(pt1) < norm_squared(pt2);

}

void center_data(vector< pair<long long, long long> >& pattern, bool is_main=false){

    // k is the size of the pattern
    assert( pattern.size() == k );

    pair<long long, long long> kmu = {0, 0};

    for(auto& pt : pattern){
        kmu.first += pt.first;
        kmu.second += pt.second;

        pt.first *= k;
        pt.second *= k;
    }

    for(auto& pt : pattern){
        pt.first -= kmu.first;
        pt.second -= kmu.second;
    }
}

void conjugate(vector<pair<long long, long long>>& pattern){
    for(auto& pt : pattern){
        pt.second = -pt.second;
    }
}

void build_characteristic( vector< pair<long long, long long> >& pattern, bool is_main=false){

    if( is_main ) characteristic_main.clear();
    else characteristic_query.clear();

    sort(pattern.begin(), pattern.end(), compare_by_arg );

    long long d = 0;

    for(int i=0; i<k; ++i){

        pair<long long, long long> pt0 = pattern[i];
        pair<long long, long long> pt1 = pattern[(i+1)%k];

        long long ns = norm_squared(pt0);
        long long xdot = dot(pt0, pt1);
        long long xcross = cross(pt0, pt1);

        d = gcd(d, ns);
        d = gcd(d, xdot);
        d = gcd(d, xcross);

        if( is_main ){
            characteristic_main.push_back( {ns, {xdot, xcross}} );
        }
        else{
            characteristic_query.push_back( {ns, {xdot, xcross}} );
        }
    }

    for(int i=0; i<k; ++i){
        if( is_main ){
            characteristic_main[i].first /= d;
            characteristic_main[i].second.first /= d;
            characteristic_main[i].second.second /= d;
        }
        else{
            characteristic_query[i].first /= d;
            characteristic_query[i].second.first /= d;
            characteristic_query[i].second.second /= d;
        }
    }

}

void scale_characteristic(vector< pair<long long, pair< long long, long long> > >& phi, long long r, bool divide=false){

    for(auto& p: phi){
        if(divide){
            p.first /= r;
            p.second.first /= r;
            p.second.second /= r;
        }
        else{
            p.first *= r;
            p.second.first *= r;
            p.second.second *= r;
        }

    }

}

bool match( vector<pair<long long, long long>>& pattern ){

    build_characteristic(pattern);

    // match is true if characteristic_main
    // and characteristic_query are the same up to
    // a rotation

    // =================================================
    // Normalize to make sure they are in the same scale

    long long scale_1 = 0;
    long long scale_2 = 0;

    for(int i=0; i<k; ++i){
        scale_1 += characteristic_main[i].first;
        scale_2 += characteristic_query[i].first;
    }

    long long LCM = lcm(scale_1, scale_2);

    scale_characteristic( characteristic_main, LCM/scale_1 );
    scale_characteristic( characteristic_query, LCM/scale_2 );


    int n = k;
    vector<int> z(2*n);

    for (int i = 0, l = 0, r = 0; i < 2*n; ++i) {

        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);

        while ( z[i] < n &&
                i + z[i] < 2*n &&
                characteristic_main[z[i]] == characteristic_query[(i + z[i])%n]
                )

            ++z[i];

        if( z[i] == n ){

            scale_characteristic( characteristic_main, LCM/scale_1, true);

            return true;
        }

        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }

    scale_characteristic( characteristic_main, LCM/scale_1, true);

    return false;

}


void query(){

    query_pattern.clear();

    int I;
    cin >> I;

    for(int i=0; i<I; ++i){
        long long x,y;
        cin >> x >> y;
        query_pattern.push_back( {x,y} );
    }

    if( I==1 && k ==1 ){
        cout << "TAK\n";
        return;
    }

    if( I != k ){
        cout << "NIE\n";
        return;
    }

    center_data(query_pattern);

    if( match(query_pattern) ){
        cout << "TAK\n";
        return;
    }

    conjugate(query_pattern);

    if( match(query_pattern) ){
        cout << "TAK\n";
        return;
    }

    cout << "NIE\n";
}

int main(){

    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    // edge case k = 1
    cin >> k;

    for(int i=0; i<k; ++i){
        long long x, y;
        cin >> x >> y;

        main_pattern.push_back({x, y});
    }

    if( k!=1 ){

        center_data(main_pattern, true);

        build_characteristic(main_pattern, true);

    }

    int n;
    cin >> n;
    while(n--){
        query();
    }

    return 0;
}

