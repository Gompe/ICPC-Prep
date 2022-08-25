#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;

int N, M;

void storeSolution(int a, int b, int c){

}

void spaceSearch(int a, int b, int c, int n){
    m = max( {a,b,c} );

    if( n>=N || m > M){
        return;
    }

    if( a==m ){
        if( b>c ){
            n += 2;
        }
        else{
            n += 1;
        }
    }
    if( b==m ){
        if( c>a ){
            n+=2;
        }
        else{
            n+=1;
        }
    }
    if( c==m ){
        if( a>b ){
            n+=2;
        }
        else{
            n+=1;
        }
    }

    if( m==M && n==N){
        storeSolution(a,b,c,n);
    }

    if( a==m ){
        spaceSearch(a, a+c, c, n);
        spaceSearch(a, b, a+b, n);
    }

    if( b==m ){
        spaceSearch(b+c, b, c, n);
        spaceSearch(a, b, a+b, n);
    }

    if( c==m ){
        spaceSearch(b+c, b, c, n);
        spaceSearch(a, a+c, c, n);
    }
}

int main(){

    while(true){
        scanf("%d %d", &N, &M);
        if(N==-1 && M==-1)
            break;
        int p = 0;
        vector< array<int, 3> > pcases;

        test(N, M, &pcases, &p);
        printQuery(&p, &pcases);
    }

    return 0;
}