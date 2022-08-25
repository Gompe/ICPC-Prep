#include<bits/stdc++.h>
using namespace std;

#define run false
#define timeit true

const int MAXN = 50010, MAXM = 100010;
int N, M, P, T;

int NUM_ITER = 0;

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
            return r1->value < r2->value;
        }
    };
};

vector< vector< Route* > > routes;
vector< Route* > route_list;

void bfs(Route *initial_route){

    // priority_queue< pair<int, int> > to_process;
    queue< pair<int, int> > to_process;

    to_process.push( {0, -(initial_route->index)} );

    while( !to_process.empty() ){
        NUM_ITER++;

        //int index = - to_process.top().second;
        int index = - to_process.front().second;

        Route *curr = route_list[index];
        to_process.pop();

        if(curr->destination == -1){
            continue;
        }

        for(auto& next : routes[curr->destination]){
            if(next->a >= curr->d){
                // we can go from route to next_route
                if( next->update(curr->value + next->b - curr->c) ){
                    to_process.push( {-(next->value), -(next->index)} );
                }
            }
        }
    }
}

void dfs(Route *route){

    if(route->destination == -1) return;

    for(auto next_route : routes[route->destination]){
        if(next_route->a >= route->d){
            // we can go from route to next_route
            if( next_route->update(route->value + next_route->b - route->c) ){
                dfs(next_route);
            }
        }
    }
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

#if timeit


    N = 250;
    M = 100*1000;

    T = 100;
    P = 1;

    routes.resize(N);
    route_list.resize(M+2);

    Route *phantom_route0 = new Route(-1, 0, 0, 0, 0, 0);
    phantom_route0->value = 0;
    phantom_route0->index = 0;

    Route *phantom_route1 = new Route(P, -1, T, T, -1, -1);
    phantom_route1->index = 1;

    routes[P].push_back(phantom_route1);

    route_list[0] = phantom_route0;
    route_list[1] = phantom_route1;

    /** --- **/
    std::random_device dev;
    std::mt19937 rng(dev());

    rng.seed(time(0));

    std::uniform_int_distribution<std::mt19937::result_type> distr(0,N-1);
    /** --- **/

    for(int i=0; i<M; ++i){

        int s,t;
        int a,b,c,d;

        s = distr(rng);
        t = distr(rng);

        // if( i < 15 ) cout << s << " " << t << endl;

        a = b = c = d = 0;

        Route *new_route = new Route(s,t,a,b,c,d);
        new_route->index = i+2;
        route_list[i+2] = new_route;

        routes[s].push_back(new_route);
    }


    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    bfs(phantom_route0);

    cout << phantom_route1->value << " "<< NUM_ITER << "\n";

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << endl;

    return 0;


#endif // debug


#if run
    cin >> N >> M >> P >> T;
    --P;

    routes.resize(N);
    route_list.resize(M+2);

    Route *phantom_route0 = new Route(-1, 0, 0, 0, 0, 0);
    phantom_route0->value = 0;
    phantom_route0->index = 0;

    Route *phantom_route1 = new Route(P, -1, T, T, -1, -1);
    phantom_route1->index = 1;

    routes[P].push_back(phantom_route1);

    route_list[0] = phantom_route0;
    route_list[1] = phantom_route1;

    int s,t;
    int a,b,c,d;

    for(int i=0; i<M; ++i){
        cin >> s >> t;
        s--; t--;

        cin >> a >> b >> c >> d;

        Route *new_route = new Route(s,t,a,b,c,d);
        new_route->index = i+2;
        route_list[i+2] = new_route;

        routes[s].push_back(new_route);
    }

    bfs(phantom_route0);

    cout << phantom_route1->value;

    return 0;

#endif // run

}

/*

3 6 2 100
1 3 10 20 30 40
3 2 32 35 95 95
1 1 1 1 7 8
1 3 8 8 9 9
2 2 98 98 99 99
1 2 0 0 99 101

32


=================

3 2 2 100
1 3 0 0 49 51
3 2 50 51 100 100


-1

*/
