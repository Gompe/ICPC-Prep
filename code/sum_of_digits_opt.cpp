#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct base10num{
    string rep;
    int s10=0;

    base10num(string b10rep){
        rep = b10rep;
        for(int i=0; i<rep.size(); ++i){
            s10 += (int) (rep[i]-'0');
        }
    }

    void next_term(int b){
        if(s10 < b){
            int pos = 0;
            while(s10 < b){
                while(rep[pos]=='9'){
                    ++pos;
                    if(pos>=rep.size())
                        rep.append(1, '0');
                }
                int inc = min( (int)('9'-rep[pos]) , b-s10 );
                rep[pos] = (char) (rep[pos] + inc);
                s10 += inc;
            }
            return;
        }

        int pos = 0;
        int part_sum = 0;
        int diff = s10 - b;
        do{
            part_sum += (int) (rep[pos]-'0');
            rep[pos] = '0';
            ++pos;
            if(pos >= rep.size())
                rep.append(1, '0');
        } while(part_sum <= diff ||rep[pos]=='9');
        rep[pos] = (char) (rep[pos]+1);
        part_sum = part_sum-(1+diff);
        pos = 0;
        while(part_sum > 0){
            int inc = min(9, part_sum);
            rep[pos] = '0'+inc;
            part_sum -= inc;
            ++pos;
        }
        s10 = b;
        return;
    }
};

base10num first_term(int b){
    int q = (int) b/9;
    int r = b - 9*q;
    string rep;
    rep.append(q, '9');
    if(r==0)
        return base10num(rep);
    else{
        rep.append(1, (char)(r+'0') );
        return base10num(rep);
    }
}

int main(){
    int n;
    scanf("%d", &n);

    vector<string> aout;

    int b;
    scanf("%d", &b);
    base10num last = first_term(b);
    aout.push_back( last.rep );

    for(int i=1; i<n; ++i){
        scanf("%d", &b);
        last.next_term(b);
        aout.push_back( last.rep );
    }

    for(int i=0; i<n; ++i){
        reverse( aout[i].begin(), aout[i].end() );
        cout << aout[i] << '\n';
    }

    return 0;
}
