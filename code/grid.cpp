#include<bits/stdc++.h>
using namespace std;

#define DEBUG false
#define RUN true

int R, C;
char grid[10001][76];

// int alphas[10001], betas[76];
// int z[10001];

const long long m = 1000*1000*1000+7;
const long long p = 53;

long long row_table[10001], col_table[76];
long long powers[10001];

int zR[10001], zC[76];

inline void make_powers(){
    powers[0] = 1;
    for(int i=1; i<10001; ++i){
        powers[i] = p*powers[i-1]%m;
    }

}

/*
inline void z_information(int type, int index){

    memset(z, 0, sizeof(z));

    if(type == 0){
        // look at grid[index][:]
        int n = C;

        for(int i=1, l=0, r=0; i<n; ++i){
            if(i<=r){
                z[i] = min (r-i+1, z[i-l]);
            }
            while (i+z[i]<n && grid[index][z[i]] == grid[index][i+z[i]]){
                ++z[i];
            }
            if(i+z[i]-1>r){
                l = i, r = i+z[i]-1;
            }
            if( i+z[i]==n ){
                betas[i]++;
            }
        }
    }
    else{
        // look at grid[:][index]
        int n = R;

        for(int i=1, l=0, r=0; i<n; ++i){
            if(i<=r){
                z[i] = min (r-i+1, z[i-l]);
            }
            while (i+z[i]<n && grid[z[i]][index] == grid[i+z[i]][index]){
                ++z[i];
            }
            if(i+z[i]-1>r){
                l = i, r = i+z[i]-1;
            }
            if( i+z[i]==n ){
                alphas[i]++;
            }
        }
    }
}

int solution(){

    for(int i=0; i<C; ++i){
        z_information(1,i);
    }

    for(int i=0; i<R; ++i){
        z_information(0, i);
    }

    int alpha = R, beta = C;
    for(int i=0; i<R; ++i){
        if(alphas[i] == C){
            alpha = i;
            break;
        }
    }
    for(int i=0; i<C; ++i){
        if(betas[i] == R){
            beta = i;
            break;
        }
    }

    // cout << " ALPHA: " << alpha << " BETA: "<<beta<< "\n";

    return alpha*beta;
}

*/

int solution2(){

    int alpha = R, beta = C;

    int n = R;
    for(int i=1, l=0, r=0; i<n; ++i){
        if(i<=r){
            zR[i] = min (r-i+1, zR[i-l]);
        }
        while (i+zR[i]<n && row_table[zR[i]] == row_table[i+zR[i]]){
            ++zR[i];
        }
        if(i+zR[i]-1>r){
            l = i, r = i+zR[i]-1;
        }
        if( i+zR[i]==n ){
            alpha = i;
            break;
        }
    }

    n = C;
    for(int i=1, l=0, r=0; i<n; ++i){
        if(i<=r){
            zC[i] = min (r-i+1, zC[i-l]);
        }
        while (i+zC[i]<n && col_table[zC[i]] == col_table[i+zC[i]]){
            ++zC[i];
        }
        if(i+zC[i]-1>r){
            l = i, r = i+zC[i]-1;
        }
        if( i+zC[i]==n ){
            beta = i;
            break;
        }
    }

    //cout << "before returning: " << alpha << " " << beta << endl;

    return alpha*beta;

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);


#if DEBUG

    srand(time(0));

    R = 10000;
    C = 75;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();


    make_powers();

    for(int i=0; i<R; ++i){
        for(int j=0; j<C; ++j){
            grid[i][j] = 'A';
            if( rand()%1500 == 1)
                grid[i][j] = 'B';

            row_table[i] += (1+grid[i][j]-'A')*powers[j];
            col_table[j] += (1+grid[i][j]-'A')*powers[i];

            row_table[i]%=m;
            col_table[j]%=m;
        }
    }
    cout << solution2() << "\n";

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << endl;

#endif // DEBUG

#if RUN

    make_powers();

    cin >> R >> C;
    for(int i=0; i<R; ++i){
        for(int j=0; j<C; ++j){
            cin >> grid[i][j]; //Uppercase char

            row_table[i] += (1+grid[i][j]-'A')*powers[j];
            col_table[j] += (1+grid[i][j]-'A')*powers[i];

            row_table[i]%=m;
            col_table[j]%=m;
        }
    }

    cout << solution2();
#endif // RUN


    return 0;
}

