#include <iostream>
#include <set>

using namespace std;

long long balance = 0;
int num_pos = 0;
multiset<long long> st;

void insertion(long long a){
    balance -= a;
    st.insert(a);
    if( balance<0 ){
        auto last_ptr = --st.end();
        balance += *last_ptr;
        st.erase(last_ptr);
    }
}

int main(){
    int n;
    scanf("%d", &n);

    long long a;
    for(int i=0; i<n; ++i){
        scanf("%lld", &a);
        if(a>=0){
            ++num_pos;
            balance += a;
        }
        else
            insertion(-a);
    }
    printf("%lld\n", (long long) num_pos+st.size());
    return 0;
}
