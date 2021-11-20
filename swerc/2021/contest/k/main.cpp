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

#define MAX_N 300010

string T;
int n;
int RA[MAX_N];
int SA[MAX_N];
int tempRA[MAX_N];
int tempSA[MAX_N];
int c[MAX_N];

// Code taken from CP3 suffix array page 257
void countingSort(int k){
    int i, sum, maxi = max(300, n);
    memset(c, 0, sizeof c);
    for (i = 0; i < n; i++)
        c[i+k < n ? RA[i+k] : 0]++;
    for (i = sum = 0; i < maxi; i++) {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (i = 0; i < n; i++)
        tempSA[c[SA[i]+k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for (i = 0; i < n; i++)
        SA[i] = tempSA[i];

}

void constructSA() {
    int i, k, r;
    for (i = 0; i < n; i++) RA[i] = T[i];
    for (i = 0; i < n; i++) SA[i] = i;
    for (k=1; k<n; k<<=1) {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        for(i=1; i < n; i++)
            tempRA[SA[i]] = RA[SA[i]] == RA[SA[i-1]] && RA[SA[i] + k] == RA[SA[i-1] + k] ? r : ++r;
        for (i=0; i<n; i++)
            RA[i] = tempRA[i];
        if (RA[SA[n-1]] == n-1)
            break;
    }
}

vector<int> computeLCP() {
    int i, L;
    int Phi[n];
    int PLCP[n];
    vector<int> LCP(n);
    Phi[SA[0]] = -1;
    for (i = 1; i < n; i++)
        Phi[SA[i]] = SA[i-1];
    for (i = L = 0; i < n; i++){
        if (Phi[i] == -1){
            PLCP[i] = 0;
            continue;
        }
        while(T[i+L] == T[Phi[i] + L])
            L++;
        PLCP[i] = L;
        L = max(L-1, 0);
    }
    for (i=0; i<n; i++)
    LCP[i] = PLCP[SA[i]];
    return LCP;
}

int main(){
    cin>> T;
    T += "$";
    n = T.size();
    constructSA();
    vector<int> LCP = computeLCP();
    int min_pref_len = n;
    int min_pos = n;
    for (int i = 1; i < n; i++){
        bool smaller_equal = false;
        int max_pref = n;
        if (LCP[i] <= min_pref_len){
            if(i < n-1){
                if (LCP[i+1] <= min_pref_len){
                    smaller_equal = true;
                    max_pref = max(LCP[i+1], LCP[i]);
                    COUT(i);
                    COUT(" ");
                    COUT(max_pref);
                    COUT(endl);
                }
            }
            else {
                smaller_equal = true;
                max_pref = LCP[i];
            }
        }
        if (smaller_equal && (max_pref < n - 1 - SA[i])){
            if (max_pref < min_pref_len){
                min_pref_len = max_pref;
                min_pos = SA[i];
            }
            else if (min_pos > SA[i])
                min_pos = SA[i];
                
        }
    }
    cout << T.substr(min_pos, min_pref_len+1) << endl;
    return 0;
}