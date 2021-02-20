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


struct ScoreFunction {
    int time, rank;
    ll cum_sum;
    ScoreFunction(int t, int r, ll sum) : time(t), rank(r), cum_sum(sum) {
		
	}
    ScoreFunction() {

    }
};

struct Participant {
    int last_time, score;
    ll cum_sum;
    Participant() {

    }
};

bool ScoreFuncComp(int t, ScoreFunction& s1){
    return t < s1.time;
}

void print_score_func(unordered_map<int, vector<ScoreFunction>*>& score_funcs){
    for(auto iter: score_funcs){
        VALUE(iter.first);
        FOR(j,0,iter.second->size()){
            #ifdef TESTING
            cout << "time: " << iter.second->at(j).time << "\trank: " << iter.second->at(j).rank 
                    << "\tcum_sum: " << iter.second->at(j).cum_sum << endl;
            #endif
        }
    }
}

void print_parts(vector<Participant>& parts){
    FOR(i,0,parts.size()){
        #ifdef TESTING
        cout << i << "\tscore: " << parts[i].score << "\ttime: " << parts[i].last_time << "\tsum: " <<parts[i].cum_sum << endl;
        #endif
    }
}

int main(){

    int ws, ps;
    cin >> ps >> ws;
    VALUE(ps);
    VALUE(ws);
    vector<Participant> parts(ps);
    FOR(i,0,ps){
        parts[i].cum_sum=0LL;
        parts[i].last_time=0;
        parts[i].score=0;
    }
    int ups;
    cin >> ups;
    unordered_map<int, vector<ScoreFunction>*> score_funcs;
    if (ups == 0){
        // set all participants to rank 1
        FOR(i,0,ps){
            parts[i].score = 0;
            parts[i].last_time = 1;
            parts[i].cum_sum = 1LL;
        }
        score_funcs[0] = new vector<ScoreFunction>();
        score_funcs[0]->push_back(ScoreFunction(1, 1, 0LL));
    }
    else{
        // First cycle we do it by hand
        unordered_set<int> part_first_turn;
        FOR(j,0,ups){
            int p;
            cin >> p;
            p--;
            part_first_turn.insert(p);
            parts[p].score = 1;
            parts[p].cum_sum = 1LL;
            parts[p].last_time = 1;
        }
        FOR(j,0,ps){
            if (part_first_turn.find(j)==part_first_turn.end()){
                parts[j].score = 0;
                parts[j].last_time = 1;
                parts[j].cum_sum = (ll) part_first_turn.size() + 1LL;
            }
        }
        score_funcs[0] = new vector<ScoreFunction>();
        score_funcs[1] = new vector<ScoreFunction>();
        score_funcs[1]->push_back(ScoreFunction(1, 1, 0LL));
        score_funcs[0]->push_back(ScoreFunction(1, part_first_turn.size()+1, 0LL));
    }

    // print_score_func(score_funcs);
    print_parts(parts);
    
    FOR (w,2,ws+1){
        VALUE(w);
        int ups;
        unordered_map<int, int> ups_per_score;
        cin >> ups;
        vector<int> updates;
        FOR(j,0,ups){
            int p;
            cin >> p;
            p--;
            updates.push_back(p);
            int s = parts[p].score;
            if (score_funcs.find(s)==score_funcs.end()){
                score_funcs[s] = new vector<ScoreFunction>();
                score_funcs[s]->push_back(ScoreFunction(w, 1, 0L));
            }
            if (score_funcs.find(s+1)==score_funcs.end()){
                score_funcs[s+1] = new vector<ScoreFunction>();
                score_funcs[s+1]->push_back(ScoreFunction(w, 1, 0L));
            }
            if (ups_per_score.find(s)==ups_per_score.end()){
                ups_per_score[s] = 0;
            }
            ups_per_score[s] ++;

            // Update participant.
            // cum_sum must have all points done until time w (including w itself).

        }
        for (ii iter: ups_per_score){
            int actual_rank = score_funcs[iter.first]->back().rank;
            ll actual_sum =  score_funcs[iter.first]->back().cum_sum
                         + (((ll)w) - ((ll)score_funcs[iter.first]->back().time)) * ((ll)actual_rank);
            if (w == 1){
                // Handle special case for time == 1
                actual_sum = 0LL;
            }
            score_funcs[iter.first]->push_back(ScoreFunction(w, actual_rank + iter.second, actual_sum));
        }
        FOR(l,0,updates.size()){
            int p = updates[l];
            int s = parts[p].score;
            int index = upper_bound(score_funcs[s]->begin(), score_funcs[s]->end(), parts[p].last_time, ScoreFuncComp) - score_funcs[s]->begin();
            parts[p].cum_sum += (ll)score_funcs[s+1]->back().rank;      // last turn made with new score +1.
            parts[p].cum_sum += score_funcs[s]->back().cum_sum;
            parts[p].cum_sum -= score_funcs[s]->at(index).cum_sum;
            parts[p].cum_sum += (((ll)score_funcs[s]->at(index).time) - ((ll) parts[p].last_time) - 1LL) * 
                    ((ll) score_funcs[s]->at(index-1).rank);

            parts[p].score ++;
            parts[p].last_time = w;
        }
        // print_score_func(score_funcs);
        print_parts(parts);
    }
    FOR (i,0,score_funcs.size()){
        if (score_funcs[i]->back().time != ws){
            int actual_rank = score_funcs[i]->back().rank;
            ll actual_sum =  score_funcs[i]->back().cum_sum + ((ll)ws - (ll)score_funcs[i]->back().time) * ((ll)actual_rank);
            
            score_funcs[i]->push_back(ScoreFunction(ws, actual_rank, actual_sum));
        }
    }
    print_score_func(score_funcs);
    FOR(i,0,parts.size()){
        if (parts[i].last_time != ws){
            int s = parts[i].score;
            int index = upper_bound(score_funcs[s]->begin(), score_funcs[s]->end(), parts[i].last_time, ScoreFuncComp) - score_funcs[s]->begin();
            parts[i].cum_sum += (ll) score_funcs[parts[i].score]->back().rank;
            parts[i].cum_sum += score_funcs[parts[i].score]->back().cum_sum;
            parts[i].cum_sum -= score_funcs[parts[i].score]->at(index).cum_sum;
            parts[i].cum_sum += (((ll)score_funcs[s]->at(index).time) - ((ll)parts[i].last_time) - 1LL) * ((ll)score_funcs[s]->at(index-1).rank);
        }
        cout << fixed << setprecision(12) << (double)parts[i].cum_sum / (double)ws << endl;
    }

    

    


    return 0;
}