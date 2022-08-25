#include<bits/stdc++.h>
using namespace std;

using ld = long double;

int main(){

    ld k1, k2;
    int m,n;

    scanf("%Lf %Lf", &k1, &k2);
    scanf("%d %d", &m, &n);

    int s = n/m, r = n%m;
    assert(s*m+r == n);

    ld minCost = -1;

    if( r==0 ){
        ld cost = 0;

        int p = 100/m, q=100%m;
        int p1 = p/s, q1 = p%s;
        int p2 = (p+1)/s, q2 = (p+1)%s;

        cost += k1*( p*p*(m-q)+(p+1)*(p+1)*q );

        cost += k2 * ( p1*p1*(s-q1)+(p1+1)*(p1+1)*q1 ) * (m-q);
        cost += k2 * ( p2*p2*(s-q2)+(p2+1)*(p2+1)*q2 ) * q;

        if(minCost>cost || minCost==-1){
                minCost = cost;
        }
    }

    else{
        for(int x = m-r; x <= 100-r; ++x){

            ld cost = 0;

            // left
            int p = x/(m-r), q = x%(m-r);
            int p1 = p/s, q1 = p%s;
            int p2 = (p+1)/s, q2 = (p+1)%s;

            cost += k1*( p*p*(m-r-q)+(p+1)*(p+1)*q );

            cost += k2 * ( p1*p1*(s-q1)+(p1+1)*(p1+1)*q1 ) * (m-r-q);
            cost += k2 * ( p2*p2*(s-q2)+(p2+1)*(p2+1)*q2 ) * q;

            // right
            p = (100-x)/r, q = (100-x)%r;
            p1 = p/(s+1), q1 = p%(s+1);
            p2 = (p+1)/(s+1), q2 = (p+1)%(s+1);

            cost += k1*( p*p*(r-q)+(p+1)*(p+1)*q );

            cost += k2*( p1*p1*(s+1-q1)+(p1+1)*(p1+1)*q1 ) * (r-q);
            cost += k2*( p2*p2*(s+1-q2)+(p2+1)*(p2+1)*q2 ) * q;

            if(minCost>cost || minCost==-1){
                minCost = cost;
            }
        }
    }

    printf("%.3Lf", minCost);

    return 0;
}
