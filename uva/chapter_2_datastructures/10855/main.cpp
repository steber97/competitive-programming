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

int check_occurrences(vector<vector<char>>& V, vector<vector<char>>& v){
    int counter = 0;
    MAT(V);
    MAT(v);
    FOR(i,0,V.size()-v.size()+1){
        FOR(j,0,V.size()-v.size()+1){
            bool equal = true;
            FOR(l,0,v.size()){
                FOR(k,0,v.size()){
                    if (V[i+l][j+k] != v[l][k]){
                        equal = false;
                    }
                }
            }
            if (equal)
                counter++;
        }
    }
    return counter;
}

int main(){
    while(true){
        int N, n;
        cin >> N >> n;
        if (N == 0)
            break;
        vector<vector<char>> V(N, vector<char>(N));
        FOR(i,0,N)
            FOR(j,0,N)
                cin >> V[i][j];

        vector<vector<char>> v(n, vector<char>(n));
        FOR(i,0,n)
            FOR(j,0,n)
                cin >> v[i][j];
        
        int a,b,c,d;
        a = check_occurrences(V, v);

        
        vector<vector<char>> v90(n, vector<char>(n));
        FOR(i,0,n)
            FOR(j,0,n)
                v90[j][n-1-i] = v[i][j];
        b = check_occurrences(V, v90);
        
        vector<vector<char>> v180(n, vector<char>(n));
        FOR(i,0,n)
            FOR(j,0,n)
                v180[n-1-i][n-1-j] = v[i][j];
        c = check_occurrences(V, v180);

        vector<vector<char>> v270(n, vector<char>(n));
        FOR(i,0,n)
            FOR(j,0,n)
                v270[n-1-j][i] = v[i][j];
        d = check_occurrences(V, v270);

        cout << a << " " << b << " " << c << " " << d << endl;
    }    
    return 0;    
}