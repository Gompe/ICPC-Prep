#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1010;
const int inf = 2*1000*1000*1000;

int n, ml, md;

struct Constraint{
    int v;
    int weight;

    Constraint(int v, int weight) : v(v), weight(weight){}
};

vector<Constraint> CONSTRAINTS[MAXN];

/**

Here CONSTRAINS[a] = (b, d) means

    dis[a] >= dis[b] - d


*/

int dis[MAXN];
int times_in_queue[MAXN];

bool in_queue[MAXN];

/**

dis[x] will be decreasing throughout the program.

The program eventually ends because whenever a point
v is added to the queue, its dis was decreased by at least 1.

The task is impossible if, at some point, one of the dis[v] is
smaller than 0.

This is also sufficient, because otherwise the program ends by
finding an satisfying assignment.

*/

bool check_SAT(int i){

    queue<int> Q;

    dis[i] = 0;

    Q.push(i);
    in_queue[i] = true;

    while( !Q.empty() ){

        int u = Q.front();
        Q.pop();

        in_queue[u] = false;

        for(auto& A : CONSTRAINTS[u]){

            int v = A.v;

            if( v < i ) continue;

            if( dis[v] > dis[u] + A.weight ){
                // failed constraint

                dis[v] = dis[u] + A.weight;

                if( dis[v] < 0 ){
                    return false;
                }

                if( !in_queue[v] ){
                    Q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }

    return true;
}



int constraint_SAT(){

    fill(dis, dis + (n+1), inf);

    if( !check_SAT(1) )
        return -1;

    if( dis[n] == inf ){

        // since n is not connected to 1,
        // it only remains to check if an assignment can
        // be found

        for(int i=0; i<n; ++i){
            if(dis[i] < inf) continue;

            if( !check_SAT(i) ){
                return -1;
            }
        }
        return -2;
    }

    else{
        return dis[n];
    }

}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> ml >> md;

    // Special case of LP

    int a, b, d;

    for(int i=0; i<ml; i++){
        cin >> a >> b >> d;
        CONSTRAINTS[a].push_back( Constraint(b, d) );
    }

    for(int i=0; i<md; i++) {
        int a,b,d;
        cin >> a >> b >> d;
        CONSTRAINTS[b].push_back( Constraint(a, -d) );
    }

    for(int i=1; i<n; i++) {
        CONSTRAINTS[i+1].push_back( Constraint(i,0) );
    }

    cout << constraint_SAT();

    return 0;
}

