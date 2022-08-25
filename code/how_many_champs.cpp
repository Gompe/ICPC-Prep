#include<bits/stdc++.h>
using namespace std;

long long N, T;

vector< pair<long long, long long> > stats;
vector<long long> champions;
vector<long long> times;

void POP(){
    champions.pop_back();
    times.pop_back();
}

void PUSH(long long i, long long time){
    champions.push_back(i);
    times.push_back(time);
}

int main(){

    scanf("%lld %lld", &N, &T);

    stats.resize(N);

    for(int i=0; i<N; ++i){
        scanf("%lld %lld", &stats[i].first, &stats[i].second);
    }

    sort(stats.begin(), stats.end());
    reverse(stats.begin(), stats.end());

    // ====================

    PUSH(0, 0);

    for(int i=1; i<N; ++i){

        int curr = champions.back();

        if( stats[i].second < stats[curr].second ) continue;

        if( stats[i] == stats[curr]){
            PUSH(i, times.back());
            continue;
        }

        while(1){

            curr = champions.back();

            long long time_num = stats[curr].first - stats[i].first;
            long long time_den = stats[i].second - stats[curr].second;
            // i beats curr at time ... time_num/time_den ...

            long long int_time = (time_num - (time_num%time_den))/time_den;
            int_time += (time_num%time_den == 0) ? 0 : 1;

            if( T < int_time ) break;

            if( times.back() > int_time ){
                POP();
                continue;
            }

            if( (times.back() == int_time) && (time_num%time_den != 0) ){
                POP();
                continue;
            }

            PUSH(i, int_time);
            break;
        }
    }

    printf("%lld\n", (long long) champions.size());

    return 0;
}
