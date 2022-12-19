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
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef pair<double, double> dd;
typedef vector<ii> vii;
typedef vector<dd> vdd;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


int main(){
    int testcase = 0;
    do{
        string s; 
        getline(cin, s);
        if (s.size()==0)
            break;
        int n = s.size();
        vi pos(n);
        FOR(i,0,n){
            if(s[i]<='9' && s[i]>='1')  
                pos[i] = s[i]-'1';
            else if (s[i]!='?'){
                pos[i] = s[i]-'A' + 9;
            }
            else
                pos[i]=-1;
        }
        vvll comb(n, vll(n, 0));
        for(int i = n-1;i>=0;i--){
            if (pos[i]!=-1){
                FOR(j,0,n) {
                    comb[i][j] = 0;
                }
                if (i==n-1)
                    comb[i][pos[i]] = 1;
                else{
                    FOR(j,0,n){
                        if (abs(pos[i]-j) > 1){
                            comb[i][pos[i]] += comb[i+1][j];
                        }
                    }
                }
            }
            else{
                if (i==n-1){
                    FOR(k,0,n){
                        comb[i][k] = 1;
                    }
                }
                else{
                    FOR(k,0,n){
                        FOR(j,0,n){
                            if (abs(j-k)>1){
                                comb[i][k] += comb[i+1][j];
                            }
                        }
                    }
                }
                
            }
        }
        ll result=0;
        FOR(i,0,n)
            result+=comb[0][i];
        cout << result << endl;
    }while(!cin.eof());
    return 0;
}
