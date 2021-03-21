#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TESTING

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

string no_asterisks(unordered_set<string>& no_asterisks, vector<string>& p){
    // first, all strings must be equal.
    string result;
    for(string i: no_asterisks){
        for (string j: no_asterisks){
            if(i.compare(j) != 0){
                return "*";
            }
            result = i;
        }
    }
    
    for(string s: p){
        if (s.compare(result) != 0){
            string segment = "";
            int first = 0;
            FOR(i,0,s.size()){
                if (s[i] == '*'){
                    if (segment.size() > 0) {
                        int pos = result.find(segment, first);
                        if (pos == string::npos){
                            return "*";
                        }
                        first = pos + segment.size();
                        segment = "";
                    }
                }
                else{
                    segment += s[i];
                    if (i == s.size()-1){
                        // it is the last one!
                        if (first > result.size() - segment.size()){
                            return "*";
                        }
                        if (result.find(segment, result.size()-segment.size()) == string::npos)
                            return "*";
                    }
                }
            }
        }
    }
    return result;
}

string asterisks(vector<string>& p){
    string prefix = "";
    string suffix = "";
    unordered_set<int> done_forward, done_backwards;
    string result;
    int j = 0;
    while(done_forward.size() < p.size()){
        FOR(i,0,p.size()){
            if (done_forward.find(i) == done_forward.end()){
                if (p[i][j] == '*'){
                    done_forward.insert(i);
                }
                else if (p[i].substr(0, prefix.size()).compare(prefix) == 0){
                    prefix = p[i].substr(0, j+1);
                }
                else {
                    return "*";
                }
            }
        }
        j++;
    }

    j = 0;
    while(done_backwards.size() < p.size()){
        FOR(i,0,p.size()){
            if (done_backwards.find(i) == done_backwards.end()){
                if (p[i][p[i].size()- j - 1] == '*'){
                    done_backwards.insert(i);
                }
                else if (p[i].substr(p[i].size() -  suffix.size(), suffix.size()).compare(suffix) == 0){
                    suffix = p[i].substr(p[i].size() - j - 1);
                }
                else {
                    return "*";
                }
            }
        }
        j++;
    }

    result += prefix;

    FOR(i,0,p.size()){
        int last_ast = -1;
        FOR(j,0,p[i].size()){
            if (p[i][j] == '*'){
                if (last_ast == -1){

                }
                else{
                    result += (p[i].substr(last_ast+1, j - last_ast - 1));
                }
                last_ast = j;
            }
        }
    }
    result += suffix;
    return  result;
}


int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int N;
        cin >> N;
        vector<string> p(N);
        unordered_set<string> no_asterisk;
        FOR(i,0,N){
            cin >> p[i];
            if (p[i].find("*") == string::npos){
                no_asterisk.insert(p[i]);
            }
        }
        
        // Case 1, there are vectors with no asterisks.
        if (no_asterisk.size() > 0){
            string result = no_asterisks(no_asterisk, p);
            cout << "Case #" << t+1 << ": " << result << endl;
        }
        else{
            string result = asterisks(p);
            cout << "Case #" << t+1 << ": " << result << endl;
        }

    }
    return 0;
}