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



#define N 1000001
int main(){
    while(true){
        deque<string> q;
        string s;
        cin >> s;
        if (cin.eof())
            break;
        
        int start = 0;
        bool push_front = true;
        int j = 0;
        for(int i=0; i < s.size(); i++){
            if (s[i] == '[' || s[i] == ']'){
                VALUE(s.substr(start, j));
                if (push_front)
                    q.push_front(s.substr(start, j));
                else
                    q.push_back(s.substr(start, j));
                j = 0;
                start = i+1;
                push_front = (s[i] == '[');
            }
            else{
                j++;
            }
        }
        if (push_front)
            q.push_front(s.substr(start, j));
        else
            q.push_back(s.substr(start, j));
        while(!q.empty()){
            string d = q.front();
            q.pop_front();
            cout << d;
        }
        cout << endl;
    }
    return 0;    
}