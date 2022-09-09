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
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


int expense(int tot){
    int res = 0;
    if (tot <= 100){
        return tot * 2;
    }
    res += 200;
    if (tot <= 10000){
        return res + (tot-100)*3;
    }
    res += 9900*3;
    if (tot <= 1000000){
        return res + (tot - (10000))*5;
    }
    res += (1000000-10000)*5;
    return res + (tot - 1000000) * 7;
    
}

int main(){
    int a,b;
    cin >> a >> b;
    while(a!=0){
        int consumed = 0;
        if (a <= 200){
            consumed += a/2;
        }
        else{
            consumed += 100;
            if (a <= 29700 + 200){
                consumed += (a - 200) / 3;
            }
            else{
                consumed += 9900;
                
                if (a <= 29700 + 200 + 4950000){
                    consumed += (a - 29700 - 200) / 5;
                }
                else {
                    consumed += 990000;
                    consumed += (a - 29700 - 200 - 4950000) / 7;
                }
            }   
        }
        VALUE(consumed);
        bool found = false;
        int x,y;
        x=1;y=consumed;
        while(!found){
            int res = (x+y)/2;
            VALUE(res);
            int other = consumed-res;
            int myexp = expense(res);
            int otherexp = expense(other);
            VALUE(myexp); VALUE(otherexp);
            if(otherexp-myexp == b){
                found = true;
            }
            else if (otherexp - myexp < b){
                y=res-1;
            }
            else{
                x=res+1;
            }
        }
        cout << expense((x+y)/2) << endl;
        
        cin >> a >> b;
    }
    return 0;    
}