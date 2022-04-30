#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

#define TESTING

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


int mcd(int a, int b){
    if (a % b == 0)
        return b;
    int c = a % b;
    return mcd(b, c);
}


unordered_set<int>* fun(int n1, int n2){
    int v = mcd(n1, n2);
    unordered_set<int>* res = new unordered_set<int>();
    FOR(i, 1, int(sqrt(v)) + 2){
        if (v % i == 0){
            res->insert(i);
            res->insert(v/i);
        }
    }
    res->insert(v);
    return res;
}

int main(){
    int T;
    cin >> T;
    FOR(t, 0, T)    {
        int w, l;
        cin >> w >> l;
        unordered_set<int>* s1 = fun(max(w-1, l-1), min(w-1, l-1));
        unordered_set<int>* s2 = fun(max(w-2, l), min(w-2, l));
        unordered_set<int>* s3 = fun(max(w, l-2), min(w, l-2));
        if (l % 2 == 0 && (w-1) % 2 == 0)
            s1->insert(2);
        if (w % 2 == 0 && (l-1) % 2 == 0)
            s1->insert(2);
        unordered_set<int> s_un;
        for(unordered_set<int>::iterator it = s1->begin(); it != s1->end(); it++){
            s_un.insert(*it);
        }
        for(unordered_set<int>::iterator it = s2->begin(); it != s2->end(); it++)
            s_un.insert(*it);
        for(unordered_set<int>::iterator it = s3->begin(); it != s3->end(); it++)
            s_un.insert(*it);
        
        vector<int> set_list(s_un.size());
        int i = 0;
        for (int e: s_un){
            set_list[i] = e;
            i++;
        }
        sort(set_list.begin(), set_list.end());
        cout << set_list.size() << " ";
        FOR(j,0,set_list.size())
            cout << set_list[j] << " ";
        cout << endl;
    }
    return 0;
}