#include<bits/stdc++.h>

using namespace std;

struct cow{
    int M, P, A;
    long double f;

    cow(int m, int p){
        M = m;
        P = p;
        A = m*(100-p);
        f = 1.0 - (double) p/100.;
    }
};

bool operator< (cow c1, cow c2){
    if(c1.P == 0 && c2.P!=0){
        return true;
    }
    if(c1.P==0 && c2.P==0){
        return c1.A > c2.A;
    }
    return  c1.A*c2.P > c2.A*c1.P;
}

int main(){
    int N;
    scanf("%d", &N);

    vector<cow> T;
    int m, p;

    for(int i=0; i<N; ++i){
        scanf("%d %d", &m, &p);
        T.push_back(cow(m,p));
    }

    sort(T.begin(), T.end());

    bool debug = false;
    if(debug){
        printf("============================================================\n");
        for(int i=N-1; i>=0; i-=1){
            printf("%d\n", T[i].M);
        }
        return 0;
    }

    long double expected_return = 0.0;
    for(int i=N-1; i>=0; i-=1){
        expected_return += T[i].M;
        expected_return *= T[i].f;
    }

    printf("%.3Lf\n", expected_return);

    return 0;
}
