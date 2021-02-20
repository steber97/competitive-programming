#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

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
#define MODULUS 10000
#define DELTA 0.0000001

struct query{
    int q1, q2;   // query1, query2
    int p, r;   // player, reply
};

int other(int p){
    return (p + 1) % 2;  // the other player, either 1 or 0
}

bool in_set(const unordered_set<int>& s, int i){
    return s.find(i) != s.end();
}

bool rec_fairies(const vector<query>& queries, int i, unordered_set<int>& bv, vector<unordered_set<int>>& players){
    if (i == queries.size()){
        return true;
    }
    query q = queries[i];
    int o = other(q.p);  // other player
    // Case 1: the result of the query is 2:
    if (q.r == 2){
        if ( in_set(players[o], q.q1) || in_set(players[o], q.q2) || in_set(bv, q.q1) ||  in_set(bv, q.q2) ){
            // No one can have either q1 either q2;
            return false;
        }
        // Insert in the current player both queries
        players[q.p].insert(q.q1);
        players[q.p].insert(q.q2);
        return rec_fairies(queries, i+1, bv, players);
    }

    // Case 2: the result is 0
    if (q.r == 0){
        if (in_set(players[q.p], q.q1) || in_set(players[q.p], q.q2)){
            return false;
        }
        if (! in_set(bv, q.q1)){
            // q1 not in bv, it must be owned by the other player
            players[o].insert(q.q1);
        }
        if (! in_set(bv, q.q2)){
            // q2 not in bv, it must be owned by the other player
            players[o].insert(q.q2);
        }
        return rec_fairies(queries, i+1, bv, players);
    }

    if (q.r == 1){
        // tricky case
        if (in_set(players[q.p], q.q1) && in_set(players[q.p], q.q2) ){
            // player can't have both
            return false;
        }
        if ((in_set(players[o], q.q1) || in_set(bv, q.q1)) && (in_set(players[o], q.q2) || in_set(bv, q.q2) )){
            // The other player or bv have both queries.
            return false;
        }

        // case 1: the player has q1
        if (in_set(players[q.p], q.q1)){
            // then q2 is either in bv or in p2
            if (! in_set(bv, q.q2)){
                players[o].insert(q.q2);
            }
            return rec_fairies(queries, i+1, bv, players);
        }

        // case 2: the player has q2, same as above
        if (in_set(players[q.p], q.q2)){
            // then q1 is either in bv or in p2
            if (! in_set(bv, q.q1)){
                players[o].insert(q.q1);
            }
            return rec_fairies(queries, i+1, bv, players);
        }

        // case 3: q1 is either in bv or in other
        if(in_set(bv, q.q1) || in_set(players[o], q.q1)){
            // then current player must have q2
            players[q.p].insert(q.q2);
            return rec_fairies(queries, i+1, bv, players);
        }

        // case 4: q2 is either in bv or in other, same as above
        if(in_set(bv, q.q2) || in_set(players[o], q.q2)){
            // then current player must have q1
            players[q.p].insert(q.q1);
            return rec_fairies(queries, i+1, bv, players);
        }

        // base case, we can do backtrack
        // case 1: current player gets q1 and either bv either other player gets q2
        vector<unordered_set<int>> copy_players(2);
        for (int j = 0; j<2; j++){
            for (int el: players[j]){
                copy_players[j].insert(el);
            }
        }
        copy_players[q.p].insert(q.q1);
        copy_players[o].insert(q.q2);
        bool res1 = rec_fairies(queries, i+1, bv, copy_players);

        if (res1)
            return true;

        players[q.p].insert(q.q2);
        players[o].insert(q.q1);

        return rec_fairies(queries, i+1, bv, players);
    }
    return 1; // Totally useless, only to remove warning
}

int main(){

    int N;
    cin >> N;
    vector<query> queries(N);
    FOR(i,0,N){
        string s;
        int p, r;
        cin >> s >> p >> r;
        query q;
        q.p = p-1;
        q.r = r;
        q.q1 = s[0] - 'A';
        q.q2 = s[1] - 'A';
        queries[i] = q;
    }

    int res = 0;
    FOR(i, 0, 24){
        FOR(j, i+1, 25){
            FOR(k, j+1, 26){
                unordered_set<int> bv;  // black vienna
                vector<unordered_set<int>> players(2);   // player1, player2
                // Make all possibilities
                bv.insert(i);
                bv.insert(j);
                bv.insert(k);
                
                if (rec_fairies(queries, 0, bv, players)){
                    res++;
                }
            }
        }
    }

    // Output the result, the number of possible black viennas!
    cout << res << endl;
    return 0;
}