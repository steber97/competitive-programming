
#include <bits/stdc++.h>
#include <climits>

using namespace std;

#define TESTING

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


int main(){

    int N;
    cin >> N;
    vector<string> sentence(N);
    FOR(i,0,N){
        cin >> sentence[i];
    }

    int M;
    cin >> M;

    unordered_map<string,string> first;
    unordered_map<string,int> correct, total;

    FOR(i,0,M){
        string s1,s2,s3;
        cin >> s1 >> s2 >> s3;
        
        first[s1] = s2;

        if (total.find(s1)== total.end()){
            total[s1] = 0;
        }
        total[s1] ++;
        if (s3[0] == 'c'){
            // correct
            if (correct.find(s1) == correct.end()){
                correct[s1] = 0;
            }
            correct[s1]++;
        }
    }


    bool can_be_written = true;
    FOR(i,0,N){
        if (total[sentence[i]] != 1){
            can_be_written = false;
        }
    }

    //case 1
    if(!can_be_written){
        ll total_possibilities = 1LL;
        FOR(i,0,N){
            total_possibilities *= ll(total[sentence[i]]);
        }

        ll correct_possibilities = 1LL;
        FOR(i,0,N){
            correct_possibilities *= ll(correct[sentence[i]]);
        }

        cout << correct_possibilities << " correct" << endl << total_possibilities - correct_possibilities << " incorrect" << endl;
    }
    else{
        bool is_correct = true;
        FOR(i,0,N){
            cout << first[sentence[i]] << (i < N-1 ? " " : "");
            if (correct.find(sentence[i]) == correct.end()){
                is_correct = false;
            }
        }
        cout << endl << (is_correct ? "correct" : "incorrect") << endl;
    }

    return 0;
}