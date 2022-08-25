#include<bits/stdc++.h>
using namespace std;

class RollingMedian {

public:

multiset<long long> order;
multiset<long long>::iterator it;

RollingMedian() {
}

~RollingMedian(){
}

RollingMedian(long long x){
    add(x);
}

int num_elements(){
    return order.size();
}

void add(long long val) {
    order.insert(val);
    if (order.size() == 1) {
        it = order.begin();
    } else {
        if (val < *it and order.size() % 2 == 0) {
            --it;
        }
        if (val >= *it and order.size() % 2 != 0) {
            ++it;
        }
    }
}

long long twice_median() {

    if (order.size() % 2 != 0) {
        return 2*(*it);
    }

    else {
        auto one = *it, two = *next(it);
        return one + two;
    }
}
};


const int MAXN = 1000*1000;
int N;

long long t[MAXN];
long long z[MAXN];

vector< RollingMedian* > blocks;

void Merge(RollingMedian* &r1, RollingMedian* &r2){

    if( r1->num_elements() < r2->num_elements() ){
        swap(r1,r2);
    }

    for( multiset<long long>::iterator it = (r2->order).begin(); it != (r2->order).end(); ++it ){
        r1->add(*it);
    }

}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);


    /*

    cin >> N;
    for(int i=0; i<N; ++i){
        cin >> t[i];
        t[i] -= i;
    }

    */

    /** --- **/
    std::random_device dev;
    std::mt19937 rng(dev());

    rng.seed(time(0));

    std::uniform_int_distribution<std::mt19937::result_type> distr(0, 1000*1000*1000);
    /** --- **/

    N = 1000*1000;
    for(int i=0; i<N; ++i){
        t[i] = distr(rng) - i;
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();


    for(int i=0; i<N; ++i){

        RollingMedian *r = new RollingMedian(t[i]);
        blocks.push_back(r);

        while( (blocks.size() > 1) &&
               (blocks[blocks.size()-1]->twice_median() <= blocks[blocks.size()-2]->twice_median())
              ){

            // Merge the two blocks
            RollingMedian *r1 = blocks[blocks.size()-1];
            RollingMedian *r2 = blocks[blocks.size()-2];

            blocks.pop_back();
            blocks.pop_back();

            Merge(r1, r2);

            blocks.push_back(r1);
            delete r2;
        }

    }

    int i = 0;
    int idx = 0;

    while( i < N ){
        fill( z + i, z + i + blocks[idx]->num_elements(), (long long) (blocks[idx]->twice_median())>>1 );
        i += blocks[idx]->num_elements();
        idx++;
    }

    long long result = 0;
    for(int ii=0; ii<N; ++ii){
        result += abs(z[ii] - t[ii]);
    }

    cout << result << "\n";

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << endl;

    return 0;
}
