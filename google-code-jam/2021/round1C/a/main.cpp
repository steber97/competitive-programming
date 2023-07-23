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
    cout << fixed;
    FOR(t,1,T+1){
        ll K,N;
        cin >> N >> K;
        vector<ll> numbers(N);
        FOR(i,0,N)
            cin >> numbers[i];
        sort(numbers.begin(), numbers.end());
        priority_queue<long long, std::vector<int>, std::greater<int>> best;
        VECT(numbers);
        FOR(i,0,N){
            if (i == 0){
                if (numbers[i] == 1LL){
                    ;
                }
                else{
                    best.push(numbers[i]-1LL);
                }
                if (i == N-1){
                    if (numbers[i] == K){
                        ;
                    }
                    else{
                        if (best.size() < 2){
                            best.push(K - numbers[i]);
                        }
                        else{
                            ll second_best = best.top(); 
                            if (second_best < (K - numbers[i])){
                                best.pop();
                                best.push(K - numbers[i]);
                            }
                        }

                    }
                }
            }
            else if (i < N-1){
                if (numbers[i] != numbers[i-1]){
                    if (best.size() < 2){
                        ll res = (numbers[i] - numbers[i-1] - 1LL) % 2LL == 0LL? (numbers[i] - numbers[i-1] - 1LL)/2LL : (numbers[i] - numbers[i-1] - 1LL)/2LL + 1LL;
                        best.push(res);
                    }
                    else{
                        ll second_best = best.top(); 
                        ll res = (numbers[i] - numbers[i-1] - 1LL) % 2LL == 0LL? (numbers[i] - numbers[i-1] - 1LL)/2LL : (numbers[i] - numbers[i-1] - 1LL)/2LL + 1LL;
                        
                        if (second_best < res){
                            best.pop();
                            best.push(res);
                        }
                    }
                }
            }
            else {
                
                ll res;
                if (numbers[i]==numbers[i-1])
                    res = 0LL;
                else
                    res = (numbers[i] - numbers[i-1] - 1LL) % 2LL == 0LL? (numbers[i] - numbers[i-1] - 1LL)/2LL : (numbers[i] - numbers[i-1] - 1LL)/2LL + 1LL;
                    
                if (best.size() < 2){
                    best.push(res);
                }
                else{
                    ll second_best = best.top(); 
                    if (second_best < res){
                        best.pop();
                        best.push(res);
                    }
                }
                if (numbers[i] == K){
                    ;
                }
                else{
                    if (best.size() < 2){
                        best.push(K - numbers[i]);
                    }
                    else{
                        ll second_best = best.top(); 
                        if (second_best < (K - numbers[i])){
                            best.pop();
                            best.push(K - numbers[i]);
                        }
                    }

                }
            }
        }
        ll tot = 0LL;
        while(!best.empty())
        {
            VALUE(best.top());
            tot += best.top();
            best.pop();
        }
        double res = double(tot) / double(K);
        cout << std::setprecision(9) << "Case #" << t << ": " << res << endl;
    }
    return 0;
}