#include<bits/stdc++.h>
using namespace std;

const long double eps = 1e-15;
const long double PI  = 2*acos(0);


/** struct Point declaration **/

struct Point{
    long double x,y,z;

    Point(long double x, long double y, long double z);
    Point(long double phi, long double theta);

    long double square_norm() const;
    void normalize();
    Point antipode() const;

    Point operator+(const Point& other);
    Point operator-(const Point& other);
};

Point::Point(long double x, long double y, long double z){
    this->x = x;
    this->y = y;
    this->z = z;

    normalize();
}

Point::Point(long double phi, long double theta){

    phi = PI*phi/180.;
    theta = PI*theta/180.;

    x = cos(phi)*cos(theta);
    y = cos(phi)*sin(theta);
    z = sin(phi);
}

long double Point::square_norm() const{
    return x*x+y*y+z*z;
}

void Point::normalize(){
    const long double norm = sqrt(square_norm());

    if(norm < eps){
        x = y = z = 0;
    }
    else{
        x = x/norm;
        y = y/norm;
        z = z/norm;
    }
}

Point Point::antipode() const{
    return Point(-x,-y,-z);
}

Point Point::operator+(const Point& other){
    return Point(x+other.x,
                 y+other.y,
                 z+other.z);
}

Point Point::operator-(const Point& other){
    return (*this) + (other.antipode());
}

/** end struct Point **/

vector<Point> stations;
long double max_radius = 0;

Point cross(const Point& a, const Point& b){
    return Point(a.y*b.z-b.y*a.z,
                 a.z*b.x-b.z*a.x,
                 a.x*b.y-b.x*a.y);
}

long double dot(const Point& a, const Point& b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

long double sphere_distance(const Point& a, const Point& b){
    // Assumes a,b are normalized
    return acos(dot(a,b));
}

void update(const Point& p){
    long double min_radius = 6.30;
    for(const Point& q : stations){
        min_radius = min(min_radius, sphere_distance(p, q));
    }

    max_radius = max(min_radius, max_radius);
}

void process_point(Point p){
    if(p.square_norm() < eps){ return; }

    p.normalize();
    update(p);
    update(p.antipode());
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    long double phi, theta;
    for(int i=0; i<N; ++i){
        cin >> phi >> theta;
        stations.push_back(Point(phi, theta));
    }

    for(int i=0; i<N; ++i){
        process_point(stations[i]);

        process_point(Point(-stations[i].y-stations[i].z,
                            stations[i].x,
                            stations[i].x));

        process_point(Point(stations[i].y,
                            -stations[i].x-stations[i].z,
                            stations[i].y));

        process_point(Point(stations[i].z,
                            stations[i].z,
                            -stations[i].x-stations[i].y));
    }

    for(int i=0; i<N; ++i){
        for(int j=i+1; j<N; ++j){
            process_point(stations[i]+stations[j]);
        }
    }

    for(int i=0; i<N; ++i){
        for(int j=i+1; j<N; ++j){
            for(int k=j+1; k<N; ++k){
                process_point(cross(stations[i]-stations[j],
                                    stations[i]-stations[k]));

                process_point(cross(stations[j]-stations[k],
                                    stations[j]-stations[i]));

                process_point(cross(stations[k]-stations[i],
                                    stations[k]-stations[j]));
            }
        }
    }

    printf("%.6Lf\n", max_radius);
    return 0;
}

/*

4
59 30
53 83
41 69
41 41

*/

