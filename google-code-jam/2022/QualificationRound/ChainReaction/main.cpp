#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>

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

vi topsort(vi& p){
    vi incount(p.size(), 0);
    FOR(i,0,p.size()){
        if (p[i] >= 0)
            incount[p[i]] ++;
    }
    queue<int> start;
    FOR(i,0,incount.size())
        if (incount[i] == 0)
            start.push(i);
    vi result;
    while(!start.empty()){
        int node = start.front(); start.pop();
        result.push_back(node);
        if (p[node] >= 0){
            incount[p[node]] --;
            if (incount[p[node]] == 0)
                start.push(p[node]);
        }
    }
    return result;
}

int main(){

    int T;
    cin >> T;
    FOR(t,0,T){
        int n;
        cin >> n;
        vll fun(n);
        vi p(n);
        FOR(i,0,n)
            cin >> fun[i];
        FOR(i,0,n){
            cin >> p[i];
            p[i]--;
        }
        
        vi tops = topsort(p);
        
        vll minDP(n, -1);
        vi pDP(n, -1);
        FOR(i,0,n){
            int v = tops[i];
            if (minDP[v] == -1){
                minDP[v] = fun[v];
                pDP[v] = v;
            }
            if (p[v] != -1){
                if (pDP[p[v]] != -1){
                    if (minDP[p[v]] > max(fun[v], minDP[v])){
                        minDP[p[v]] = max(fun[v], minDP[v]);
                        pDP[p[v]] = pDP[v];
                    }
                }
                else {
                    minDP[p[v]] = max(fun[v], minDP[v]);
                    pDP[p[v]] = pDP[v];
                }
            }
        }
        VECT(tops);
        VECT(pDP);
        vector<bool> visited(n, false);
        ll result = 0;
        FOR(i,0,n){
            int j = n-1-i;
            int iter = pDP[tops[j]];
            ll tmpval = 0;
            while(iter != -1 && !visited[iter]){
                visited[iter] = true;
                tmpval = max(tmpval, fun[iter]);
                iter = p[iter];
            }
            result += tmpval;
        }
        cout << "Case #" << t+1 << ": " << result << endl;
    }
    return 0;
}