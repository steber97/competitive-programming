#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>

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

pair<vi, int> understand_possibility(vi& v){
    if (v.size() == 0){
        return {v, 10};
    }
    vvi four_pos(4, vi());
    // array as it is
    FOR(i,0,v.size())
        four_pos[0].push_back(v[i]);
    // reversed
    FOR(i,0,v.size())
        four_pos[1].push_back(v[v.size()-1-i]);
    // flipped
    FOR(i,0,v.size())
        four_pos[2].push_back(v[i]==1?0:1);
    //flipped reversed
    FOR(i,0,v.size())
        four_pos[3].push_back(v[v.size()-1-i]==1?0:1);

    // always ask for the first
    cout << 1 << endl << flush;
    int judge;
    cin >> judge;
    vvi second_query;
    FOR(i,0,4){
        if(four_pos[i][0] == judge)
            second_query.push_back(four_pos[i]);
    }

    FOR(i,0,v.size()){
        if (second_query[0][i] != second_query[1][i]){
            cout << i+1 << endl << flush;
            cin >> judge;
            if (judge == second_query[0][i]){
                return {second_query[0], 8};
            }
            else{
                return {second_query[1], 8};
            }
        }
    }
    // Still consume at random a query
    cout << 1 << endl << flush;
    cin >> judge;
    return {second_query[0], 8};
}

int main(){
    int T,B;
    cin >> T >> B;

    cerr << T << " " << B << endl;
    FOR(t,0,T){
        int done = 0;
        bool finished = false;
        vi new_res(0);
        while(!finished){
            pair<vi, int> p = understand_possibility(new_res); // vi the correct possibiltiy, int: the amount of remaining queries.

            vi pos = p.first;
            int remaining_queries = p.second;
            
            new_res.resize(0);   // set it from scratch again
            if (B - done < remaining_queries)
                remaining_queries = B-done;
            FOR(i,0,pos.size()/2){
                new_res.push_back(pos[i]);
            }
            
            FOR(i,0,remaining_queries){
                done ++;
                int tmp;
                if (i < remaining_queries/2){
                    cerr << pos.size()/2 + i + 1 << endl;
                    cout << pos.size()/2 + i + 1 << endl << flush;
                }
                else{
                    cerr << B - pos.size()/2 - remaining_queries + i + 1 << endl;
                    cout << B - pos.size()/2 - remaining_queries + i + 1 << endl << flush;
                }
                cin >> tmp;
                new_res.push_back(tmp);
            }
            FOR(i,pos.size()/2,pos.size()){
                new_res.push_back(pos[i]);
            }
            if (done == B){
                string result;
                FOR(i,0,new_res.size()){
                    char tmp = new_res[i] == 0 ? '0' : '1';
                    result += tmp;
                }
                cout << result << endl << flush;
                finished = true;
                char judge_answer;
                cin >> judge_answer;
                if (judge_answer == 'Y'){
                    // we can stop correct answer
                }
                else{
                    // wrong answer, we should stop
                    return 0;
                }
            }
            
        }
    }
    return 0;
}