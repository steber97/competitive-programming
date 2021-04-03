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
        int n;
        cin >> n;
        string s;
        cin >> s;
        vi zeros(n);
        int count = 0;
        for(int i = n-1; i>=0; i--){
            if (s[i]=='0')
                count++;
            zeros[i] = count;
        }
        
        int open1=0, close1=0, open2=0, close2=0;
        string res1, res2;
        bool impossible = false;
        for(int i = 0; i < n; i++){
            VALUE(i);
            if (s[i]=='0'){
                if ((close1>=open1) and (close2>=open2))
                    impossible = true;
                else{
                    if (open1 <= open2){
                        // Open 1
                        res1.push_back('(');
                        res2.push_back(')');
                        open1++;
                        close2++;
                    }
                    else{
                        // Open 1
                        res1.push_back(')');
                        res2.push_back('(');
                        open2++;
                        close1++;
                    }
                }
            }
            else{
                int min_ = min(open1, open2);
                int max_ = max(open1, open2);
                if (((zeros[i]%2==0?zeros[i]/2:zeros[i]/2+1) + min_ < n/2) and 
                ((zeros[i]/2) + max_ < n/2)){
                    // Open both
                    res1.push_back('(');
                    res2.push_back('(');
                    open1++;
                    open2++;
                }
                else{
                    res1.push_back(')');
                    res2.push_back(')');
                    close1++;
                    close2++;
                }
            }

            VALUE(open1);
            VALUE(close1);
            VALUE(open2);
            VALUE(close2);
            if (open1>n/2 or open2>n/2)
                impossible = true;
            if (close1 > open1 or close2 > open2)
                impossible = true;
        }
        if (impossible)
            cout << "NO" << endl;
        else{
            cout << "YES" << endl;
            cout << res1 << endl << res2 << endl;
        }
    }
    return 0;    
}