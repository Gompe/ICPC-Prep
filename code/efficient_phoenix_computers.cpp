#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define NAX 410

/*

_ _ _ _ x

g(n) -> with end



*/

long long M;
vector< vector<long long> > v(NAX);

void step_list(int n){
    if(v[n].size()!=0)
        return;
    v[n].resize(NAX);
    for(int i=1; i<=n; ++i){
        // left -> i
        // right -> n+1-i
        for(int k=0; k<=i; ++k){
            for(int l=0; l<=n+1-i; ++l){


            }
        }
    }
}

long long f(int n){


}

int main(){
    int N; // N<400
    scanf("%d %lld", &N, &M);

    printf("%lld", f(N));

    return 0;
}
