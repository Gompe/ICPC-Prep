#include <iostream>

using namespace std;

#pragma comment(linker, "/STACK:2000000")

void f(int n){
    int x;
    x = x+1;
    if(n==0)
        return;
    return f(n-1);
}

int main(){
    f(3*1e5);
    printf("DONE");
    return 0;
}
