#include<bits/stdc++.h>

using namespace std;

using ld = long double;

const int maxN = 25;
const ld eps = 1e-15;
ld PI_2 = acos(0);

struct Point{

    ld x, y, z;

    Point(ld tx,ld ty,ld tz){
        x=tx;
        y=ty;
        z=tz;
    }

    ld square_norm(){
        return x*x+y*y+z*z;
    }

    void normalize(){
        const ld magnitude = sqrt(x*x+y*y+z*z);
        x = (ld) x/magnitude;
        y = (ld) y/magnitude;
        z = (ld) z/magnitude;
    }

    void antipode(){
        x=-x;
        y=-y;
        z=-z;
    }

};

vector<Point> st;
ld minr = 0;

Point cross(Point a, Point b){
    return Point( (ld) a.y*b.z-b.y*a.z, (ld) a.z*b.x-a.x*b.z, (ld) a.x*b.y-b.x*a.y );
}

ld dot(Point a, Point b){
    return (ld) a.x*b.x+a.y*b.y+a.z*b.z;
}

Point sumP(Point a, Point b){
    return Point( (ld) a.x+b.x, (ld) a.y+b.y, (ld) a.z+b.z );
}

ld sphereDist(Point a, Point b){
    //assumes a and b are normalized
    return acos( dot(a,b) );
}

Point angle_to_Point( ld phi, ld theta ){
    return Point( (ld) cos(phi)*cos(theta), (ld) cos(phi)*sin(theta), (ld) sin(phi) );
}

void update(Point p){
    ld rhere = 100;
    for(Point q:st){
        rhere = min(rhere, sphereDist(q, p));
    }
    minr = max(rhere, minr);
}

void process(Point p){

    if(p.square_norm() < eps)
        return;

    p.normalize();
    update(p);

    p.antipode();
    update(p);
}

int main(){

    int N;
    scanf("%d", &N);

    for(int i=0; i<N; ++i){
        ld phi, theta;
        scanf("%Lf %Lf", &phi, &theta);
        phi = (ld) (PI_2)*(phi/90);
        theta = (ld) (2*PI_2)*(theta/180);

        st.push_back( angle_to_Point(phi, theta) );
    }

    for(int i=0; i<N; ++i){
        Point station = st[i];
        process(station);
        process(cross(station, Point(rand(), rand(), rand())));
    }


    for(int i=0; i<N; ++i){
        for(int j=i+1; j<N; ++j){
            Point midpoint_stations = sumP(st[i], st[j]);

            process(midpoint_stations);
            process(cross(midpoint_stations, Point(rand(), rand(), rand())));
        }
    }

    for(int i=0; i<N; ++i){
        Point u = st[i];

        for(int j=0; j<N; ++j){
            if(i == j) continue;
            Point v = st[j];
            v.antipode();

            for(int k=j+1; k<N; ++k){
                if(k==i) continue;
                Point w = st[k];
                w.antipode();
                process( cross(sumP(u,v), sumP(u,w)) );

                process( cross(sumP(u,v), Point(rand(), rand(), rand())) );
                process( cross(sumP(u,w), Point(rand(), rand(), rand())) );

            }
        }
    }


    printf("%.6Lf\n", minr);
    return 0;
}
