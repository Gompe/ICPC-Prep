#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>

using namespace std;

struct point{
    int z;
    int type;

    point(){}

    point(int z0, int type0){
        z = z0;
        type = type0;
    }
};

bool operator< (point p1, point p2){
    if(p1.z!=p2.z)
        return p1.z < p2.z;
    return p1.type<p2.type;
}

long long cnt(point* a, int n){
    long long ip = 0;
    int cc = 0;

    for(int i=0; i<n; ++i){
        if(a[i].type == 0){
            ip += (cc*(cc-1))/2;
            cc = 0;
        }
        else{
            cc++;
        }
    }
    return ip;
}

int main(){
    int t;
    scanf("%d", &t);

    for(int i=0; i<t; ++i){
        int n,m,k;
        scanf("%d %d %d", &n, &m, &k);

        vector<point> X0, X1, Y0, Y1;
        unordered_set<int> x_roads, y_roads;
        int x, y;

        for(int j=0; j<n; ++j){
            scanf("%d", &x);
            X0.push_back( point(x, 0) );
            x_roads.insert(x);
        }
        for(int j=0; j<m; ++j){
            scanf("%d", &y);
            Y0.push_back( point(y, 0) );
            y_roads.insert(y);
        }

        for(int j=0; j<k; ++j){
            scanf("%d %d", &x, &y);
            if( x_roads.count(x) == 0 )
                X1.push_back( point(x,1) );
            if( y_roads.count(y) == 0 )
                Y1.push_back( point(y, 1) );
        }
        sort(X1.begin(), X1.end());
        sort(Y1.begin(), Y1.end());

        point X[X0.size()+X1.size()];
        point Y[Y0.size()+Y1.size()];

        merge(X0.begin(), X0.end(), X1.begin(), X1.end(), X);
        merge(Y0.begin(), Y0.end(), Y1.begin(), Y1.end(), Y);

        cout << "X: ";
        for(point pt:X){
            cout<< pt.z << " ";
        }
        cout << "\n" << "Y: ";
        for(point pt:Y){
            cout<< pt.z << " ";
        }
        cout<<"\n";

        long long ip = 0;
        ip += cnt(X, X0.size()+X1.size());
        ip += cnt(Y, Y0.size()+Y1.size());

        printf("TEST CASE %d : %lld\n", i, ip);
    }

    return 0;
}

