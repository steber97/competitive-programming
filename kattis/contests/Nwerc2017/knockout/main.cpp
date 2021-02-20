
#include <bits/stdc++.h>
#include <climits>

using namespace std;

// #define TESTING

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
#define EPS 0.000000000005
#define EPS2 0.000000

vector<vector<long double>> dp;

int myPow(int x, unsigned int p)
{
  if (p == 0) return 1;
  if (p == 1) return x;
  
  int tmp = myPow(x, p/2);
  if (p%2 == 0) return tmp * tmp;
  else return x * tmp * tmp;
}

long double compute_prob(int id, int lev, vi & players){
    
    if (abs(dp[id][lev] + ((long double)(1.0))) > EPS){
        // Return
    }
    else {
        long double result = (long double) 0.0;
        int child = id / myPow(2, lev-1);
        int other = child % 2 == 0 ? child + 1 : child - 1;
        if (players[id] == 0){
            dp[id][lev] = (long double) 0.0;    
        }
        else{
            for (int i = other * myPow(2, lev-1);
                i <= other * myPow(2, lev-1) + myPow(2, lev-1) - 1; 
                i++){
                result += compute_prob(id, lev-1, players) * \
                    ((long double)players[id]) / ((long double)(players[id] + players[i])) * \
                    compute_prob(i, lev-1, players);
            }
            if ((abs(result) < EPS) and (players[id] != 0)){
                result = dp[id][lev-1];
            }
            dp[id][lev] = result;
        }
        VALUE(id);
        VALUE(lev);
        VALUE(dp[id][lev]);
    }
    return dp[id][lev];
}

int main(){

    int N;
    cin >> N;

    vi players_in(N), players;
    FOR(i,0,N){
        cin >> players_in[i];
    }
    swap(players_in[0], players_in[N-1]);

    sort(players_in.begin(), players_in.end()-1, greater<int>());

    if ( ceil(log2(N)) != floor(log2(N))){
        VALUE(N);
        VALUE(floor(log2(N)));
        VALUE(ceil(log2(N)));
        VALUE( (N - myPow(2, int(floor(log2(N))))) * 2);
        FOR(i,0,N){
            players.push_back(players_in[i]);
            if (i >= (N - myPow(2, int(floor(log2(N))))) * 2){
                players.push_back(0);
            }
        }
        swap(players[players.size()-1], players[players.size()-2]);
        N = players.size();
    }
    else{
        players = players_in;
    }

    VECT(players_in);
    VECT(players);

    // Initialize to -1 the dynamic programming table.
    dp.resize(N, vector<long double>(int(log2(N)) + 1, (long double)-1.0));
    FOR(i, 0, N){
        dp[i][0] = (long double)1.0;
    }

    cout << fixed << setprecision(10) << compute_prob(N-1, int(log2(N)), players) << endl;

    return 0;
}