
#include <bits/stdc++.h>
#include <climits>

using namespace std;

#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl
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


int main(){

    int D,R,T;
    cin >> D >> R >> T;

    int i = 4;
    int j = 4-D;

    int count1 = 0;int count2 = 0;
    bool finish = false;
    int res;
    while(!finish){
        if (i >= 4)
            count1 += i;
        if (j >= 3)
            count2 += j;

        if (count1 + count2 == R+T){
            finish = true;
            res = R - count1;
        }
        else{
            i++; j++;
        }
    }
    cout << res << endl;
}