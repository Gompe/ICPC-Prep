#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;

int MaxDepth = 0;

int next3(int x, int r){
    int r1 = x%3;
    if(r1>r)
        return x+3+r-r1;
    else
        return x+r-r1;
}

int treeSearch(int a, int b, int c, int depth=0){

    if(depth > MaxDepth)
        return -1;

    int numMax = max( {a,b,c} );

    if( a==numMax ){
        int a0 = max(b,c) - min(b,c);
        if( b==c ){
            return 1;
        }
        else{
            int tS = treeSearch(a0, b, c, depth+1);
            if(tS == -1)
                return -1;
            return next3(tS, 1);
        }
    }

    if( b==numMax ){
        int b0 = max(a,c) - min(a,c);
        if( a==c ){
            return 2;
        }
        else{
            int tS = treeSearch(a,b0,c, depth+1);
            if(tS == -1)
                return -1;
            return next3(tS, 2);
        }
    }

    if( c==numMax ){
        int c0 = max(b,a) - min(b,a);
        if( b==a ){
            return 3;
        }
        else{
            int tS = treeSearch(a,b,c0, depth+1);
            if(tS == -1)
                return -1;
            return next3(tS, 0);
        }
    }
}

int fastSearch(int a, int b, int c){
    int d = 0;
    int a0, b0, c0;
    while( d <= MaxDepth ){
        int numMax = max( {a,b,c} );
        a0 = a, b0 = b, c0 = c;

        if( a==numMax ){
            if( b==c ){
                return d+1;
            }
            if( b>c ){
                d += 2;
            }
            else{
                d+=1;
            }
            a0 = max(b,c) - min(b,c);
        }
        if( b==numMax ){
            if( a==c ){
                return d+2;
            }
            if( c>a ){
                d+=2;
            }
            else{
                d+=1;
            }
            b0 = max(a,c) - min(a,c);
        }
        if( c==numMax ){
            if( a==b ){
                return d+3;
            }
            if( a>b ){
                d+=2;
            }
            else{
                d+=1;
            }
            c0 = max(a,b) - min(a,b);
        }
        a = a0, b = b0, c = c0;
    }
    return -1;
}


void query(int N, int M){ //, vector< array<int,3> > *pcases, int *p){
    int p = 0;
    vector<int> a,b,c;

    for(int i=1; i < M; i++){
        switch( N%3 ){
            case 1:
                if( fastSearch(M, i, M-i) == N){
                    a.push_back(M);
                    b.push_back(i);
                    c.push_back(M-i);
                    p++;

                    //pcases->push_back( array<int, 3>{M, i, M-i} );
                    //(*p)++;
                }
            case 2:
                if( fastSearch(i, M, M-i) == N){
                    a.push_back(i);
                    b.push_back(M);
                    c.push_back(M-i);
                    p++;

                    //pcases->push_back( array<int, 3>{i, M, M-i} );
                    //(*p)++;
                }
            case 0:
                if( fastSearch(i, M-i, M) == N){
                    a.push_back(i);
                    b.push_back(M-i);
                    c.push_back(M);
                    p++;


                    //pcases->push_back( array<int, 3>{i, M-i, M} );
                    //(*p)++;
                }
        }
    }
    printf("%d \n", p);
    for(int i=0; i < p; i++){
        printf("%d %d %d \n", a[i], b[i], c[i]);
    }
}


int main(){

    while(true){
        int N, M;
        scanf("%d %d", &N, &M);
        if(N==-1 && M==-1)
            break;
        int p = 0;
        vector< array<int, 3> > pcases;
        MaxDepth = N+1;

        query(N, M);
    }

    return 0;
}
