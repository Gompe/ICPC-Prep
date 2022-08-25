#include <bits/stdc++.h>
using namespace std;

long long Xmax, Ymax;
long long integerProjection(long long x, long long y, bool start){
    // Let y1 be the farther vertical side of the Xmax Ymax rect
    // x1 analog for horizontal
    long long slopeSign = y*Xmax - Ymax*x;
    if (slopeSign == 0){
        return Ymax;
    }
    if (slopeSign < 0){
        // integer point before the projection of (x,y) onto y1
        long long intProj = y*Xmax/x;
        int err = 0;

        // if y*Xmax%x!=0, intProj is smaller than it should be
        if(start && (y*Xmax)%x != 0)
            err = 1;

        return intProj + err;
    }
    if (slopeSign > 0){
        // integer point after the projection of (x,y) onto x1
        long long intProj = Xmax - x*Ymax/y + Ymax;
        int err = 0;

        // if x*Ymax%y != 0, intProj is larger than it should be
        if(!start && (x*Ymax)%y != 0)
            err = 1;

        return intProj - err;
    }
    return -1;
}
int main(){
    int n;
    scanf("%lld %lld %d", &Xmax, &Ymax, &n);
    vector < pair<long long,int> > intervals;
    for(int i=0; i<n; ++i){
        long long x0,y0,x1,y1;
        scanf("%lld %lld %lld %lld", &x0, &y0, &x1, &y1);

        intervals.push_back({integerProjection(x1, y0, true), 1});

        intervals.push_back({integerProjection(x0, y1, false) + 1, -1});
    }
    sort(intervals.begin(), intervals.end());
    int cnt = 0, ans = 0;

    for(auto v: intervals){
        cnt += v.second;
        ans = max(ans, cnt);
    }

    printf("%d\n", ans);
    return 0;
}

