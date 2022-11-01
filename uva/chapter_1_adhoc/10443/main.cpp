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

// legend
// scissor 0
// rock 1
// paper 2


int main(){
    unordered_map<char,int> ci;
    ci['S'] = 0;
    ci['R'] = 1;
    ci['P'] = 2;
    vector<char> ic = {'S', 'R', 'P'};
    int T;
    cin >> T;
    FOR(t,0,T){
        int r, c, n;
        cin >> r >> c >> n;
        vector<vector<int>> grid(r, vector<int>(c));
        FOR(i,0,r){
            FOR(j,0,c){
                char tmp;
                cin >> tmp;
                grid[i][j] = ci[tmp];
            }
        }

        FOR(p,0,n){
            vector<vector<int>> gridtmp(r, vector<int>(c, 3));
            FOR(i,0,r){
                FOR(j,0,c){
                    for(int l=-1; l<2; l++){
                        for(int k=-1; k<2; k++){
                            if ((k == 0 || l == 0) && (k!=0 || l!=0)){
                                if (((i+l) < r) && ((i+l) >=0) && ((j+k) < c) && ((j+k) >=0)){
                                    if ((grid[i][j] + 1) % 3 == grid[i+l][j+k]){
                                        gridtmp[i][j] = grid[i+l][j+k];  // gets conquered
                                    }
                                }
                            }
                        }
                    }
                    if (gridtmp[i][j] == 3)
                        gridtmp[i][j] = grid[i][j];
                }
            }
            grid = gridtmp;
        }
        FOR(i,0,r){
            FOR(j,0,c){
                cout << ic[grid[i][j]];
            }
            cout << endl;
        }
        if (t<T-1)
            cout << endl;
    }
    return 0;    
}