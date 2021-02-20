
#include <bits/stdc++.h>
#include <climits>

using namespace std;

//#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
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

    int n;
    cin >> n;

    vll v2(n);

    vll width(3);
    for (int i = 0; i<n; i++){
        int temp;
        cin >> temp; 
        width[i%3] += temp;
    }

    FOR(i,0,n){
        cin >> v2[i];
    }

    vll colors (3, 0);

    FOR(i,0,n){
        FOR(j,0,3){
            colors[(i+1+1+j)%3] += width[j] * v2[i];
        }
    }

    cout << colors[0] << " " << colors[1] << " " << colors[2] << endl;
    return 0;


}