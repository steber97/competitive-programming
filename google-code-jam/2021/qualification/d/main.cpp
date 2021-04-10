#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>
#include <random>

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

vi tripartite_sort(unordered_set<int> allnums, int high, bool ishigh){
    cerr << "start" << endl;
    // base case: only 3 elements or less
    if (allnums.size() == 0){
        cerr << "allnums size 0" << endl;
        vi res(0);
        return res;
    }
    if (allnums.size() == 1){
        cerr << "allnums size 1" << endl;
        vi res(1);
        res[0] = *(allnums.begin());
        return res;
    }
    if (allnums.size() == 2){
        cerr << "allnums size 2 with high " << high << endl;
        cout << *(allnums.begin()) << " " << *(next(allnums.begin())) << " " << high << endl << flush;
        int res; cin >> res;
        if (res == -1){
            exit(0);
        }
        vi vect;
        if (ishigh){
            if (res == *(allnums.begin())){
                vect = {*(next(allnums.begin())), *(allnums.begin())};
            }
            else {
                vect = {*(allnums.begin()), *(next(allnums.begin()))};
            }
        }
        else{
            if (res == *(allnums.begin())){
                vect = {*(allnums.begin()), *(next(allnums.begin()))};
            }
            else {
                vect = {*(next(allnums.begin())), *(allnums.begin())};
            }
        }
        return vect;
    }
    if (allnums.size() == 3){
        cerr << "allnums size 3 with high " << high << endl;
        vi vect;
        int a = *(allnums.begin());
        int b = *(next(allnums.begin()));
        int c = *(next(next(allnums.begin())));
        cout << a << " "  << b << " " << c << endl << flush;
        int r ; cin >> r; if (r == -1) exit(0);
        int a2, b2, c2;
        if (r == a){
            b2 = a; a2 = b; c2=c;
        }
        if (r == b){
            b2 = b; a2 = a; c2=c;
        }
        if (r == c){
            b2 = c; a2 = b; c2=a;
        }

        cout << a2 << " "  << c2 << " " << high << endl << flush;
        cin >> r;
        if (r == -1)
            exit(0);
        if (ishigh){
            if (r == a2){
                vect = {c2, b2, a2};
            }
            if (r == c2)
                vect = {a2, b2, c2};
        }
        else{
            if (r == a2){
                vect = {a2, b2, c2};
            }
            if (r == c2)
                vect = {c2, b2, a2};
        }
        return vect;
    }
    unordered_set<int> lower, medium, higher;
    int a,b,c;
    a = *(allnums.begin()); b = *(next(allnums.begin()));
    allnums.erase(a); allnums.erase(b);
    int low, top;
    int r;
    if (high != -1){
        c = high;
        cout << a << " " << b << " " << c << endl << flush;
        cerr << a << " " << b << " " << c << endl << flush;
        cin >> r;
        if (r == -1)
            exit(0);
        if (ishigh){
            if (r == a){
                low = b;
                top = a;
            }
            else{
                low = a;
                top=b;
            }
        }
        else{
            if (r == b){
                low = b;
                top = a;
            }
            else{
                low = a;
                top=b;
            }
        }
    }
    else {
        cerr << "This should happen just once" << endl;
        c = *(allnums.begin());
        allnums.erase(c);
        cerr << a << " " << b << " " << c << endl;
        cout << a << " " << b << " " << c << endl << flush;
        cin >> r;
        cerr << r << endl;
        if (r == -1)
            exit(0);
        if (r == a){
            low = b;
            top = c;
        }
        if (r == b){
            low = a;
            top = c;
        }
        if (r == c){
            low = a;
            top = b;
        }
        allnums.insert(r);
    }
    
    
    for(int val: allnums){
        cerr << low << " " << top << " " << val << endl;
        cout << low << " " << top << " " << val << endl << flush;
        cin >> r;
        if (r == -1)
            exit(0);
        if (r == low){
            lower.insert(val);
        }
        if (r == top){
            higher.insert(val);
        }
        if (r == val){
            medium.insert(val);
        }
    }
    // cerr << "finish" << endl;
    vi res1 = tripartite_sort(lower, low, true);
    vi res2 = tripartite_sort(medium, top, true);
    vi res3 = tripartite_sort(higher, top, false) ;
    
    res1.push_back(low);
    res1.insert(res1.end(), res2.begin(), res2.end());
    res1.push_back(top);
    res1.insert(res1.end(), res3.begin(), res3.end());
    return res1;
}

int main(){
    int T, N, Q;
    cin >> T >> N >> Q;
    cerr << T << " "  << N << " " << Q << endl;
    
    FOR(t,0,T){
        cerr << "Test case #" << t+1 << endl;
        unordered_set<int> allnums;
        vi res;
        FOR(i,0,N)
            allnums.insert(i+1);
        res = tripartite_sort(allnums, -1, false);
        
        FOR(i,0,res.size())
            cout << res[i] << " " ;
        cout << endl << flush;
        int r;
        cin >> r;
        if (r == 1)
            cerr << "good" << endl;
        else{
            exit(0);
        }
    }

    return 0;
}