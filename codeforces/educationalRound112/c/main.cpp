#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

// #define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << endl; cout << endl
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
#define MODULUS 10000
#define DELTA 0.0000001


int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int b;
        cin >> b;
        VALUE(b);
        if (b == 1){
            vvi mat(2, vi(b));
            FOR(i,0,2){
                FOR(j,0,b){
                    cin >> mat[i][j];
                }
            }
            cout << 0 << endl;
        }
        else{
            vvi mat(2, vi(b));
            FOR(i,0,2){
                FOR(j,0,b){
                    cin >> mat[i][j];
                }
            }
            if (b == 2){
                FOR (i,0,b){
                    FOR(j,0,b){
                        COUT(mat[i][j]); 
                        COUT(" ");
                    }
                    COUT(endl);
                }
                cout << min(mat[0][1], mat[1][0]) << endl;
            }
            else{

                
                vi mat_sum1(b);
                vi mat_sum2(b);
                mat_sum1[0] = 0;
                FOR (i,1,b)
                    mat_sum1[i] = mat_sum1[i-1] + mat[0][i];
                mat_sum2[0] = mat[1][0];
                FOR (i,1,b)
                    mat_sum2[i] = mat_sum2[i-1] + mat[1][i];
                mat_sum2[b-1] = 0;

                int best = min(mat_sum1[b-1], mat_sum2[b-2]);
                FOR (i, 1, b-1){
                    best = min(best,
                        max(mat_sum1[b-1] - mat_sum1[i],
                            mat_sum2[i-1])
                    );
                }
                cout << best << endl;
            }
        }
        
    }
    return 0;
}