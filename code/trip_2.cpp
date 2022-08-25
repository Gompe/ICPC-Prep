#include<bits/stdc++.h>
using namespace std;


const int MAXN = 50010, MAXM = 100010;
int N, M, P, T;

struct Route{

    int source, destination;
    int a, b, c, d;

    int value = -1;
    int index;

    Route(int s, int t, int a, int b, int c, int d){
        source = s;
        destination = t;
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }

    bool update(int time){

        if(value == -1 || value > time){
            value = time;
            return true;
        }

        return false;
    }

    struct CompPtr{
        bool operator()(Route *r1, Route *r2){
            return r1->d > r2->d;
        }
    };
};



vector< vector< Route* > > routes;

void bfs(Route *initial_route){

    priority_queue<Route*, vector<Route*>, Route::CompPtr > to_process;
    to_process.push(initial_route);

    while( !to_process.empty() ){

        Route *curr = to_process.top();
        to_process.pop();

        if(curr->destination == -1) continue;

        int sz = routes[curr->destination].size()-1;
        while( sz>=0 ){
            Route *next = routes[curr->destination][sz];
            if(next->a >= curr->d){
                if( next->update(curr->value + next->b - curr->c) ){
                    to_process.push(next);
                }
            }
            else{
                assert( sz==routes[curr->destination].size()-1 );
                routes[curr->destination].pop_back();
            }
            sz--;
        }

    }
}


bool compare_by_a(Route *r1, Route *r2){
    return r1->a > r2->a;
}


int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> P >> T;
    --P;

    routes.resize(N);

    int s,t;
    int a,b,c,d;

    for(int i=0; i<M; ++i){
        cin >> s >> t;
        s--; t--;

        cin >> a >> b >> c >> d;

        routes[s].push_back(new Route(s,t,a,b,c,d));
    }

    Route *phantom_route0 = new Route(-1, 0, 0, 0, 0, 0);
    phantom_route0->value = 0;

    Route *phantom_route1 = new Route(P, -1, T, T, -1, -1);

    routes[P].push_back(phantom_route1);

    for(int i=0; i<N; ++i){
        sort(routes[i].begin(), routes[i].end(), compare_by_a);
    }

    bfs(phantom_route0);

    cout << phantom_route1->value;

    return 0;


}
