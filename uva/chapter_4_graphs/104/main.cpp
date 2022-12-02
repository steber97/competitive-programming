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
typedef vector<double> vd;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vd> vvd;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


int main(){
    while(!cin.eof()){
        string s; cin >> s;
        if (s.size() == 0 || (s[0] < '0' || s[0] > '9'))
            break;
        int n = stoi(s);
        if (n < 2 || n > 20)
            break;
        vvd graph(n);
        FOR(i,0,n){
            vd lined(n-1);
            FOR(j,0,n-1){
                cin >> lined[j];
            }
            vd l;
            FOR(j,0,n){
                if (i == j){
                    l.push_back(1.0);
                }
                else if (j<i)
                    l.push_back(lined[j]);
                else
                    l.push_back(lined[j-1]);
            }
            graph[i] = l;
        }
        bool finish = false;
        vector<vvd> distances({vvd(n, vd(n,1.0)), graph});
        vector<vvi> parents(2, vvi(n, vi(n)));
        FOR(i,0,n){
            FOR(j,0,n){
                parents[0][i][j] = i;
            }
        }
        FOR(i,0,n){
            FOR(j,0,n){
                parents[1][i][j] = j;
            }
        }
        vi result;
        FOR(u,1,n+3){
            // check
            FOR(i,0,n){
                FOR(j,0,n){
                    COUT(distances[u][i][j]);COUT(" ");
                }
                COUT(endl);
            }
            COUT(endl);

            FOR(i,0,n){
                FOR(j,0,n){
                    COUT(parents[u][i][j]); COUT("\t");
                }
                COUT(endl);
            }
            COUT(endl);
            
            COUT(endl);
            FOR(i,0,n){
                if (!finish){
                    FOR(j,0,n){
                        if (distances[u][i][i] >= 1.01 || abs(distances[u][i][i] - 1.01) < DELTA){
                            int start = i;
                            int l = u;
                            while(l>=0){
                                result.push_back(start);
                                start = parents[l][start][i];
                                l--;
                            }
                            finish=true;
                            break;
                        }
                    }
                }
            }
            if (!finish){
                vvd distancesnew(n, vd(n, -1.0));
                vvi parentsnew(n, vi(n, -1));
                FOR(i,0,n){
                    FOR(j,0,n){
                        FOR(k,0,n){
                            if (k!=j){
                                if (distancesnew[i][j] < graph[k][j] * distances[u][i][k]){
                                    distancesnew[i][j] = graph[k][j] * distances[u][i][k];
                                    parentsnew[i][j] = parents[u][i][k];
                                }
                            }
                        }
                        assert(parentsnew[i][j]!=-1);
                    }
                }
                parents.push_back(parentsnew);
                distances.push_back(distancesnew);
            }
            
        }
        if ((result.size()> 0) && (result.size() <= (n + 1))){
            FOR(i,0,result.size()){
                cout << result[i] + 1 << (i != result.size()-1 ? " " : "");
            }
            cout << endl;
        }
        else{
            cout << "no arbitrage sequence exists" << endl;
        }
        if (cin.eof())
            break;
    }
    return 0;
}