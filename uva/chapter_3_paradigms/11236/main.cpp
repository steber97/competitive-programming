#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

#define TESTING

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


int main(){
    int counter = 0;
    for(double i = 0.01; i<20.0; i=i+0.01){
        for(double j = i; j<20.0-i; j=j+0.01){
            for(double k = j; k<20.0-i-j; k=k+0.01){
                double d = double(i+j+k) / double((i*j*k) - double(1.0));

                if (d >= k-DELTA && (i+j+k+d)<=double(20.0+DELTA)){
                    double decimals = d - ((long long)(d+DELTA));
                    decimals *= double(100.0);
                    decimals = decimals - ((long long)(decimals+DELTA));
                    // if (abs(i-0.40)<DELTA && abs(j-1.51)<DELTA && abs(k-2.20)<DELTA){
                    //     cout << decimals;
                    //     exit(0);
                    // }
                    if (decimals <= DELTA && decimals >= -DELTA){
                        if ((d >= (0.01- double(DELTA))) && (d <= (double(20.0) + double(DELTA)))){
                            printf("%.2f %.2f %.2f %.2f\n", i, j, k, d);
                            counter++;
                        }
                    }
                }
            }
        }
    }
    // cout << counter << endl;
    return 0;
}