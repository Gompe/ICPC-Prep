#include<bits/stdc++.h>

using namespace std;

const int maxn = 200100;
const int maxm = 400200;

int p[maxn];
int tin[maxn];

void set_representative(int a){
    stack<int> st;
    st.push(a);

    while( p[st.top()] != st.top() )
        st.push( p[st.top()] );

    int rep = st.top();
    int t = -1;

    while( !st.empty() ){

        if(tin[st.top()] == -1)
            tin[st.top()] = t;
        t = tin[st.top()];

        p[ st.top() ] = rep;
        st.pop();
    }
}

void combine(int a, int b, int t){
    if(a==-1 || b==-1)
        return;

    set_representative(a);
    set_representative(b);

    a = p[a];
    b = p[b];

    if(b<a) swap(a,b);

    p[b] = a;
    if(a==1 && b!=1)
        tin[b] = t;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);

    // -- read input --
    int l[n+1], r[n+1];
    for(int i=1; i<=n; ++i){
        scanf("%d %d", &l[i], &r[i]); // left and right
    }

    int ra[m][2]; //reversed observations
    for(int i=0; i<m; ++i){
        int monkey, action;
        scanf("%d %d", &monkey, &action);
        ra[i][0] = monkey;
        if(action == 1){
            //left
            ra[i][1] = l[monkey];
            l[monkey] = -1;
        }
        else{
            //right
            ra[i][1] = r[monkey];
            r[monkey] = -1;
        }
    }

    // -- sets the union find structure --
    memset(tin, -1, sizeof(tin));
    for(int i=1; i<=n; ++i)
        p[i] = i;

    for(int i=1; i<=n; ++i){
         combine(i, l[i], -1);
         combine(i, r[i], -1);
    }

    for(int i=m-1; i>=0; --i){
        combine(ra[i][0], ra[i][1], i);
    }


    // -- prints the result --
    for(int i=1; i<=n; ++i)
        set_representative(i);

    for(int i=1; i<=n; ++i)
        printf("%d\n", tin[i]);

    return 0;
}
