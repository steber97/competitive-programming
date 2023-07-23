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



int fatina(int zeros, int middle_one, int unbalance, int last_rev, vector<vector<vector<vector<int>>>>& DP){
    if (DP[zeros][middle_one][unbalance][last_rev] != -1){
        return DP[zeros][middle_one][unbalance][last_rev];
    }
    int res = zeros;
    if (zeros == 0)
        return 0;
    else if (zeros == 1){
        if (middle_one == 0){
            // String is palindrome
            return 1;
        }
        if (last_rev == 1)
            return 1;
        else return 0;
    }
    else {
        if (middle_one == 1){
            // try_in_the_middle 
            int v = fatina(zeros-1, 1, unbalance, 0, DP);
            COUT("fatina "); COUT(zeros-1); COUT(" "); COUT(true); COUT(" ");
            COUT(unbalance); COUT(" "); COUT(false); COUT(" = "); COUT(v); COUT(endl);
            res = min(
                res, 
                zeros - v);
        }
        if ((unbalance != 0) && (last_rev == 0)){
            // Give it back reversed
            int v = fatina(zeros, middle_one, unbalance, 1, DP);
            COUT("fatina "); COUT(zeros); COUT(" "); COUT(middle_one); COUT(" ");
            COUT(unbalance); COUT(" "); COUT(true); COUT(" = "); COUT(v); COUT(endl);
            res = min(res,
                zeros - v
            );
        }
        if (unbalance != 0){
            // Balance
            int v = fatina(zeros-1, middle_one, unbalance-1, 0, DP);
            // COUT("fatina "); COUT(zeros-1); COUT(" "); COUT(middle_one); COUT(" ");
            // COUT( unbalance-1); COUT(" "); COUT(false); COUT(" = "); COUT(v); COUT(endl);
            
            res = min(
                res,
                zeros - v
            );
        }
        if ((unbalance + 1) <= (zeros - 1)){
            int v = fatina(zeros-1, middle_one, unbalance+1, 0, DP);
            // COUT("fatina "); COUT(zeros-1); COUT(" "); COUT(middle_one); COUT(" ");
            // COUT(unbalance+1); COUT(" "); COUT(false); COUT(" = "); COUT(v); COUT(endl);
            
            res = min(
                res,
                zeros - v
            );
        }
    }
    DP[zeros][middle_one][unbalance][last_rev] = res;
    return res;
}

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int count_zeros = 0;
        FOR(i,0,s.size()){
            if (s[i] == '0'){
                count_zeros++;
            }
        }
        bool middle_one = ((count_zeros % 2) == 0) ? true : 
            (s[s.size()/2] == '1');
        VALUE(middle_one);
        int unbalance = 0;
        vector<vector<vector<vector<int>>>> DP(count_zeros+1, vector<vector<vector<int>>>(
            2, vector<vector<int>>( count_zeros+1, vector<int>(2, -1))
        ));
        int first_spends = fatina(count_zeros, middle_one ? 1 : 0, unbalance, 1, DP);
        VALUE(first_spends);
        if ((first_spends * 2) == count_zeros){
            cout << "DRAW" << endl;
        }
        else if (first_spends == (count_zeros / 2)){
            cout << "ALICE" << endl;
        }
        else{
            cout << "BOB" << endl;
        }
    }
    return 0;
}
