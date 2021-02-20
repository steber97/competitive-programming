
#include <bits/stdc++.h>
#include <climits>

using namespace std;

//#define TESTING

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
#define INF 100000000



int LSOne(int b){
    return b & (-b);
}

class FenwickTree{
    private:
        vector<ll> ft;
    public:
        FenwickTree(int n){
            ft.assign(n+1, 0LL);
        }

        ll rsq(int b){
            ll sum = 0LL;
            for (; b; b -= LSOne(b)){
                sum += ft[b];
            }
            return sum;
        }

        ll rsq(int a, int b){
            if (a == 1)
                return rsq(b);
            return rsq(b) - rsq(a-1);
        }
        void adjust (int k, ll v){
            for (; k<int(ft.size()); k += LSOne(k)){
                ft[k] += v;
            }
        }
};

vll res;
FenwickTree ft(100100);        // as big as 100000, so that it can contain all possible keys. 
vll spec, cost;
vvi graph;

void dfs(int node){
    COUT("CIA");COUT(endl);
    ll prev = ft.rsq(spec[node]-1LL);

    FOR(i,0,graph[node].size()){
        dfs(graph[node][i]);
    }
    res[node] = ft.rsq(spec[node]-1LL) - prev;
    ft.adjust(spec[node], ll(cost[node]));
}


int main(){

    int N;
    cin >> N;
    N++;
    graph.resize(N);
    res.resize(N);
    spec.resize(N);
    cost.resize(N);
    vi sfh;  // start from here

    FOR(i,1,N){
        ll x,y,z;
        cin >> x >> y >> z;
        spec[i] = y;
        cost[i] = z;
        if (x == -1LL){
            // it's a manager
            sfh.push_back(i);
        }
        else{
            graph[x].push_back(i);
        }
    }

    FOR(i,0,sfh.size()){
        dfs(sfh[i]);
    }

    FOR(i,1,N)
        cout << res[i] << endl;

    return 0;
}