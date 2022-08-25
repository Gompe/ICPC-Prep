#include<iostream>
#include<set>

using namespace std;

int main(){
    set< pair<int, int> > st;
    st.insert( make_pair(1, 2) );
    st.insert( make_pair(3, 2) );

    for( auto it = st.begin(); it!=st.end(); ++it ){
        printf("(%d, %d) ", (*it).first, (*it).second);
    }
    cout << "\n";
}
