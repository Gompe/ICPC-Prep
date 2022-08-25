#include<iostream>
#include<vector>

using namespace std;

const int nmax = 100+2e5;
bool a[nmax];

void NOT_SOLVABLE(){
    //printf("==========\n");

    printf("NO\n");

    //printf("==========\n");
};

void PRINT_SOLUTION(vector<int>& ops){
    //printf("==========\n");


    printf("YES\n");
    printf("%d\n", ops.size());
    for(int pos:ops){
        printf("%d ", pos+1);
    }

    if(ops.size())
        printf("\n");

    //printf("==========\n");
}

void solve_from_0(int mk, int n, vector<int>& ops){
    int pos = mk;
    // traverse left
    while(pos > 0){
        if( !a[pos-1] ){
            pos--;
            continue;
        }
        if( a[pos-2] ){
            a[pos-2] = a[pos-1] = false;
            ops.push_back(pos-2);
            pos = pos-2;
        }
        else{
            bool res = a[pos-3]^a[pos-2]^a[pos-1];
            a[pos-3] = a[pos-2] = a[pos-1] = res;
            ops.push_back(pos-3);
            if( !res ){
                pos = pos-3;
            }
            else{
                a[pos-2] = a[pos-1] = false;
                ops.push_back(pos-2);
                pos = pos-2;
            }
        }
    }
    pos = mk;
    //traverse right
    while(pos <= n-3){
        if( !a[pos+1] ){
            pos++;
            continue;
        }
        if( a[pos+2] ){
            a[pos+2] = a[pos+1] = false;
            ops.push_back(pos);
            pos = pos+2;
        }
        else{
            bool res = a[pos+3]^a[pos+2]^a[pos+1];
            a[pos+3] = a[pos+2] = a[pos+1] = res;
            ops.push_back(pos+1);
            if( !res ){
                pos = pos+3;
            }
            else{
                a[pos+2] = a[pos+1] = false;
                ops.push_back(pos);
                pos = pos+2;
            }
        }
    }
    PRINT_SOLUTION(ops);
}

void solve_from_1(int mk, int n){
    vector<int> ops;
    int pos = mk;

    while( !a[pos-2] ){
        a[pos-2] = a[pos-1] = true;
        ops.push_back(pos-2);
        pos = pos-2;
    }
    ops.push_back(pos-2);
    a[pos-2] = a[pos-1] = a[pos] = 0;
    solve_from_0(pos, n, ops);
}

void solve(int n){
    int num0s = 0;
    int num1s = 0;
    int marker0 = -1;
    int marker1 = -1;

    for(int i=0; i<n; ++i){
        if(a[i]){
            num1s++;
            if(num0s%2 == 1 && marker1==-1)
                marker1 = i;
        }
        else{
            num0s++;
            if(num1s%2==0 && marker0==-1)
                marker0 = i;
        }
    }

    if(num1s%2==1){
        NOT_SOLVABLE();
        return;
    }

    if(marker0 == -1 && marker1 == -1){
        NOT_SOLVABLE();
        return;
    }

    if(marker0 != -1){
        vector<int> ops;
        solve_from_0(marker0, n, ops);
        return;
    }

    solve_from_1(marker1, n);
}

void read_array(int n){
    int b;
    for(int i=0; i<n; ++i){
        scanf("%d", &b);
        a[i] = b ? 1:0;
    }
}

int main(){
    int t, n;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        read_array(n);
        solve(n);
    }
    return 0;
}
