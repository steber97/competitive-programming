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
    
    int n;
    cin >> n;
    ii pos1={0,0};
    ii pos2={0,1};
    int num1 = 0, num2 = 0;

    int maxnum1 = 0;
    for (int i = 0; i < n-1; i+=2){
        maxnum1 += (i+1);
    }
    int maxnum2 = 0;
    for (int i = 1; i < n-1; i+=2){
        maxnum2 += (i+1);
    }

    maxnum1 *= 2;
    maxnum2 *= 2;

    if (n%2 == 0){
        maxnum2 += n;
    }
    else{
        maxnum1 += n;
    }
    VALUE(maxnum1);
    VALUE(maxnum2);

    bool finish = false;
    bool finish1 = false;
    FOR(i,0,n*n){
        int a;
        cin >> a;
        if (!finish){
            if (a == 1){
                cout << 2 << " " << pos2.first + 1 << " " << pos2.second + 1 << endl << flush;
                pos2.second += 2;
                if (pos2.second >= n){
                    pos2.second = (pos2.second % 2 == 0) ? 1 : 0;
                    pos2.first ++;
                }
                num2++;
            }
            else if (a==2){
                cout << 1 << " " << pos1.first + 1 << " " << pos1.second + 1 << endl << flush;
                pos1.second += 2;
                if (pos1.second >= n){
                    pos1.second = (pos1.second % 2 == 0) ? 1 : 0;
                    pos1.first ++;
                }
                num1++;
            }
            else{
                if (num1 > num2){
                    cout << 2 << " " << pos2.first + 1 << " " << pos2.second + 1 << endl << flush;
                    pos2.second += 2;
                    if (pos2.second >= n){
                        pos2.second = (pos2.second % 2 == 0) ? 1 : 0;
                        pos2.first ++;
                    }
                    num2++;
                }
                else{
                    cout << 1 << " " << pos1.first + 1 << " " << pos1.second + 1 << endl << flush;
                    pos1.second += 2;
                    if (pos1.second >= n){
                        pos1.second = (pos1.second % 2 == 0) ? 1 : 0;
                        pos1.first ++;
                    }
                    num1++;
                }
            }
            if (num1 == maxnum1 || num2 == maxnum2){
                finish = true;
                if (num1 == maxnum1)
                    finish1 = true;
                else
                    finish1 = false;
            }
        }
        else{
            if (finish1){
                cout << (a == 2 ? 3 : 2) << " " << pos2.first + 1 << " " << pos2.second + 1 << endl << flush;
                pos2.second += 2;
                if (pos2.second >= n){
                    pos2.second = (pos2.second % 2 == 0) ? 1 : 0;
                    pos2.first ++;
                }
                num2++;
            }
            else{
                cout << (a == 1 ? 3 : 1) << " " << pos1.first + 1 << " " << pos1.second + 1 << endl << flush;
                pos1.second += 2;
                if (pos1.second >= n){
                    pos1.second = (pos1.second % 2 == 0) ? 1 : 0;
                    pos1.first ++;
                }
                num1++; 
            }
        }
        
    }
    return 0;    
}