#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include<algorithm>
#include<set>
#include<vector>

using namespace std;

set <pair<int, int>> st;

int solveRepeated( int y, int v ){
    pair <int, int> p = make_pair(y, -1);
    auto it = st.upper_bound( p );

    if(it == st.end()){
        return -1;
    }

    else if( (*it).first != y){
        return -1;
    }

    //Now we solve when y is inside
    v += (*it).second;
    st.erase(*it);
    st.insert( make_pair(y, v) );
    return v;
}

void cleanSet(int y, int v){
    //printf("\n cleaning for y=%d, v=%d \n ", y, v);
    auto it = st.upper_bound(make_pair(y ,v));
    vector<pair<int, int>> u;
    while( it!=st.end() && (*it).second<= v ){
        u.push_back(*it);
        ++it;
    }
    for(auto q : u){
        st.erase(q);
    }
}

void process( pair<int, int> p ){

    if (st.empty()){
        st.insert(p);
        return;
    }

    int v = solveRepeated(p.first, p.second);

    if( v!=-1 ){
        cleanSet(p.first, v);
        return;
    }

    auto it = st.upper_bound( p );

    if (it == st.begin()){
        v = p.second;
        st.insert(p);
    }
    else if (it == st.end()){
        --it;
        v = p.second + (*it).second;
        st.insert( make_pair(p.first, v) );
    }
    else{
        --it;
        v = (*it).second + p.second;
        st.insert( make_pair(p.first, v) );
    }

    cleanSet(p.first, v);
}

void printSet(){
    for( auto it = st.begin(); it!=st.end(); ++it ){
        printf("(%d, %d) ", (*it).first, (*it).second);
    }
    cout << "\n";
}

int main(){

    /*
    ios::sync_with_stdio(0);
    cin.tie(0); */

    int n, m, k;
    cin >> n >> m >> k;

    pair< pair<int, int>, int> f[k];

    for (int i=0; i<k; i++){
        cin>>f[i].first.first>>f[i].first.second;
        cin>>f[i].second;
    }

    sort (f, f+k);

    for (int i=0; i<k; i++){
        process( make_pair(f[i].first.second, f[i].second) );
        //printSet();
    }

    cout << (*--st.end()).second ;

    return 0;
}
