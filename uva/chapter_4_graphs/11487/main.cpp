#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

// #define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << " "; cout << endl
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
typedef vector<char> vc;
typedef vector<double> vd;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vc> vvc;
typedef vector<vvi> vvvi;
typedef vector<vd> vvd;
typedef vector<vector<long long>> vvll;
typedef vector<pair<int,ll>> vill;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<pair<ll,ll>> vllll;
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<vector<pair<int,ll>>> vvill;
typedef vector<vllll> vvllll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001 


int main(){
    int n;
    int testcase = 1;
    do {
        cin >> n;
        if (n>0){
            vector<vector<char>> grid(n, vector<char>(n,'a'));
            vii poslett;
            FOR(i,0,n){
                FOR(j,0,n){
                    char tmp; cin >> tmp;
                    grid[i][j] = tmp;
                    if (grid[i][j] != '.'){
                        if (grid[i][j] != '#'){
                            while(poslett.size() <= (grid[i][j]-'A'))
                                poslett.push_back({-1,-1});
                            poslett[grid[i][j]-'A'] = {i,j};
                        }
                    }
                }
            }
            int totpaths = 1;
            int totdist = 0;
            bool possible = true;
            FOR(i,0,poslett.size()-1){
                vvi dist(n, vi(n, INT32_MAX));
                vvi comb(n, vi(n, -1));
                queue<ii> q;
                q.push({poslett[i].first, poslett[i].second});
                dist[poslett[i].first][poslett[i].second] = 0;
                comb[poslett[i].first][poslett[i].second] = 1;
                while(!q.empty()){
                    int y = q.front().first, x = q.front().second;
                    COUT(y);COUT(" ");COUT(x);COUT(endl);
                    if ((grid[y][x] - 'A') == (i+1))
                        break;
                    q.pop();
                    FOR(k,-1,2){
                        FOR(l,-1,2){
                            if (((k==0) || (l==0)) && ((k!=0) || (l!=0))){
                                if (((k+y) >= 0) && ((k+y) < n)){
                                    if (((l+x) >= 0) && ((l+x) < n)){
                                        if ((grid[k+y][l+x] == '.') ||
                                        ((grid[k+y][l+x]!='#') && (grid[k+y][l+x]-1<=grid[poslett[i].first][poslett[i].second]))){
                                            if(dist[k+y][l+x] == INT32_MAX){
                                                dist[k+y][l+x] = dist[y][x]+1;
                                                comb[k+y][l+x] = comb[y][x];
                                                q.push({k+y,x+l});
                                            }
                                            else if (dist[k+y][l+x] == dist[y][x]+1)
                                                comb[k+y][l+x] += comb[y][x];
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (dist[poslett[i+1].first][poslett[i+1].second] == INT32_MAX)
                    possible = false;
                totdist += dist[poslett[i+1].first][poslett[i+1].second];
                totpaths *= comb[poslett[i+1].first][poslett[i+1].second];
                totpaths %= 20437;
                VALUE(dist[poslett[i+1].first][poslett[i+1].second]);
            }
            cout << "Case " << testcase << ": ";
            if (possible){
                cout << totdist << " " << totpaths << endl;
            }
            else{
                cout << "Impossible" << endl;
            }
            testcase++;
        }
        
    }while(n>0);
    return 0;
}