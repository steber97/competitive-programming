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
        for(int t = 0; t < T; t++){
            int n,m;
            cin >> n >> m;
            vi task_per_worker(n,0);
            int max_iter = 0;
            FOR(i,0,m){
                int task;
                cin >> task;
                task --;
                task_per_worker[task]++;
                max_iter = max(task_per_worker[task], max_iter);
            }

            int low=0,high=max_iter+1;
            int res = max_iter;
            while(low <= high){
                int it = (high+low) / 2;
                int tot_sum = 0;
                float excess = 0;
                FOR(i,0,n){
                    if (it <= task_per_worker[i]){
                        tot_sum += it;
                        excess += float(task_per_worker[i] - it);
                    }
                    else{
                        int mod = (it - task_per_worker[i]) % 2;
                        excess -= ((it - task_per_worker[i]) / 2);
                        tot_sum += (task_per_worker[i] + (it - task_per_worker[i])/2);
                    }
                }
                if (excess <= DELTA){
                    res = min(res, it);
                    high = it-1;
                }
                else{
                    low = it+1;
                }
            }
            cout << res << endl;
        }
        return 0;
    }