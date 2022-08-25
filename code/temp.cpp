#include<bits/stdc++.h>
using namespace std;


#define DEBUG true
#define RUN false

// N <= 50,000
// Ne[v] = Neighbors of v

const int MAXN = 100*1001;

vector< vector<int> > Ne;

// Number of Vertices
int num_vertices;

// List of leaves
vector<int> L;
int num_leaves;


// Help vectors
// vector< unordered_set<int> > NIL_neighbors;
vector< vector<int> > children;

/*
vector< int > deg0, deg1, degNIL;
vector< bool > taken, in_queue;
*/

int deg0[MAXN], deg1[MAXN], degNIL[MAXN];
bool taken[MAXN], in_queue[MAXN];


template <typename T> void reset_vector(vector<T>& vec){
    vec.clear();
    vec.resize(num_vertices);
}


void set_color(int v, int color, vector<int>& labels){

    assert( labels[v]==-1 );
    labels[v] = color;
    for(auto u: Ne[v]){
        // No longer a NIL neighbor
        degNIL[u] -= 1;
        // NIL_neighbors[u].erase(v);

        if(color == 0) deg0[u]++;
        else deg1[u]++;
    }
}

void propagate(int v, int color, vector<int>& labels, queue<int>& to_process){

    stack<int> to_set;
    to_set.push(v);

    while( !to_set.empty() ){
        int u = to_set.top(); to_set.pop();

        set_color(u, color, labels);
        for(auto w: Ne[u]){
            if( labels[w]==-1 && !in_queue[w]){
                to_process.push(w);
                in_queue[w] = true;
            }
        }
        for(auto w: children[u]) to_set.push(w);
    }
}

void minCostColoring(vector<int>& labels){

    // reset_vector(NIL_neighbors);
    reset_vector(children);

    memset(in_queue, false, sizeof(in_queue));
    memset(taken, false, sizeof(taken));
    memset(deg0, 0, sizeof(deg0));
    memset(deg1, 0, sizeof(deg1));
    memset(degNIL, 0, sizeof(degNIL));

    for(int v=0; v<num_vertices; ++v){
        for(auto u: Ne[v]){
            if(labels[u] == 0) deg0[v]++;
            if(labels[u] == 1) deg1[v]++;
            if(labels[u] == -1){
                degNIL[v]++;
            }
        }
    }

    queue<int> to_process;
    for(auto l: L){
        for(auto v : Ne[l]){
            if( labels[v]==-1 && !in_queue[v]){
                to_process.push(v);
                in_queue[v] = true;
            }
        }
    }

    while( !to_process.empty() ){
        int v = to_process.front();
        to_process.pop();
        in_queue[v] = false;

        // CHECK IF THIS IS CORRECT
        if(labels[v] != -1) continue;

        if(deg0[v] >= deg1[v]+degNIL[v]){
            propagate(v,0,labels,to_process);
        }
        else if(deg1[v] >= deg0[v]+degNIL[v]){
            propagate(v,1,labels,to_process);
        }
        // If nothing worked, v is still NIL
        else if(degNIL[v] == 1 && !taken[v]){
            for(auto u: Ne[v]){
                if( labels[u]==-1 && !taken[u] ){
                    children[u].push_back(v);
                    degNIL[u] -= 1;


                    if( !in_queue[u] ){
                        to_process.push(u);
                        in_queue[u] = true;
                    }

                    taken[v] = true;

                    break;
                }
            }
        }
    }
}

long long costColoring(const vector<int>& labels){
    long long cost = 0;
    for(int v=0; v<num_vertices; ++v){
        assert(labels[v]!=-1);
        for(auto u: Ne[v]){
            if(labels[v] != labels[u]) cost++;
        }
    }
    assert(cost%2==0);
    return cost/2;
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

#if DEBUG

    srand( time(0) );

    int PROB1 = 2;
    int MAXEDGES = 2;

    num_vertices = 50*1000;
    Ne.resize(num_vertices);

    int to_insert = 2;

    queue<int> q;
    q.push(1);

    while( to_insert <= num_vertices ){

        assert( !q.empty());

        int v = q.front(); q.pop();

        int d = 1 + (rand()%MAXEDGES);
        d = min(d, 1+num_vertices-to_insert);

        for(int i=0; i<d; ++i){
            Ne[v-1].push_back(to_insert-1);
            Ne[to_insert-1].push_back(v-1);

            q.push(to_insert);
            to_insert++;
        }
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();


    vector<vector<int>> char_labels(26);
    for(int i=0; i<26; ++i){
        char_labels[i].resize(num_vertices);
        fill(char_labels[i].begin(), char_labels[i].end(), -1);
    }

    num_leaves = 0;
    for(int v=0; v<num_vertices; ++v ){
        if( Ne[v-1].size()==1 ){
            L.push_back(v-1); num_leaves++;

            for(int j=0; j<26; ++j){
                char_labels[j][v-1] = (rand()%PROB1 == 1) ? 1:0;
            }
        }
    }


    long long result = 0;
    for(int i=0; i<26; ++i){
        minCostColoring(char_labels[i]);
        result += costColoring(char_labels[i]);
    }

    cout << result << "\n";

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << endl;

    return 0;

#endif // DEBUG

#if RUN

    cin >> num_vertices >> num_leaves;
    Ne.resize(num_vertices);

    vector<vector<int>> char_labels(26);
    for(int i=0; i<26; ++i){
        char_labels[i].resize(num_vertices);
        fill(char_labels[i].begin(), char_labels[i].end(), -1);
    }

    int x,y;
    string leaf_label;

    for(int i=0; i<num_vertices-1; ++i){
        cin >> x >> y;
        // 0-indexed
        Ne[x-1].push_back(y-1);
        Ne[y-1].push_back(x-1);
    }

    for(int i=0; i<num_leaves; ++i){

        cin >> x;
        cin >> leaf_label;
        // push to the leaves list
        L.push_back(x-1);

        for(int j=0; j<26; ++j){
            char_labels[j][x-1] = 0;
        }
        for(char ch:leaf_label){
            if(ch == '$') break;
            char_labels[ch-'A'][x-1] = 1;
        }
    }

    long long result = 0;
    for(int i=0; i<26; ++i){
        minCostColoring(char_labels[i]);
        result += costColoring(char_labels[i]);
    }

    cout << result;

    return 0;

#endif // RUN
}

