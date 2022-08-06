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
#define MAT(x) for (int u = 0; u < x.size(); u++) { for (int o = 0; o<x[u].size(); o++) cout << x[u][o] << " "; cout << endl;} cout << endl
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#define MAT(x)
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

#define len 65538LL
// #define len 12LL

int main(){
    int T;
    cin >> T;
    FOR(t,1,T+1){
        int N, S, Q;
        cin >> N >> S >> Q;
        stack<int> st;
        vector<queue<int>> vq(N, queue<int>());
        int tot=0;
        FOR(i,0,N){
            int q;
            cin >> q;
            tot+=q;
            FOR(j,0,q){
                int a;
                cin >> a;
                a--;
                vq[i].push(a);
            }
        }

        int timer = 0;
        int station = 0;
        while(tot!=0){
            // unload
            VALUE(tot);
            while(st.size()>0){
                int a = st.top();
                st.pop();
                if (a==station){
                    tot--;
                    timer++;
                }
                else{
                    if (vq[station].size() < Q){
                        vq[station].push(a);
                        timer++;
                    }
                    else{
                        // re-put item on top of stack.
                        st.push(a);
                        break;
                    }
                }
            }
            VALUE(tot);
            // load
            while(st.size()<S){
                if (vq[station].size() > 0){
                    int a = vq[station].front();
                    vq[station].pop();
                    st.push(a);
                    timer++;
                }
                else{
                    break;
                }
            }
            if (tot != 0)
                timer +=2;
            
            station = station + 1 == N ? 0 : station + 1;
        }
        cout << timer << endl;
    }
    return 0;    
}