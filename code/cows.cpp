#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

#define INF 1000001

struct pt{
    double x, y;
};

double dist(pt pt1,pt pt2){
    return sqrt( pow(pt1.x-pt2.x, 2) + pow(pt1.y-pt2.y, 2) );
}

bool cmp(pt pt1, pt pt2){
    return pt1.x < pt2.x || (pt1.x == pt2.x && pt1.y < pt2.y);
}

bool cw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull(vector<pt>& a, vector<pt>& CH){

    CH.clear();

    if( a.size() == 1 ){
        CH.push_back(a[0]);
        return;
    }

    sort(a.begin(), a.end(), &cmp);

    vector<pt> up, down;

    pt p1 = a[0], p2 = a.back();

    up.push_back(p1);
    down.push_back(p1);

    for (int i = 1; i < (int)a.size(); i++) {
        if (i == a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    for (int i = 0; i < (int)up.size(); i++)
        CH.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        CH.push_back(down[i]);
}

double convex_hull_cost(vector<pt>& a){
    vector<pt> CH;
    convex_hull(a, CH);

    CH.push_back(CH[0]);

    double p = 0;

    /*
    for(int i=0; i<CH.size(); i++){
        printf("%.2lf %.2lf \n", CH[i].x, CH[i].y);
    }
    */

    for(int i=1; i<CH.size(); i++){
        p += dist(CH[i-1], CH[i]);
    }

    return p;

}

int main(){
    int N;

    scanf("%d", &N);

    vector<pt> p;

/*
    pt a;
    a.x = -1000000, a.y = 1000000;
    p.push_back(a);
    pt b;
    b.x = -1000000, b.y = -1000000;
    p.push_back(b);
    pt c;
    c.x = 1000000, c.y = 1000000;
    p.push_back(c);
    pt d;
    d.x = 1000000, d.y = -1000000;
    p.push_back(d);
*/

    for( int i=0; i<N; i++){
        pt a;
        scanf("%lf %lf", &a.x, &a.y);
        p.push_back(a);
    }


    printf("%.2lf", convex_hull_cost(p));

    return 0;
}
