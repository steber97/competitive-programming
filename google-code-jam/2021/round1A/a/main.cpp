#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>
#include <random>

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
    FOR(t,0,T)   {
        int n;
        cin >> n;
        vll numbers(n);
        vector<string> numbers_str(n);
        FOR(i,0,n){
            cin >> numbers[i];
            numbers_str[i] = to_string(numbers[i]);
        }
        int counter=0;
        FOR(i,1,n){
            if ((numbers_str[i].size() > numbers_str[i-1].size()) || 
                    ((numbers_str[i].size() == numbers_str[i-1].size()) && (numbers_str[i].compare(numbers_str[i-1]) > 0 ))){
                ; // Do nothing
            }
            else if ((numbers_str[i].size() == numbers_str[i-1].size()) && (numbers_str[i].compare(numbers_str[i-1]) == 0 )){
                numbers_str[i].push_back('0');
                counter += 1;
            }
            else if (numbers_str[i].size() == numbers_str[i-1].size()){
                numbers_str[i].push_back('0');
                counter += 1;
            }
            else if (numbers_str[i].size() < numbers_str[i-1].size()){
                string up = numbers_str[i-1].substr(0, numbers_str[i].size());
                VALUE(up);
                if (up.compare(numbers_str[i]) < 0){
                    // case 110, 12
                    // Add zeros
                    FOR(j,0,numbers_str[i-1].size()-up.size()){
                        numbers_str[i].push_back('0');
                        counter ++;
                    }
                }
                else if (up.compare(numbers_str[i]) > 0){
                    // case 120, 11, add zeros
                    FOR(j,0,numbers_str[i-1].size()-up.size() + 1){
                        numbers_str[i].push_back('0');
                        counter ++;
                    }
                }
                else if (up.compare(numbers_str[i]) == 0){
                    // case 119, 11 or 11667, 116
                    string remainder = numbers_str[i-1].substr(up.size());
                    string modulus = "";
                    FOR(i,0,remainder.size())
                        modulus.push_back('9');
                    VALUE(remainder); VALUE(modulus);
                    if (remainder.compare(modulus) != 0){
                        for(int i = remainder.size()-1; i>=0; i--){
                            remainder[i] = remainder[i] + 1;
                            if (remainder[i] != '0')
                                break;
                        }
                        numbers_str[i].append(remainder);
                        counter += numbers_str[i-1].size()-up.size();
                    }
                    else{
                        FOR(j,0,numbers_str[i-1].size()-up.size()+1)
                            numbers_str[i].push_back('0');
                        counter += numbers_str[i-1].size()-up.size()+1;
                    }
                }
            }
            COUT(numbers[i]); COUT(" "); COUT(numbers_str[i]); COUT(endl);
        }
        cout << "Case #" << t+1 << ": " << counter << endl;
    }

    return 0;
}