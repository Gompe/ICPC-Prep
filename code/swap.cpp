#include <iostream>
#include <algorithm>

using namespace std;

void sort_triplet(int *c1, int *c2, int *c3){
    int a1, a2, a3;
    a1 = min( {*c1, *c2, *c3} );
    a3 = max( {*c1, *c2, *c3} );
    a2 = *c1+ *c2+ *c3 - a1-a2;

    *c1 = a1;
    *c2 = a2;
    *c3 = a3;
}

int main(){

    int a,b,c;
    cin >>a>>b>>c;

    sort_triplet(&a,&b,&c);

    cout <<a<<b<<c;

    return 0;
}
