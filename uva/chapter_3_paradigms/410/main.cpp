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




int main(){
    int t = 1;

    while(true){
        int c,s;
        cin >> c >> s;
        if (cin.eof())
            break;
        vi sp(c*2, 0);
        double sum = 0;
        FOR(i,0,s){
            cin >> sp[i];
            sum += double(sp[i]);
        }
        double avg = sum / double(c);
        
        sort(sp.begin(), sp.end());
        cout << "Set #" << t << endl;
        double imbalance = 0.0;
        FOR(i,0,c){
            imbalance += abs(sp[i] + sp[c*2-i-1] - avg);
            cout << " " << i << ":" << (sp[c*2-i-1] != 0 ? " " + to_string(sp[c*2-i-1]) : "");
            cout << (sp[i] != 0 ? " " + to_string(sp[i]) : "") << endl;
        }
        cout << "IMBALANCE = ";
        printf("%.5f\n", imbalance);
        t++;
        cout << endl;
    }
    
    return 0;
}