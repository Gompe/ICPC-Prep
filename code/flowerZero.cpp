#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <set>

using namespace std;

set< pair<int, int> > st;

struct flower{
    long long x, y, w;
};

bool cmp(flower f1, flower f2){
    if(f1.x < f2.x || (f1.x==f2.x & f1.y<f2.y) || (f1.x==f2.x & f1.y==f2.y & f1.w <= f2.w))
        return true;
    return false;
}

void insertion(pair<int, int> *it){

}

void processing(flower f){
    pair<long long ,long long> p = make_pair(f.y, f.w);

    if(st.empty()){
        st.insert(p);
        return;
    }

    auto it = st.upper_bound(p);
    if(it==st.end()){
        st.insert(p);
        return;
    }

    if((*it).first == p.first ){
        long long w = p.second + (*it).second;
        pair<long long, long long> new_element = make_pair(p.first, w);
        st.erase((*it));
        insertion(new_element);
        return;
    }

    insertion(p);
    return;
}

int main(){
    long long n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);

    flower F[k];
    for(int i=0; i<k; ++i)
        scanf("%lld %lld %lld", &F[i].x, &F[i].y, &F[i].w);

    sort(F, F+k, cmp);

}
