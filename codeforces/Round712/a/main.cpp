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




int main(){
    
    int T;
    cin >> T;
    FOR(t,0,T){
        string s;
        cin >> s;
        vector<char> res(s.size()+1);
        if (s.size()==1){
            if (s[0] == 'a')
                cout << "NO" <<endl;
            else{
                cout <<"YES" << endl << s[0] << "a" << endl;
            }
        }
        else{
            int start = 0;
            int end = res.size()-1;
            bool finish = false;
            for(int i = 0; i < s.size()/2; i++){
                VALUE(s[i]); VALUE(s[s.size()-i-1]);
                if ((s[i] != 'a' or s[s.size()-i-1] != 'a') and !finish){
                    if (s[i] != 'a'){
                        res[start] = s[i];
                        res[end] = 'a';
                        res[end-1] = s[s.size()-i-1];
                        start++; end -= 2;
                    }
                    else{
                        res[start] = 'a';
                        res[start+1] = s[i];
                        res[end] = s[s.size()-i-1];
                        start += 2; end--;
                    }
                    finish = true;
                }
                else{
                    res[start] = s[i];
                    res[end] = s[s.size()-i-1];
                    start++; end--;
                }
            }

            if (s.size() % 2 == 1){
                if (!finish){
                    if (s[s.size()/2] != 'a'){
                        VALUE(start); VALUE(end);
                        res[start] = 'a';
                        res[end] = s[s.size()/2];
                        finish = true;
                    }
                    else{
                        // Cannot finish!
                    }
                }
                else{
                    res[start] = s[s.size()/2];
                }
            }
            
            if (finish){
                cout << "YES" << endl;
                for(char c: res)
                    cout << c;
                cout << endl;
            }
            else{
                cout << "NO" << endl;
            }
        }
    }
    return 0;    
}