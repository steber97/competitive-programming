#include <bits/stdc++.h>
#include <climits>
#include <cmath>

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
#define MODULUS 10000
#define DELTA 0.0000001

int main(){

    int N, M;
    cin >> N >> M;

    vi results(N+M+1, 0);

    int max_res = 0;
    for (int i = 1; i<=N; i++){
        for (int j = 1; j<=M; j++){
            results[i+j] ++;
            if (results[i+j] > max_res){
                max_res = results[i+j];
            }
        }
    }

    for (int i = 0; i<results.size(); i++){
        if (results[i] == max_res){
            cout << i << endl;
        }
    }

    return 0;
}