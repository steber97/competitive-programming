#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << endl; cout << endl
#define MAT(x) for (int u = 0; u < x.size(); u++) { for (int o = 0; o<x[u].size(); o++) cout << x[u][o] << " "; cout << endl;} cout << endl
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#define MAT(x)
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
        int kth;
        cin >> kth;
        vector<vector<unordered_set<char>>> grids(2, vector<unordered_set<char>>(5));
        FOR(i,0,2)
            FOR(j,0,6)
                FOR(k,0,5){
                    char tmp;
                    cin >> tmp;
                    grids[i][k].insert(tmp);
                }
        
        vector<vector<char>> pos(5);
        bool possible = true;
        FOR(i,0,5){
            FOR(j,0,26){
                if(grids[0][i].find('A'+j) != grids[0][i].end() && grids[1][i].find('A'+j) != grids[1][i].end())
                    pos[i].push_back('A'+j);
            }
            if (pos[i].size()==0){
                possible=false;
                break;
            }
            sort(pos[i].begin(), pos[i].end());
        }

        if(possible){
            int counter = 1;
            FOR(i,0,pos[0].size()){
                FOR(j,0,pos[1].size()){
                    FOR(k,0,pos[2].size()){
                        FOR(l,0,pos[3].size()){
                            FOR(m,0,pos[4].size()){
                                if (counter == kth){
                                    cout << pos[0][i] << pos[1][j] << pos[2][k] << pos[3][l] <<pos[4][m] <<endl;
                                    counter += 10000;
                                }
                                counter++;
                            }
                        }
                    }
                }
            }
            if (counter < 10000){
                cout << "NO" << endl;
            }
        }
        else{
            cout << "NO" << endl;
        }
        
    }
    return 0;
}