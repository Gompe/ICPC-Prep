#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <queue>
#include <mem.h>

using namespace std;

long long n, m, w;
long long a[2010][2010];

long long s[2010][2010];
long long t[2010][2010];

long long best_sportal = -1;
long long best_tportal = -1;

bool is_valid( int x, int y ){
    if(x<0 || x>=n || y<0 || y>=m)
        return false;
    if(a[x][y] == -1)
        return false;
    return true;
}

void s_bfs(){
    queue< pair<int, int> > q;
    q.push( {0,0} );

    memset(s, -1, sizeof(s));
    s[0][0] = 0;

    while(!q.empty()){
        pair<int, int> v = q.front();
        q.pop();

        int x = v.first, y = v.second;
        if(is_valid(x+1, y) && s[x+1][y]==-1){
            s[x+1][y] = w+s[x][y];
            q.push( {x+1, y} );
        }
        if(is_valid(x-1, y) && s[x-1][y]==-1){
            s[x-1][y] = w+s[x][y];
            q.push( {x-1, y} );
        }
        if(is_valid(x, y+1) && s[x][y+1]==-1){
            s[x][y+1] = w+s[x][y];
            q.push( {x, y+1} );
        }
        if(is_valid(x, y-1) && s[x][y-1]==-1){
            s[x][y-1] = w+s[x][y];
            q.push( {x, y-1} );
        }
        if( a[x][y]>0 ){
            //portal
            if(best_sportal == -1)
                best_sportal = a[x][y]+s[x][y];
            best_sportal = min(best_sportal, a[x][y]+s[x][y]);
        }
    }
}

void t_bfs(){
    queue< pair<int, int> > q;
    q.push( {n-1, m-1} );

    memset(t, -1, sizeof(t));
    t[n-1][m-1] = 0;

    while(!q.empty()){
        pair<int, int> v = q.front();
        q.pop();

        int x = v.first, y = v.second;

        if(is_valid(x+1, y) && t[x+1][y]==-1){
            t[x+1][y] = w+t[x][y];
            q.push( {x+1, y} );
        }
        if(is_valid(x-1, y) && t[x-1][y]==-1){
            t[x-1][y] = w+t[x][y];
            q.push( {x-1, y} );
        }
        if(is_valid(x, y+1) && t[x][y+1]==-1){
            t[x][y+1] = w+t[x][y];
            q.push( {x, y+1} );
        }
        if(is_valid(x, y-1) && t[x][y-1]==-1){
            t[x][y-1] = w+t[x][y];
            q.push( {x, y-1} );
        }

        if( a[x][y]>0 ){
            //portal
            if(best_tportal == -1)
                best_tportal = a[x][y]+t[x][y];
            best_tportal = min(best_tportal, a[x][y]+t[x][y]);
        }
    }
}

int main(){
    scanf("%lld %lld %lld", &n, &m, &w);
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            scanf("%lld", &a[i][j]);
        }
    }

    s_bfs();
    t_bfs();

    long long best_portal_cost = -1;
    if(best_sportal != -1 && best_tportal != -1)
        best_portal_cost = best_sportal + best_tportal;

    long long answer = -1;

    if(best_portal_cost == -1)
        answer = t[0][0];
    else if(t[0][0] == -1)
        answer = best_portal_cost;
    else
        answer = min(best_portal_cost, t[0][0]);

    printf("%lld\n", answer);
    return 0;
}
