#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define nMAX 310
#define lenMAX 90

struct base10num{
    string rep; // representation
    int d; // num of digits
    int s10; // sum of digits

    base10num(string this_rep, int this_sum){
        rep = this_rep;
        s10 = this_sum;
        d = rep.size();
    }

    char get_digit(int pos){
        if(pos<d)
            return rep[pos];
        else
            return '0';
    }
};

base10num naive_next_element(base10num& a, int b){
    string r = a.rep;
    int new_s10 = a.s10;

    if(b>a.s10){
        int pos = 0;
        while(new_s10 < b){
            while(a.get_digit(pos)=='9' || r[pos]=='9'){
                ++pos;
                if(pos>=r.size())
                    r.append(1, '0');
            }
            int inc = min((int) ('9'-r[pos]), b-new_s10);
            r[pos] = (char) (r[pos] + inc);
            new_s10 += inc;
        }
        return base10num(r, b);
    }
    bool same = true;
    int pos = 1;
    if(r.size()==1)
        r.append(1, '0');
    while(new_s10 > b || same){
        while(r[pos]=='9'){
            ++pos;
            if(pos >= r.size())
                r.append(1, '0');
        }
        r[pos] = (char) (r[pos]+1);
        ++new_s10;
        same = false;
        int zero_it = pos-1;
        while(zero_it >= 0){
            int inc = min(r[zero_it]-'0', new_s10-b);
            r[zero_it] = (char) (r[zero_it]-inc);
            new_s10 -= inc;
        }
    }
    return base10num(r, b);
}

int main(){
    int n;
    scanf("%d", &n);

    vector<base10num> aout;
    aout.push_back( base10num("0", 0) );
    int b;
    for(int i=0; i<n; ++i){
        scanf("%d", &b);
        aout.push_back( naive_next_element(aout.back(), b) );
    }

    for(int i=1; i<=n; ++i)
        cout << aout[i].rep << '\n';

    return 0;
}
