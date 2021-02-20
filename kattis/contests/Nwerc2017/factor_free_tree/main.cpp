
#include <bits/stdc++.h>
#include <climits>

using namespace std;

// #define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int prf = 0; prf<x.size(); prf++) cout << x[prf] << " "; cout << endl
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

#define MAXN   10000005 
  

// This list of lists keeps, for every index i,
// all indices of v that are divided by i.
vector<vector<int>> occ(MAXN, vector<int>());
  
// stores smallest prime factor for every number 
int spf[MAXN]; 
  
// Calculating SPF (Smallest Prime Factor) for every 
// number till MAXN. 
// Time Complexity : O(nloglogn) 
void sieve() 
{ 
    spf[1] = 1; 
    for (int i=2; i<MAXN; i++) 
  
        // marking smallest prime factor for every 
        // number to be itself. 
        spf[i] = i; 
  
    // separately marking spf for every even 
    // number as 2 
    for (int i=4; i<MAXN; i+=2) 
        spf[i] = 2; 
  
    for (int i=3; i*i<MAXN; i++) 
    { 
        // checking if i is prime 
        if (spf[i] == i) 
        { 
            // marking SPF for all numbers divisible by i 
            for (int j=i*i; j<MAXN; j+=i) 
  
                // marking spf[j] if it is not  
                // previously marked 
                if (spf[j]==j) 
                    spf[j] = i; 
        } 
    } 
} 
  
// A O(log n) function returning primefactorization 
// by dividing by smallest prime factor at every step 
vector<int> getFactorization(int x) 
{ 
    vector<int> ret; 
    while (x != 1) 
    { 
        ret.push_back(spf[x]); 
        x = x / spf[x]; 
    } 
    return ret; 
} 


bool interval(int l, int h, int val, vvi& occ, vi& v){
    int a = v[val];
    while(a != 1){
        int div = spf[a];
        // All other numbers that are divisible by div
        // Do not use vi conflicts = occ[div], or it makes a copy.
        vi* conflicts = &(occ[div]); 
        auto it = lower_bound(conflicts->begin(), conflicts->end(), val);
        if (it != conflicts->begin() && *prev(it) >= l)
            return false;
        if (it+1 != conflicts->end() && *(it+1) <= h)
            return false;
        
        while(a % div == 0)
            a /= div;
    }
    return true;
}

  
bool fatina(vi& v, vvi& occ, int l, int h, vi& parents, int parent){
    if (l == h){
        return true;
    }
    for(int i = 0; i < (h-l)/2 + 1; i++){
        if (interval(l, h, l+i, occ, v)){
            parents[l+i] = parent + 1;
            return fatina(v, occ, l, l+i, parents, l+i) && 
                    fatina(v, occ, l+i+1, h, parents, l+i);
        }
        if (interval(l, h, h-i-1, occ, v)){
            parents[h-i-1] = parent + 1;
            return fatina(v, occ, l, h-i-1, parents, h-i-1) && 
                    fatina(v, occ, h-i, h, parents, h-i-1);
        }
    }
    return false;
}

int main(){

    int N;
    cin >> N;
    sieve(); 
    vi v(N);
    FOR(i,0,N){
        cin >> v[i];
        vi p = getFactorization(v[i]);
        int last = -1;
        for (int x: p){
            if (x != last){
                occ[x].push_back(i);
            }
            last = x;
        }
    }

    vi parents(N, -1);
    if (fatina(v, occ, 0, N, parents, -1)){
        for (int x: parents)
            cout << x << " ";
        cout << endl;
    }
    else{
        cout << "impossible" << endl;
    }
    
    return 0;
}