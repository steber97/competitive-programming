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

vector<char> letters;




int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n;
        string s;
        cin >> n;
        cin >> s;
        vb taken(n, false);
        assert(n == s.size());
        int countt=0, countm=0;
        FOR(i,0,n){
            if (s[i] == 'T')
                countt ++;
            else
                countm ++;
        }
        if (countm * 2 != countt){
            cout << "NO" << endl;
        }
        else{
            int j = 0;
            bool finish = false;
            for(int i = 0; (i<n) and (!finish); i++){
                if (s[i] == 'M'){
                    bool found = false;
                    for(int k=j; (k< i) and (!found); k++){
                        if ((s[k] == 'T') and (!taken[k])){
                            taken[k] = true;
                            found = true;
                            j = k+1;
                        }
                    }
                    if (!found){
                        cout << "NO" << endl;
                        finish = true;
                    }
                }
            }
            if (!finish){
                int j = 0;
                for(int i=0; (i<n) and (!finish); i++){
                    if (s[i] == 'M'){
                        bool found = false;
                        for(int k=max(i+1, j); (k<n) and (!found); k++){
                            if ((s[k] == 'T') and (!taken[k])){
                                taken[k] = true;
                                found = true;
                                j = k+1;
                            }
                        }
                        if (!found){
                            cout << "NO" << endl;
                            finish = true;
                        }
                    } 
                }
                if (!finish)
                    cout << "YES" << endl;
            }
        }
    }
    return 0;
}