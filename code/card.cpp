#include<iostream>
#include<algorithm>

using namespace std;

struct arrow{
    long double slope;
    bool start;
};

bool operator<(arrow A1, arrow A2){
    if(A1.slope == A2.slope)
        return A1.start && !A2.start;
    return A1.slope > A2.slope;
}

arrow A[21000];

int main(){

    int X,Y;
    int N;
    scanf("%d %d %d", &X, &Y, &N);

    for(int i=0; i<N; ++i){
        int x1,y1,x2,y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        int top_left_index = 2*i;
        int bottom_right_index = 2*i+1;

        A[top_left_index].slope = ( (long double) y2)/( (long double) x1);
        A[top_left_index].start = true;

        A[bottom_right_index].slope = ( (long double) y1)/( (long double) x2);
        A[bottom_right_index].start = false;
    }

    sort(A, A+2*N);

    int max_cut = 0;
    int current_cut = 0;

    for(int i=0; i<2*N; ++i){
        if(A[i].start)
            current_cut+=1;
        else
            current_cut-=1;
        max_cut = max(max_cut, current_cut);
    }

    printf("%d\n", max_cut);

    return 0;
}
