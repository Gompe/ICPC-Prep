#include <iostream>
#include <algorithm>

using namespace std;

int cell[520][520] = { };
int table[520][520][10];
int log2_tab[520];

int max4(int a, int b, int c, int d){
    return max(max(a,b), max(c,d));
}

void process(int N){
    for( int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            table[i][j][0] = cell[i][j];
        }
    }

    int p=1;
    int i1, j1;

    for (int l=1; l<= log2_tab[N]; l++, p*=2){
        for (int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                i1 = max( i, min(i+p, N-p) );
                j1 = max( j, min(j+p, N-p) );
                table[i][j][l] = max4(table[i][j][l-1],
                                     table[i1][j][l-1],
                                     table[i][j1][l-1],
                                     table[i1][j1][l-1]);
            }
        }
    }
}

void computelog(){
    int p=1;
    int n=1;
    for(int l=0; l<9; l++){

        while(n < 2*p){
            log2_tab[n] = l;
            n++;
        }
        p *= 2;
    }
}

int pow_2(int l){
    return 1<<l;
}

int main(){

    /*
    ios::sync_with_stdio(0);
    cin.tie(0);
    */

    int N, Q, M;
    cin >> N >> Q >> M;

    int I1, I2, J1, J2;
    int c;

    for (int i=0; i<M; i++){
        cin >> I1 >> J1 >> I2 >> J2;
        for (int j=0; j<=I2-I1; j++){
            for (int k=0; k<=J2-J1; k++){
                cin >> c; // The cell [I1+j][J1+k]
                cell[I1+j-1][J1+k-1] += c; // -1 to be 0-indexed
            }
        }

    }

    // Now we do the sparse table
    computelog();
    process(N);

    int I,J,S;
    int l, p, m;
    int ans[Q];

    for(int i=0; i<Q; i++){
        cin >> I >> J >> S;
        I--, J--; // 0-indexed

        l = log2_tab[S];
        p = pow_2(l);

        m = max4(table[I][J][l],
                table[I+S-p][J][l],
                table[I][J+S-p][l],
                table[I+S-p][J+S-p][l]);

        ans[i] = m;
    }

    for (int i=0; i<Q; i++){
        cout<< ans[i]<<"\n";
    }

    return 0;

}
