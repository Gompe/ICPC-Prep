#include <iostream>
#include <algorithm>
#include <mem.h>

using namespace std;

int dp[70][70][70][70];

int main(){
    memset(dp, -1, sizeof(dp));

    int loops = 0;
    for(int i1=0; i1<70; ++i1){
        for(int i2=0; i2<70; ++i2){
        for(int i3=0; i3<70; ++i3){
                for(int i4=0; i4<70; ++i4){
                    dp[i1][i2][i3][i4] = 7;
                    ++loops;

    }

    }
    }
    }

    printf("loops = %d", loops);
    return 0;
}
