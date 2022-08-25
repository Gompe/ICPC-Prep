#include <iostream>
#include <algorithm>
#include <mem.h>

using namespace std;

#define NAX 200100

long long h[NAX];
int n;
int M=0; // This will be the answer

void insertion(long long a){
    if(h[M]+a >= 0)
        ++M;
    for(int i=M; i>max(0, M - (n/2)); --i)
        h[i] = max(h[i], h[i-1]+a);
}

int main(){
    memset(h, -1, sizeof(h));
    h[0] = 0;

    scanf("%d", &n);

    long long a;
    for(int i=0; i<n; ++i){
        scanf("%lld", &a);
        insertion(a);
    }

    printf("%d\n", M);
    return 0;
}
