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
    int T;
    cin >> T;
    FOR(t,1,T+1) {
        int N, d;
        cin >> N >> d;
        VALUE(N); VALUE(d);
        int max_jump = 0;
        int pos = 0;
        vector<char> types = {'B'};
        vector<int> dists = {0};

        FOR(i,0,N){
            string in;
            cin >> in;
            
            char type = in[0];
            int dist = stoi(in.substr(2));
            VALUE(type);
            VALUE(dist);
            types.push_back(type); dists.push_back(dist);
        }
        types.push_back('B');
        dists.push_back(d);

        VECT(types);
        
        int i = 0;
        while(i<types.size()){
            if (types[i] == 'B'){
                VALUE(dists[i]);
                max_jump=max(max_jump, dists[i]-pos);
                pos=dists[i];
                i++;
            }
            else{
                int j = i;
                while(types[j] == 'S'){
                    j++;
                }
                FOR(k,i-1,j+1){
                    if (k+2 <= j){
                        max_jump=max(max_jump, dists[k+2] - dists[k]);
                    }
                }
                i = j+1;
                pos = dists[j];
            }
        }
        cout << "Case " << t << ": " << max_jump << endl;

    }
    
    return 0;
}