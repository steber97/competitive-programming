#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <algorithm>

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

vi compute_cumul(vi& a, vi& b){
    vi res(a.size());
    int i = a.size()-1;
    int j = b.size()-1;
    while(i >= 0 and j >= 0){
        if (a[i] == b[j]){
            res[i] = (i < a.size()-1 ? res[i+1] : 0) + 1;
            i--; j--;
        }
        else if (a[i] > b[j]){
            res[i] = (i < a.size()-1 ? res[i+1] : 0);
            i--;
        }
        else{
            j--;
        }
    }
    if (i >= 0){
        for (int k = i; k>= 0; k--){
            res[k] = (k < a.size()-1 ? res[k+1] : 0);
        }
    }
    return res;
}

// count in [start, end[
int count_interval(int start, int end, vi& v){
    int low = (lower_bound(v.begin(), v.end(), start) - v.begin());
    int up = (lower_bound(v.begin(), v.end(), end) - v.begin() - 1);
    return up - low + 1;
}

int fatina(vi& a, vi& b){
    if (a.size()==0){
        return 0;
    }

    vi cumulative = compute_cumul(a,b);

    int result = cumulative[0];
    
    int old_head = a[0];
    int len_tail = 1;

    FOR(i,0,b.size()){
        if (b[i] < old_head){
            ;
        }
        else{
            int start=old_head+len_tail;
            int end=b[i]+len_tail;
            int to_move = count_interval(start, end, a);
            int tot_to_move = to_move;
            while(to_move != 0){
                start = end;
                end = end + to_move;
                to_move = count_interval(start, end, a);
                tot_to_move += to_move;
            }
            old_head = b[i];
            len_tail += tot_to_move;
            int to_add = (len_tail < a.size() ? cumulative[len_tail] : 0);
            result = max(
                result,
                count_interval(old_head, old_head+len_tail, b) + to_add
            );
            VECT(a);
            VALUE(i);
            VALUE(old_head);
            VALUE(len_tail);
            VALUE(tot_to_move);
            VALUE(result);
        }
    }

    // TODO: REMOVE THIS
    return result;
}


int main(){

    int T;
    cin >> T;
    FOR(t,0,T){
        int n,m;
        cin >> n >> m ;
        vi a_pos, a_neg;
        vi b_pos, b_neg;
        FOR(i,0,n){
            int temp;
            cin >> temp;
            if (temp >= 0){
                a_pos.push_back(temp);
            }
            else{
                a_neg.push_back(-temp);
            }
        }
            
        FOR(i,0,m){
            int temp;
            cin >> temp;
            if (temp >= 0){
                b_pos.push_back(temp);
            }
            else{
                b_neg.push_back(-temp);
            }
        }

        std::reverse(a_neg.begin(), a_neg.end());
        std::reverse(b_neg.begin(), b_neg.end());
        int res = fatina(a_pos, b_pos);
        res += fatina(a_neg, b_neg);
        cout << res << endl;
       
        
    }

    return 0;    
}