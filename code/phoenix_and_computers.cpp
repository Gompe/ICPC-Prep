#include <iostream>
#include <mem.h>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define NAX 410

long long factorial[2*NAX];
long long inv_factorial[2*NAX];
long long M;

vector< vector<long long> > te_vec;
vector< vector<long long> > oe_vec;

long long binexp(long long base, long long exponent){
    if(exponent == 0)
        return 1;

    long long res = binexp(base, (long long) exponent/2);
    if(exponent%2 == 1){
        long long aux = res*res%M;
        return aux*base%M;
    }
    else
        return res*res%M;
}

long long inverse_mod(long long x){
    return binexp(x, M-2);
}

void compute_factorials(){

    factorial[0] = 1;
    inv_factorial[0] = 1;

    long long res=1;
    for(int k=1; k<2*NAX; ++k){
        res = (res*k)%M;
        factorial[k] = res;
        inv_factorial[k] = inverse_mod(res);
    }
}

void two_end_compute(int n){

    if(n<=3)
        return;

    if(n>=5)
        two_end_compute(n-1);

    te_vec[n].clear();
    te_vec[n].resize(n, 0);

    for(int i=2; i<=n-1; ++i){
        // two_end problems
        // size i to the left
        // size n-i+1 to the right
        for(int k=0; k<te_vec[i].size(); ++k){
            if(te_vec[i][k] == 0)
                continue;
            for(int l=0; l<te_vec[n+1-i].size(); ++l){
                if(te_vec[n+1-i][l] == 0)
                    continue;
                long long ways = te_vec[i][k]*te_vec[n+1-i][l]%M;
                ways = ways*factorial[k+l]%M;
                ways = ways*inv_factorial[k]%M;
                ways = ways*inv_factorial[l]%M;
                te_vec[n][k+l+1] = (te_vec[n][k+l+1] + ways)%M;
            }
        }
    }
}

void one_end_compute(int n){

    if(n<2)
        return;

    if(n>=3)
        one_end_compute(n-1);

    oe_vec[n].clear();
    oe_vec[n].resize(n, 0);

    for(int i=2; i<=n; ++i){
        // one_end problem and two_end problem
        // size i to the left (te)
        // size n+1-i to the right (oe)
        for(int k=0; k<te_vec[i].size(); ++k){
            if(te_vec[i][k] == 0)
                continue;
            for(int l=0; l<oe_vec[n+1-i].size(); ++l){
                if(oe_vec[n+1-i][l] == 0)
                    continue;
                long long ways = te_vec[i][k]*oe_vec[n+1-i][l]%M;
                ways = ways*factorial[k+l]%M;
                ways = ways*inv_factorial[k]%M;
                ways = ways*inv_factorial[l]%M;
                oe_vec[n][k+l+1] = (oe_vec[n][k+l+1] + ways)%M;
            }
        }
    }
}

long long zero_end_compute(int n){

    long long res = 0;

    for(int i=1; i<=n; ++i){
        // two one_end problems
        for(int k=0; k<oe_vec[i].size(); ++k){
            if(oe_vec[i][k] == 0)
                continue;
            for(int l=0; l<oe_vec[n+1-i].size(); ++l){
                if(oe_vec[n+1-i][l] == 0)
                    continue;
                long long ways = oe_vec[i][k]*oe_vec[n+1-i][l]%M;
                ways = ways*factorial[k+l]%M;
                ways = ways*inv_factorial[k]%M;
                ways = ways*inv_factorial[l]%M;
                res = (res + ways)%M;
            }
        }
    }

    return res;
}

// 150 234567899

int main(){
    int n;
    scanf("%d %lld", &n, &M);

    te_vec.resize(NAX);
    oe_vec.resize(NAX);

    te_vec[3].push_back(1);
    te_vec[2].push_back(1);
    oe_vec[1].push_back(1);

    compute_factorials();

    two_end_compute(n);
    one_end_compute(n);

    printf("%lld\n", zero_end_compute(n));

    return 0;
}
