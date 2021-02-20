#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <queue>

using namespace std;

//#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#define COUT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 2147483647   // this is the modulus used by the exercise
#define DELTA 0.0000001

int main(){

    int N;
    cin >> N;

    int first_tail;
    cin >> first_tail;
    first_tail--;

    vi arrows(N);
    for (int i = 0; i<N; i++){
        cin >> arrows[i];
        arrows[i] --;
    }

    vector<vll> dp(N, vll(N+1, 0LL));
    dp[0][first_tail] = 1LL;   // start of the induction.

    for (int i = 1; i<N; i++){
        // first case: the above arrow is at the right of the below arrow
        if (arrows[i] > arrows[i-1]){
            // first step: aligh above tail to below arrow
            for (int j = arrows[i-1] + 1; j<N+1; j++){
                dp[i][arrows[i-1]] += dp[i-1][j]; 
            }

            // second step: align below tail to above head
            for (int j = arrows[i]-1; j>=0; j--){
                if (j != arrows[i-1]){
                    dp[i][j] = dp[i-1][arrows[i]];
                }
            }

            // third step: align tails to the left of both:
            for (int j=0; j<arrows[i-1]; j++){
                dp[i][j] += dp[i-1][j];
            }
            for (int j=arrows[i]+1; j<N+1; j++){
                dp[i][j] += dp[i-1][j];
            }
        }
        else{
            // first step: aligh above tail to below arrow
            for (int j = arrows[i-1] -1; j>=0; j--){
                dp[i][arrows[i-1]] += dp[i-1][j];
            }

            // second step: align below tail to above head
            for (int j = arrows[i]+1; j<N+1; j++){
                if (j != arrows[i-1]){
                    dp[i][j] = dp[i-1][arrows[i]];
                }
            }

            // third step: align tails to the left of both:
            for (int j=0; j<arrows[i]; j++){
                dp[i][j] += dp[i-1][j];
            }
            for (int j=arrows[i-1]+1; j<N+1; j++){
                dp[i][j] += dp[i-1][j];
            }
        }

        // turn everything into modulus 2**31 - 1
        for (int j = 0; j<N+1; j++){
            dp[i][j] %= MODULUS;
        }

    }

    ll result = 0LL;
    for (int j = 0; j<N+1; j++){
        result += dp[N-1][j];
    }
    cout << result % MODULUS << endl;

    return 0;
}