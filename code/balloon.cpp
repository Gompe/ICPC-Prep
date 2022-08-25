#include<bits/stdc++.h>
using namespace std;

#define debug false

const int MOD = 2004;

unordered_map<long long, long long> polynomial;


long long binexp_mod167(long long x, long long b){
    long long res = 1;
    while(b){
        if(b&1) res = (res*x)%167;
        x = (x*x)%167;
        b >>= 1;
    }
    return res;
}

long long inverse_mod167(long long x){
    return binexp_mod167(x, 165);
}

long long binomial_mod2004(long long n, long long k){
    // returns binom(n,k) mod MOD
    if(k==0) return 1;
    if(n<k) return 0;

    // get mod 167
    long long res_mod167 = 1;
    for(int l=0; l<k; ++l){
        res_mod167*= (n-l)%167;
        res_mod167*= inverse_mod167(l+1);
        res_mod167%=167;
    }
    res_mod167 = (167+(res_mod167%167))%167;
    // done 167

    // get mod 3
    long long v3 = 0;
    long long res_mod3 = 1;
    for(int l=0; l<k; ++l){
        long long a = n-l, b = l+1;
        while(a%3==0){
            v3++;
            a/=3;
        }
        while(b%3==0){
            v3--;
            b/=3;
        }
        if(a%3==2) res_mod3*=(-1);
        if(b%3==2) res_mod3*=(-1);
    }
    if(v3>0) res_mod3=0;
    else res_mod3 = (3+(res_mod3%3))%3;
    // done 3

    // get mod 4
    long long v2=0;
    long long res_mod4 = 1;
    for(int l=0; l<k; ++l){
        long long a = n-l, b = l+1;
        while(a%2==0){
            v2++;
            a/=2;
        }
        while(b%2==0){
            v2--;
            b/=2;
        }
        if(a%4==3) res_mod4*=(-1);
        if(b%4==3) res_mod4*=(-1);
    }
    if(v2>=2) res_mod4=0;
    else if(v2==1) res_mod4=2;
    else res_mod4 = (4+(res_mod4%4))%4;
    // done 4

    // Now we have to recover the value mod 2004
    long long res_mod2004 = 0;
    res_mod2004 -= res_mod3*4*167;
    res_mod2004 += res_mod4*3*167;
    res_mod2004 += res_mod167*3*4*inverse_mod167(12);

    res_mod2004 = (2004+(res_mod2004%2004))%2004;
    return res_mod2004;
}


void multiply_to_polynomial(long long m){
    // multiplies 1-x^(m+1) to polynomial
    unordered_map<long long, long long> new_polynomial;
    for (const auto & [alpha,c] : polynomial){
        new_polynomial[alpha] = c;
    }
    for (const auto & [alpha,c] : polynomial){
        if(new_polynomial.count(alpha+m+1))
            new_polynomial[alpha+m+1] -= c;
        else
            new_polynomial[alpha+m+1] = -c;
    }
    polynomial = new_polynomial;

}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // polynomial starts being 1
    polynomial[0] = 1;

#if debug
    while(1){
        int m;
        cin >> m;

        multiply_to_polynomial(m);
        for (const auto & [alpha, c] : polynomial)
            cout << "exp: "<<alpha<<" coeff: "<<c<<endl;
        cout << "======================================"<<endl;

    }
#endif // debug

    long long n,a,b;
    cin >> n >> a >> b;

    long long m;
    for(int i=0; i<n; ++i){
        cin >> m;
        multiply_to_polynomial(m);
    }

    long long res = 0;
    for (const auto & [alpha,c] : polynomial){
        res += c*binomial_mod2004(b-alpha+n, n);
        res -= c*binomial_mod2004(a-1-alpha+n,n);

        // make sure that res in [0,1,...,MOD-1]
        res = (MOD+(res%MOD))%MOD;
    }

    cout << res << "\n";
    return 0;
}
