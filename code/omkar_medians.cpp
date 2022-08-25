#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

void answer(bool c){
    if(c)
        printf("YES\n");
    else
        printf("NO\n");
}

void test_case(){
    int n;
    scanf("%d", &n);
    set<long long> s;

    long long last, b;
    scanf("%lld", &last);

    s.insert(last);
    bool valid = true;

    for(int i=1; i<n; i++){

        scanf("%lld", &b);

        if( b==last || !valid )
            continue;

        set<long long>::iterator pos = s.find(last);

        if( b<last ){
            if( pos != s.begin() & b<*(--pos) ){
                valid = false;
                continue;
            }
        }

        else{ // b > last
            if( pos != (--s.end()) & b>*(++pos) ){
                valid = false;
                continue;
            }
        }

        s.insert(b);
        last = b;
    }

    answer(valid);
    return;
}

int main(){
    int t;
    scanf("%d", &t);

    for(int i=0; i<t; i++)
        test_case();

    return 0;
}
