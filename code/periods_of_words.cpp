#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

const int p = 37;
const long long m = 1e9 + 9;

int main(){

    int k; // k <= 1e6
    scanf("%d", &k);

    char s[k]; // lower-case english letters
    scanf("%s", s);

    // power_list[n] = p^n (mod m)
    long long power_list[k];
    power_list[0] = 1;
    for(int i=1; i<k; ++i)
        power_list[i] = p*power_list[i-1]%m;

    long long hash_list[k];
    long long last = 0;

    for(int i=0; i<k; ++i){
        hash_list[i] = (last + power_list[i]*(1+s[i]-'a')%m)%m;
        last = hash_list[i];
    }

    long long result = 0;

    // maximal_period_len[m] is the size of the largest period
    // of s[0...m]
    int maximal_period_len[k] = { };

    for(int i=1; i<k; ++i){
        // we find the maximal period of prefix s[0...i]

        /*
            We keep t<=i in such a way that the maximal period is
            for sure in s[0...t-1] (Property 1).

            Notice that if s[0...t-1] is not the maximal period,
            then the maximal period of s[0...i] is also a period of
            s[0...t-1]. Thus if call
                            r = maximal_period_len[t-1]
            then the maximal period of s[0...i] is inside s[0...r-1].
            Thus the assignment
                            t <- maximal_period_len[t-1]
            preserves Property 1.
        */
        int t = i;
        while(2*t-1 >= i){
            // We decide if s[0...t-1] is the maximal period

            // hash of the concatenation s[0...t-1]s[0...i-t]
            long long candidate_hash = (hash_list[t-1] + power_list[t]*hash_list[i-t]%m)%m;
            if(candidate_hash == hash_list[i]){
                maximal_period_len[i] = t;
                break;
            }
            t = maximal_period_len[t-1];
        } // If no period is found, maximal_period_len[i] = 0

        result += maximal_period_len[i];
    }

    printf("%lld\n", result);
    return 0;
}
