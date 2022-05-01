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
    int n, m;
    cin >> n >> m;
    vll people(n);
    FOR(i,0,n)
        cin >> people[i];
    vector<int> x(m);
    FOR(i,0,m)
        cin >> x[i];
    sort(x.begin(), x.end());
    vll sump(n+1, 0);  // from 0 to i-1
    FOR(i,1,n+1)
        sump[i] = sump[i-1] + people[i-1];
    
    ll best = 0;
    if (x[0] > 0){
        int pos = min((x[0]-1) / 100, n-1);
        best = max(best, sump[pos+1]);
    }
    if (*(x.end() - 1) < (n-1) * 100){
        int pos = ceil(double(*(x.end() - 1) + 1) / 100.0);
        best = max(best, *(sump.end()-1) - sump[min(pos, int(sump.size())-1)]);
    }
    FOR(i, 0, m-1){
        // Try to place thing in between x[i], x[i+1]
        if (x[i+1] - x[i] > 1 && x[i]+1 <= (n-1)*100){
            int modulus = ((x[i]+1) % 100) > 0 ? 100 - ((x[i]+1) % 100) :  ((x[i]+1) % 100) * (-1);
            int firsthut = min((x[i] + 1 + modulus) / 100, n-1);
            int lasthut = min(((x[i+1] - 1) - ((x[i+1]-1) % 100)) / 100, n-1);
            if (firsthut * 100 < x[i+1]){
                for (int j = firsthut; j < lasthut+1; j++){
                    int mypos = min((j * 100) + (j * 100 - x[i]) - 1, x[i+1]-1);
                    int lasttaken = floor(((mypos + x[i+1]) / 2) / 100);
                    ll tmp = sump[min(lasttaken+1, int(sump.size())-1)] - sump[j];
                    best = max(best, tmp);
                }
            }
            
        }
    }

    cout << best << endl;
}