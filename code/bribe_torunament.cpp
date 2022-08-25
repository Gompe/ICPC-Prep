#include <iostream>
#include <algorithm>
#include <cstdio>
#include <set>

using namespace std;

void printset( multiset<long long> st){
    printf("ELEMENTS:\n");
    for(multiset<long long>::iterator it=st.begin(); it!=st.end(); ++it)
        printf("%lld ", *it);
    printf("\n");
}

int main(){
    long long n;
    scanf("%lld", &n);

    bool ok = false;

    long long p[n];
    long long h;

    for(int i=0; i<n; ++i){
        long long a;
        scanf("%lld", &a);

        if(a==-1){
            ok = true;
            h=i;
            p[i] = -1;
            continue;
        }

        if(ok){
            p[i] = a;
        }
        else{
            p[i] = 0;
        }
    }

    long long cost=0;
    long long time = n-1;
    multiset<long long> st;

    for(int it=n-1; it>=0; --it){
        if( it==h )
            break;

        st.insert(p[it]);
        if( it==time ){

            //printset(st);

            cost += *st.begin();
            st.erase( st.begin() );
            time = ( (time+1)>>1 )-1;
        }
    }

    printf("%lld\n", cost);

    return 0;
}
