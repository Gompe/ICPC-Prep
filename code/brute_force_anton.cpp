#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
#include<string>
#include<mem.h>

using namespace std;

vector<int> p;

string a;
int q[4];

long long best = -1;
vector<int> best_p;

int code(char ch){
    if(ch=='A')
        return 0;
    if(ch=='N')
        return 1;
    if(ch=='T')
        return 2;
    if(ch=='O')
        return 3;
}

char rcode(int cd){
    if(cd==0)
        return 'A';
    if(cd==1)
        return 'N';
    if(cd==2)
        return 'T';
    if(cd==3)
        return 'O';
}

void process(){

    /*
    p is the permutation
    1 3 2 0 means the order of the letters
    is NN...OO...TTT...A
    */

    int v[4];
    for(int i=0; i<4; ++i)
        v[i]=q[i];

    long long cost = 0;

    for(char ch:a){
        int cd = code(ch);
        --v[cd];
        int it = 0;
        while(p[it] != cd){
            cost += v[p[it]];
            ++it;
        }
    }

    if(cost > best){
        best_p = p;
        best = cost;
    }

    //printf("permutation: %d %d %d %d, cost = %d \n", p[0], p[1], p[2], p[3], cost);

}

void print_best(){
    for(int i=0; i<4; ++i){
        for(int j=0; j<q[best_p[i]]; ++j)
            printf("%c", rcode(best_p[i]));
    }
    printf("\n");
    //printf("\nbest = %d \n", best);
}

void perms( set<int> st = {0,1,2,3} ){

    if(st.empty()){
        process();
        return;
    }

    set<int> aux_st = st;
    for(set<int>::iterator it = st.begin(); it!=st.end(); ++it){

        int e = *it;

        p.push_back(e);
        aux_st.erase(e);

        perms(aux_st);

        p.pop_back();
        aux_st.insert(e);
    }

}

int main(){
    int t;
    scanf("%d", &t);

    for(int i=0; i<t; ++i){
        cin >> a;

        memset(q, 0, sizeof(q));
        best = -1;

        for(char ch:a)
            ++q[code(ch)];

        perms();
        print_best();
    }

    return 0;
}
