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
     
    bool myfunction (const vi& v1, const vi& v2) {
        for(int i = 0; i < v1.size(); i++){
            if (v1[i] < v2[i]){
                return true;
            }
            else if (v2[i] < v1[i])
                return false;
        }
        return false;
    }
     
    auto myhash = [](const vi& v) {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    };
     
     
    auto myequal = [](const vi& v1, const vi& v2){
        for(int i = 0; i < v1.size(); i++){
            if (v2[i] != v1[i])
                return false;
        }
        return true;
    };

    vector<vector<ll>> slots;
    class Compare{
    public:
        bool operator() (const vi& v1, const vi& v2){
            ll sum1 = 0LL, sum2 = 0LL;
            for(int i = 0; i < v1.size(); i++){
                sum1 += slots[i][v1[i]];
            }
            for(int i = 0; i < v2.size(); i++){
                sum2 += slots[i][v2[i]];
            }
            return sum1 > sum2;
        }
    };


    int main(){
        ios::sync_with_stdio(false);
        cin.tie(0);
        int n;
        cin >> n;
        slots.resize(n);
        vector<ll> sums(n);
        FOR(i,0,n){
            ll sum = 0LL;
            int m; cin >> m;
            slots[i].resize(m);
            FOR(j, 0, m){
                int k; cin >> k;
                slots[i][j] = k;
                sum += k;
            }
            sums[i] = sum;
        }
     
     
        int m;
        cin >> m;
        vector<vector<int>> banned(m, vector<int>(n));
        FOR(i,0,m){
            vector<int> ban(n);
            FOR(j,0,n){
                cin >> banned[i][j];
                banned[i][j]--;
            }
        }
     
        sort(banned.begin(), banned.end(), myfunction);
     
        #ifdef TESTING
        FOR(i,0,m){
            FOR(j,0,n)
                cout << banned[i][j] << " ";
            cout << endl;
        }
        #endif
     
        vector<int> node(n);
        FOR(i,0,n)
            node[i] = slots[i].size() - 1;
     

        
        priority_queue<vector<int>, vector<vector<int>>, Compare> q;
        unordered_set<vector<int>, decltype(myhash), decltype(myequal)> visited (0, myhash, myequal);
        vector<int> start(n);
        FOR(i,0,n){
            start[i] = slots[i].size() - 1;
        }
        q.push(node);
        bool finish = false;
        vi best;
        ll best_val = -1LL;
        while(!q.empty() && !finish){
            vector<int> node = q.top();
            bool found = binary_search(banned.begin(), banned.end(), node, myfunction);
            if (!found){
                ll mysum = 0LL;
                FOR(i,0,n)
                    mysum += slots[i][node[i]];
                if (best_val == -1LL || best_val < mysum){
                    best_val = mysum;
                    best = node;
                }
            }
            COUT("Node extracted\n");
            VECT(node);
            q.pop();
            
            FOR(i, 0, n){
                if (node[i] > 0){
                    node[i]--;
                    bool found = binary_search(banned.begin(), banned.end(), node, myfunction);
                    ll mysum = 0LL;
                    FOR(j,0,n)
                        mysum += slots[j][node[j]];
                    
                    if (!found){
                        COUT("Node found\n");
                        VECT(node);
                        if (best_val == -1LL || best_val < mysum){
                            best_val = mysum;
                            best = node;
                        }
                    }
                    else if(visited.find(node)==visited.end() && (best_val == -1LL || mysum > best_val)){
                        q.push(node);
                        visited.insert(node);
                    }
                    node[i]++;
                }
            }
        }
        FOR(i,0,n){
            cout << best[i]+1 << " ";
        }
        cout << endl;
        return 0;
    }