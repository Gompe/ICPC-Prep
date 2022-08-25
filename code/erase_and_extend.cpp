#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    int n, k;
    scanf("%d %d", &n, &k);

    string s;
    cin >> s;

    int len = 0;
    int last = 1;
    int cut = n;

    while(last < n){
        if( s[last] > s[len] ){
            cut = last-len;
            break;
        }
        else if( s[last] < s[len] ){
            len = 0;
        }
        else{
            ++len;
        }
        ++last;
    }

    if(last==n && len!=0){
        cut = n-len;
    }

    char t[k];
    int it = 0;
    while(it < k){
        t[it] = s[it%cut];
        ++it;
    }

    for(char c: t)
        printf("%c", c);
    printf("\n");

    return 0;
}
