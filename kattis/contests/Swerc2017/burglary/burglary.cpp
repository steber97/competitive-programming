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

int binary_search_left(int i, vi&shelf){
    int s,e;
    s=0; e=i;

    if (shelf[i] != (i == 0? 0 : shelf[i-1])){
        return i;
    }

    while(s!=e){
        int half= (s+e)/2;
        //VALUE(half);
        if (shelf[half] == shelf[i]){
            e = half;
        }
        else{
            s = half+1;
        }
    }

    return s;
}

int binary_search_right(int i, vi& shelf){
    int e=shelf.size()-1; int s = i;
    if (shelf[i] != (i == 0? 0 : shelf[i-1])){
        return i;
    }
    while(s!=e){
        int half = (s+e)/2;
        if (shelf[half] == shelf[i]){
            s = half+1;
        }
        else
            e = half;
    }
    return s;
}

int count_jars(int j, int k, int f, int g, vi& shelf, vi& ladder1, vi& ladder2, vvi& DP, vii& ladders_limit1, vii& ladders_limit2){
    
    int m1 = max(ladder1[j],ladder2[f]);
    int m2 = min(ladder1[k],ladder2[g]);
    
    if (m1 < m2){
        // easy part! :)
        
        int l1,l2,r1,r2;
        
        if (ladder1[j] > ladder2[f]){
            r1 = ladders_limit1[j].second;
            l1 = ladders_limit2[f].first;
        }
        else {
            l1 = ladders_limit1[j].first;
            r1 = ladders_limit2[f].second;
        }
        
        if(ladder1[k] > ladder2[g]){
            l2 = ladders_limit2[g].first;
            r2 = ladders_limit1[k].second;
        }
        else{
            l2 = ladders_limit1[k].first;
            r2 = ladders_limit2[g].second;
        }

        // conflict
        if (l2 > r1){
            // no conflicts
            return shelf[r1] - (l1 == 0? 0 : shelf[l1-1]) + shelf[r2] - (l2 == 0? 0 : shelf[l2-1]) + DP[f][g] ;
        }
        else{
            return shelf[r1] - (l1 == 0? 0 : shelf[l1-1]) + shelf[r2] - (l2 == 0? 0 : shelf[l2-1]) + DP[f][g] - (shelf[r1] - (l2 == 0? 0:shelf[l2-1])); 
        }
    }
    else{
        
        // bad shit happens here!
        if (shelf[m1] - (m2 == 0? 0 : shelf[m2-1])  == 0){
            // good, we can take it!

            int left, right;

            if (ladder1[j] < ladder2[f])
                left = ladders_limit1[j].first;
            else
                left = ladders_limit2[f].first;

            if (ladder1[k] > ladder2[g])
                right = ladders_limit1[k].second;
            else
                right = ladders_limit2[g].second;
        
            return shelf[right] - (left == 0? 0 : shelf[left-1]) + DP[f][g];

        }
        else{
            // we may only take the stuff on the current floor, without going downstairs.


            int pos1 = ladders_limit1[j].first;
            int pos2 = ladders_limit1[k].second;
            int res = (shelf[pos2] - (pos1 == 0 ? 0 : shelf[pos1-1]));
            return res;
        }
        
    }
    return 0;
}


int main(){

    int N,M;     // shelves, slots;
    cin >> N >> M;

    vvi shelves(N, vi(M,0));

    vvi ladders(N, vi());

    FOR(i,0,N){
        FOR(j,0,M){
            char t;
            cin >> t;
            if (t == '-'){
                // counts as null;
                // do nothing
                if (j == 0){
                    shelves[i][j] = 0;
                }
                else{
                    shelves[i][j] = shelves[i][j-1];
                }
            }
            else{
                // found value
                int t_i = t - char('0');
                if (j == 0){
                    shelves[i][j] = t_i;
                }
                else{
                    shelves[i][j] = shelves[i][j-1] + t_i;
                }
            }
        }
        FOR(j,0,M){
            // read ladders
            char t;
            cin >> t;
            if(t == '|'){
                // found ladder
                ladders[i].push_back(j);
            }
        }
    }



    vvi DP1, DP2;

    // base case
    DP1.resize(ladders[N-1].size(), vi());
    FOR(j,0,DP1.size()){
        DP1[j].resize(ladders[N-1].size(), 0);
    }
    DP1.resize(ladders[N-1].size(), vi(ladders[N-1].size(), 0));
    int res;
    for(int i = N-1; i>=0; i--){  
        if (i != 0){
            // precompute grab:
            
            vii ladders_limit_1(ladders[i-1].size(), {0,0});
            vii ladders_limit_2(ladders[i].size(), {0,0});
            FOR(t,0,ladders[i-1].size()){
                ladders_limit_1[t].first = binary_search_left(ladders[i-1][t], shelves[i]);
                ladders_limit_1[t].second = binary_search_right(ladders[i-1][t], shelves[i]);
            }
            FOR(t,0,ladders[i].size()){
                ladders_limit_2[t].first = binary_search_left(ladders[i][t], shelves[i]);
                ladders_limit_2[t].second = binary_search_right(ladders[i][t], shelves[i]);
            }

            DP2.resize(ladders[i-1].size(), vi());
            FOR(j,0,DP2.size()){
                DP2[j].resize(ladders[i-1].size());
            }
            FOR(j,0,ladders[i-1].size()){
                FOR(k,j,ladders[i-1].size()){
                    DP2[j][k] = -INF;
                    VALUE(j);
                    VALUE(k);
                    FOR(f,0,ladders[i].size()){
                        FOR(g,f,ladders[i].size()){
                            int res = count_jars(j,k,f,g,shelves[i], ladders[i-1], ladders[i], DP1, ladders_limit_1, ladders_limit_2);
                            DP2[j][k] = max(
                                DP2[j][k],
                                res
                            );
                        }
                    }
                }
            }
            //cout << "DP2 " << DP2.size() << " " << DP2[0].size() << " " << (DP2.size()>0? DP2[1].size() : -1) <<   endl;
            /*
            FOR(x,0,DP2.size()){
                FOR(y,0,DP2[x].size()){
                    COUT(DP2[x][y]) ;
                    COUT("\t");
                }
                COUT (endl);
            }*/
            DP1 = DP2;
        }
        else{
            // its a bit of a messy code
            res = 0;
            FOR(j,0,ladders[0].size()){
                FOR(k,j,ladders[0].size()){
                    res = max(res, DP1[j][k]);
                }
            }
        }
        
    }
    cout << res << endl;
    return 0;
}