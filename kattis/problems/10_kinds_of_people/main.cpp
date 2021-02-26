#include <bits/stdc++.h>
#include <climits>

using namespace std;

//#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl
#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)

void visit(int counter, vvi& mat, int i, int j, bool posit){
    int equal = posit ? 1 : 0;
    queue<pair<int,int>> q;
    q.push({i,j});
    while(!q.empty()){
        ii n = q.front();
        q.pop();
        // This is useful only the first time.
        mat[n.first][n.second] = counter;
        if (n.first > 0 && mat[n.first-1][n.second] == equal){
            mat[n.first-1][n.second] = counter;
            q.push({n.first-1, n.second});
        }
        if (n.second > 0 && mat[n.first][n.second-1] == equal){
            mat[n.first][n.second-1] = counter;
            q.push({n.first, n.second-1});
        }
        if (n.second < mat[0].size()-1 && mat[n.first][n.second+1] == equal){
            mat[n.first][n.second+1] = counter;
            q.push({n.first, n.second+1});
        }
        if (n.first < mat.size()-1 && mat[n.first+1][n.second] == equal){
            mat[n.first+1][n.second] = counter;
            q.push({n.first+1, n.second});
        }
    }
}

void visit_neg(int counter, vvi& mat, int i, int j){
    
}

int main(){
    int r, c;
    cin >> r >> c ;
    vvi mat(r, vi(c));
    FOR(i,0,r){
        string s;
        cin >> s;
        FOR(j,0,c){
            if (s[j] == '1')
                mat[i][j] = 1;
            else 
                mat[i][j] = 0;
        }
    }
    int counter_posit = 2;
    int counter_neg = -2;
    FOR(i,0,r){
        FOR(j,0,c){
            if (mat[i][j] == 0){
                visit(counter_neg, mat, i, j, false);
                counter_neg --;
            }
            else if (mat[i][j] == 1){
                visit(counter_posit, mat, i, j, true);
                counter_posit ++;
            }
        }
    }

    int q;
    cin >> q;
    FOR(i,0,q){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        if (mat[a][b] == mat[c][d]){
            if (mat[a][b] > 0){
                cout << "decimal" << endl;
            }
            else{
                cout << "binary" << endl;
            }
        }
        else{
            cout << "neither" << endl;
        }
    }
    return 0;
}