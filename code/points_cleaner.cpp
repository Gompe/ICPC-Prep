#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using triple = pair< ll, pair<ll, ll> >;

int k;

struct point{

    ll x;
    ll y;

    point(ll x, ll y){
        this->x = x;
        this->y = y;
    }

    ll norm_squared()   const;

    int quadrant()  const{
        if(x>=0 && y>=0) return 1;
        if(x< 0 && y>=0) return 2;
        if(x< 0 && y< 0) return 3;
        return 4;
    }

    void reflect_x_axis(){
        y = -y;
    }

};


vector<point> main_pattern;
vector<triple> main_sequence;


ll dot(const point& p1, const point& p2){
    return p1.x*p2.x + p1.y*p2.y;
}

ll cross(const point& p1, const point& p2){
    return p1.x*p2.y - p1.y*p2.x;
}


point operator+(const point& p1, const point& p2){
    return point(p1.x+p2.x, p1.y+p2.y);
}

point operator-(const point& p1, const point& p2){
    return point(p1.x-p2.x, p1.y-p2.y);
}

point operator*(ll a, const point& p){
    return point(a*p.x, a*p.y);
}

ll point::norm_squared()   const{
        return dot(*this, *this);
}

bool operator<(const point& p1, const point& p2){

    int q1 = p1.quadrant();
    int q2 = p2.quadrant();

    if(q1<q2) return true;
    if(q2<q1) return false;

    if(cross(p1,p2) > 0) return true;
    if(cross(p1,p2) < 0) return false;

    return p1.norm_squared() < p2.norm_squared();
}


void reflect_x_axis(vector<point>& collection){
    for(auto& pt : collection)
        pt.reflect_x_axis();
}

void center_data(vector<point>& collection){

    point kmu(0,0);
    for(auto& pt : collection){
        kmu = kmu + pt;
        pt = k*pt;
    }

    for(auto& pt : collection){
        pt = pt - kmu;
    }
}

void build_seq(vector<point>& collection, vector<triple>& sequence){

    sequence.clear();

    sort(collection.begin(), collection.end());

    for(int i=0; i<k; ++i){

        point pt0 = collection[i];
        point pt1 = collection[(i+1)%k];

        ll data1 = pt0.norm_squared();
        ll data2 = dot(pt0, pt1);
        ll data3 = cross(pt0, pt1);

        sequence.push_back({data1, {data2, data3}});
    }
}

ll gcd(ll a, ll b){

    a = abs(a);
    b = abs(b);

    if(a<b) swap(a,b);
    if(b==0) return a;
    return gcd(b, a%b);
}

ll lcm(ll a, ll b){
    return a*b/gcd(a,b);
}

triple find_scale(vector<triple>& seq1, vector<triple>& seq2){

    ll w1 = 0, w2 = 0;
    for(auto& t : seq1) w1 += t.first;
    for(auto& t : seq2) w2 += t.first;

    return { lcm(w1, w2), {w1, w2} };

}

void scale_sequence(vector<triple>& sequence, ll r, bool divide=false){
    for(auto& data : sequence){
        if(divide){
            data.first /= r;
            data.second.first /= r;
            data.second.second /= r;
        }
        else{
            data.first *= r;
            data.second.first *= r;
            data.second.second *= r;
        }
    }
}

bool match(vector<triple>& sequence1, vector<triple>& sequence2){

    bool result = false;

    int n = k;
    vector<int> z(2*n);

    for (int i = 0, l = 0, r = 0; i < 2*n; ++i) {
        if (i <= r){
            z[i] = min (r - i + 1, z[i - l]);
        }

        while ( z[i] < n &&
                i + z[i] < 2*n &&
                sequence1[z[i]] == sequence2[(i + z[i])%n]){

            ++z[i];
        }
        if( z[i] == n ){
            result = true;
            break;
        }
        if (i + z[i] - 1 > r){
            l = i, r = i + z[i] - 1;
        }
    }

    return result;
}


void ACCEPT(){
    printf("TAK\n");
}

void REJECT(){
    printf("NIE\n");
}

void query(){

    int I;
    scanf("%d", &I);

    vector<point> query_pattern;

    for(int i=0; i<I; ++i){
        ll x,y;
        scanf("%lld%lld", &x, &y);

        query_pattern.push_back( point(x,y) );
    }

    if( I==1 && k==1 ){
        ACCEPT();
        return;
    }

    if ( I!=k ){
        REJECT();
        return;
    }

    center_data( query_pattern );

    vector<triple> query_sequence;

    for(int i=0; i<2; ++i){

        build_seq( query_pattern, query_sequence );

        triple Multiples = find_scale(main_sequence, query_sequence);

        ll ratio1 = Multiples.first/Multiples.second.first;
        ll ratio2 = Multiples.first/Multiples.second.second;

        scale_sequence(main_sequence, ratio1);
        scale_sequence(query_sequence, ratio2);

        if( match(main_sequence, query_sequence) ){
            ACCEPT();
            scale_sequence(main_sequence, ratio1, true);
            return;
        }

        scale_sequence(main_sequence, ratio1, true);

        if( i==1 ) break;

        reflect_x_axis(query_pattern);
    }

    REJECT();
}

int main(){

    scanf("%d", &k);

    for(int i=0; i<k; ++i){
        ll x, y;
        scanf("%lld%lld", &x, &y);

        main_pattern.push_back( point(x,y) );
    }

    /*
    sort(main_pattern.begin(), main_pattern.end());

    cout << "Sorted Points" << endl;
    for(auto& pt: main_pattern)
        cout << pt.x << " " << pt.y << endl;
    */

    if( k!=1 ){
        center_data(main_pattern);
        build_seq(main_pattern, main_sequence);
    }

    int n;
    scanf("%d", &n);
    while(n--){
        query();
    }

    return 0;
}

/**

for sorting:

10

0 0
4 0
1 2
1 2
1 -1
1 -2
0 4
2 1
-1 1
-2 -3

*/


/**

Tests:

4
0 0
1 2
1 -1
4 0
10
4
0 0
1 2
1 -1
4 0
4
0 0
1 -2
4 0
1 1
4
0 0
2 1
-1 1
0 4
4
3 3
5 4
2 4
3 7
4
6 6
10 8
4 8
6 14
4
-6 6
-10 8
-4 8
-6 14
4
-600 600
-100 800
-400 800
-600 1400

======================

4
0 0
1 2
1 -1
4 0
10
4
-6 6
-10 8
-4 8
-6 14
4
-600 600
-100 800
-400 800
-600 1400
4
-600 600
-1000 800
-400 800
-600 1400

*/






