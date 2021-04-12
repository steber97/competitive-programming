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
    int n,k;
    cin >> n >> k;
    unordered_map<string, string> next_step;
    unordered_set<string> used;
    FOR(i,0,k)
        letters.push_back('a'+i);
    
    string start = "aa";
    if (k > 1)
        next_step["aa"] = "ab";
    FOR(i,0,k){
        FOR(j,i+1,k){
            if (j != k-1){
                next_step[{letters[i], letters[j]}] = {letters[j], letters[i]};
                next_step[{letters[j], letters[i]}] = {letters[i], letters[j+1]};
                if (used.find({letters[j], letters[i]}) != used.end()){
                    COUT("error "); COUT(letters[j]); COUT(letters[i]); COUT(endl);
                }
                if (used.find({letters[i], letters[j+1]}) != used.end()){
                    COUT("error "); COUT(letters[i]); COUT(letters[j+1]);COUT(endl);
                }
                used.insert({letters[i], letters[j+1]});
                used.insert({letters[j], letters[i]});
            }
            else{
                next_step[{letters[i], letters[j]}] = {letters[j], letters[i+1]};
                next_step[{letters[j], letters[i+1]}] = {letters[i+1], letters[i+1]};
                if (i+2 < k){
                    next_step[{letters[i+1], letters[i+1]}] = {letters[i+1], letters[i+2]};
                    if (used.find({letters[i+1], letters[i+2]}) != used.end()){
                        COUT("error "); COUT(letters[i]); COUT(letters[j+1]);COUT(endl);
                    }
                }
                used.insert({letters[j], letters[i+1]});
                used.insert({letters[i+1], letters[i+1]});
            }
        }
    }


    if (used.find({letters[k-1], letters[0]}) != used.end()){
        COUT("error");COUT(endl);
    }
    
    next_step[{letters[k-1], letters[k-1]}] = {letters[k-1], letters[0]};
    next_step[{letters[k-1], letters[0]}] = "aa";

    FOR(i,0,k)
        FOR(j,0,k){
            string tmp = next_step[{letters[i], letters[j]}];
            COUT(letters[i]); COUT(letters[j]); COUT (" "); COUT(tmp); COUT(endl);
        }
    
    string res = "aa";
    FOR(i,0,n-2){
        string next = next_step[res.substr(res.size()-2, 2)];
        res.push_back(next[1]);
    }

    if (n == 1)
        cout << 'a' << endl;
    else{
        cout << res << endl;
    }

    return 0;
}