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

vector<string> recursion_fairy(string a, string b, string seq, stack<char> s){
    vector<string> result;
    if (b.size() == 0)
        return {seq};
    if (!s.empty()){
        if (s.top() == b[0]){
            s.pop();
            vector<string> tmp = recursion_fairy(a, b.substr(1,b.size()-1), seq+'o', s);
            s.push(b[0]);
            result.insert(result.end(), tmp.begin(), tmp.end());
        }
    }
    if (a.size() > 0){
        s.push(a[0]);
        vector<string> tmp = recursion_fairy(a.substr(1, a.size()-1), b, seq+'i', s);
        result.insert(result.end(), tmp.begin(), tmp.end());
        s.pop();
    }
    return result;
}

int main(){
    while(true){
        string a,b;
        cin >> a;
        if (cin.eof())
            break;
        cin >> b;

        stack<char> s;
        vector<string> sequences = recursion_fairy(a, b, "", s);

        sort(sequences.begin(), sequences.end());
        cout << "[" << endl;
        FOR(i,0,sequences.size()){
            FOR(j,0,sequences[i].size()){
                cout << sequences[i][j] << (j == sequences[i].size() - 1 ? "" : " ");
            }
            cout << endl;
        }
        cout << "]" << endl;
    }  
    return 0;    
}