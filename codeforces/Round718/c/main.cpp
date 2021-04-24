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

struct p {
    queue<pair<int,int>> q;
    int put=0;
};

int main(){
    int n;
    cin >> n;
    vi diagonal(n);
    int total=0;
    vvi mat(n, vi(n, -1));
    vector<p> ps(n);
    FOR(i,0,n){
        cin >> diagonal[i];
        total += diagonal[i];
        diagonal[i]--;
        // mat[i][i] = diagonal[i];
        ps[diagonal[i]].q.push({i, i});
    }
    bool finish = true;
    FOR(t, 0, total){
        bool done = false;
        FOR(i,0,n){
            if (ps[i].put < i+1) {
                VALUE(i);
                FOR(j,0,ps[i].q.size()){
                    ii tmp = ps[i].q.front();
                    PAIR(tmp);
                    ps[i].q.pop();
                    if (mat[tmp.first][tmp.second] == -1){
                        ps[i].q.push(tmp);
                    }
                }
                if (ps[i].q.size() == 1){
                    ii tmp = ps[i].q.front();
                    ps[i].q.pop();
                    mat[tmp.first][tmp.second] = i;
                    ps[i].put++;
                    if (ps[i].put < i+1){
                        if (tmp.second > 0 and mat[tmp.first][tmp.second-1] == -1){
                            ps[i].q.push({tmp.first, tmp.second-1});
                        }
                        if (tmp.first < mat.size() - 1 and mat[tmp.first+1][tmp.second] == -1 ){
                            ps[i].q.push({tmp.first+1, tmp.second});
                        }
                        if (tmp.first > tmp.second and mat[tmp.first][tmp.second+1] == -1){
                            ps[i].q.push({tmp.first, tmp.second+1});
                        }
                        if (tmp.first > 0 and tmp.first > tmp.second and mat[tmp.first-1][tmp.second] == -1){
                            ps[i].q.push({tmp.first-1, tmp.second});
                        }
                    }
                    done = true;
                    break;
                }
            }
        }
        #ifdef TESTING
        FOR(i,0,n){
            FOR(j,0,i+1){
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
        #endif
        if (!done){
            finish = false;
        }
    }

    if (!finish){
        cout << -1 << endl;
    }
    else{
        FOR(i,0,n){
            FOR(j,0,i+1){
                cout << mat[i][j]+1 << " ";
            }
            cout << endl;
        }
    }

    return 0;
}