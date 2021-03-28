#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>

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

vvi buildPascalTree(int depth){
    vvi pascalTree;
    pascalTree.push_back(vi(1,1));
    FOR(i,1,depth){
        pascalTree.push_back(vi());
        FOR(j,0,i){
            if (j == 0 || j == i-1)
                pascalTree[i-1].push_back(1);
            else
                pascalTree[i-1].push_back(pascalTree[i-2][j-1] + pascalTree[i-2][j]);
        }
    }
    return pascalTree;
}

int pow2(int i){
    int j = 1;
    FOR(k,0,i)
        j *= 2;
    return j;
}

int main(){
    int T;
    cin >> T;
    vvi pascalTree = buildPascalTree(505);
    FOR(t,1,T+1){
        cout << "Case #" << t << ":" << endl;
        VALUE(t);
        int n;
        cin >> n;
        int n_copy = n;
        if (n <= 500){
            FOR(i,0,n){
                // Go straight
                cout << i+1 << " " << 1 << endl;
            }
        }
        else{
            vii result;
            result.push_back({1,1});
            int num = n - 50;  //totally random
            bitset<32> mask(num);
            VALUE(num);
            VALUE(mask);
            bool left = true;
            n -= 1;
            int last = 1;
            FOR(i, 1, 32){
                if (mask[i]){
                    FOR(j, 0, i+1){
                        if (left)
                            result.push_back({i+1, j+1});
                        else
                            result.push_back({i+1, i-j+1});
                    }
                    n -= pow2(i);
                    left = !left;
                }
                else{
                    if (left)
                        result.push_back({i+1, 1});
                    else
                        result.push_back({i+1, i+1});
                    n -= 1;
                }
                last = i+1;
            }
            FOR(i,0,n){
                if (left)
                    result.push_back({last+i+1, 1});
                else
                    result.push_back({last+i+1, last+i+1});
            }
            int total = 0;
            FOR(i,0,result.size()){
                if (i > 0){
                    assert(result[i] != result[i-1]);
                }
                cout << result[i].first << " " << result[i].second << endl;
                total += pascalTree[result[i].first - 1][result[i].second-1];
            }
            assert(total == n_copy);
            assert(result.size() <= 500);
        }
    }
    

    return 0;
}