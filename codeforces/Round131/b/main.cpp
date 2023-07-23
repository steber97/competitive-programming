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
     
    
    int main(){
        ios::sync_with_stdio(false);
        cin.tie(0);
        int T;
        cin >> T;
        FOR(t,0,T){
            int n;
            cin >> n;
            vb used(n, false);
            vi result;
            FOR(i,0,n){
                if (!used[i]){
                    used[i] = true;
                    result.push_back(i+1);
                    int j = i+1;
                    while(j*2 <= n){
                        result.push_back(j*2);
                        used[j*2-1] = true;
                        j*=2;
                    }
                }
            }
            cout << 2 << endl;
            FOR(i,0,n)
                cout << result[i] << " ";
            cout << endl;
        }
        return 0;
    }