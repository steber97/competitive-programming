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
#define VECT(x) for (int li = 0; li<x.size(); li++) cout << x[li] << " "; cout << endl;
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

string marg; 
vector<string> child_s;
vi child_v;
// map indexed by dp[i, j, p, k, rf] -> value
unordered_map<int, unordered_map<int, unordered_map<int, unordered_map<int, unordered_map<bool,int>>>>> dp;
unordered_map<int, unordered_map<int, unordered_map<bool,int>>> dp2;

// Code taken from https://www.geeksforgeeks.org/reverse-a-string-in-c-cpp-different-methods/
void reverse(string& str){
    int n = str.length(); 
  
    // Swap character starting from two 
    // corners 
    for (int i = 0; i < n / 2; i++) 
        swap(str[i], str[n - i - 1]);
}

bool isindp2(int i, int j, bool rf){
    if (dp2.find(i) == dp2.end()){
        return false;
    }
    if (dp2[i].find(j) == dp2[i].end()){
        return false;
    }
    if (dp2[i][j].find(rf) == dp2[i][j].end()){
        return false;
    }
    return true;
}

bool isindp (int i, int j, int p, int k, bool rf){
    if (dp.find(i) == dp.end()){
        return false;
    }
    if (dp[i].find(j) == dp[i].end()){
        return false;
    }
    if (dp[i][j].find(p) == dp[i][j].end()){
        return false;
    }
    if (dp[i][j][p].find(k) == dp[i][j][p].end()){
        return false;
    }
    if (dp[i][j][p][k].find(rf) == dp[i][j][p][k].end()){
        return false;
    }
    return true;
}


int fatina(int i, int j, int p, int k, bool rf){
    // from position [i, j[, using child p which has been served from [0, k[, rf==require full
    if (isindp(i,j,p,k,rf)){
        return dp[i][j][p][k][rf];
    }
    int res = -1;
    // We cannot serve the child.
    if (j-i < child_s[p].size() - k){
        dp[i][j][p][k][rf] = rf && j > i ? - 1 : 0;

        return dp[i][j][p][k][rf];
    }
    // We have served the child:
    if (k == child_s[p].size()){
        res = child_v[p];
        int add = 0;
        if (i < j){
            int limit = rf ? i+1 : j;
            if (!isindp2(i, j, rf)){
                add = rf ? -1 : 0;
                for (int h = i; h < limit; h++){
                    for (int l=0; l<child_s.size(); l++){
                        if (marg[h] == child_s[l][0])
                            // Auto match first
                            add = max(fatina(h+1, j, l, 1, rf), add);
                    }
                }
                dp2[i][j][rf] = add;
            }
            add = dp2[i][j][rf];
        }
        dp[i][j][p][k][rf] = add >= 0 ? res + add : -1;
        return dp[i][j][p][k][rf];
    }
    // If we need to finish to serve the child:
    for (int l=i; l<j; l++){
        if (marg[l] == child_s[p][k]){
            int add = 0;
            if (l-i > 0){
                if (!isindp2(i, l, true)){
                    add = -1;
                    for (int v=0; v<child_s.size(); v++){
                        if (child_s[v][0] == marg[i])
                            add = max(add, fatina(i+1, l, v, 1, true));
                    }
                    dp2[i][l][true] = add;    
                }
                add = dp2[i][l][true];
            }
            if (add >= 0){
                int tmp = fatina(l+1, j, p, k+1, rf);
                if (tmp >= 0)
                    res = max(res, add + tmp);
            }
        }
    }
    if (res < 0 and !rf)
        res = 0;
    dp[i][j][p][k][rf] = res;
    return res;
}

int main(){
    // margot's candy chain.
    
    cin >> marg;
    int c;
    cin >> c;
    
    unordered_map<string, int> instrings;
    
    FOR(i,0,c){
        string s; int v;
        
        cin >> s >> v;
        if (instrings.find(s) == instrings.end() || instrings[s] < v){
            instrings[s] = v;
        }   
        
        string s2 = s;
        reverse(s2);
        if(instrings.find(s2) == instrings.end() || instrings[s2] < v){
            instrings[s2] = v;
        }
    }

    for (pair<string, int> v: instrings){
        child_s.push_back(v.first);
        child_v.push_back(v.second);
    }

    int res = 0;
    for (int l = 0; l<marg.size(); l++){
        for (int i = 0; i<child_s.size(); i++){
            if (marg[l] == child_s[i][0])
                // Auto match the first.
                res = max(res, fatina(l+1, marg.size(), i, 1, false));
        }
    }
    cout << res << endl;
    return 0;
}