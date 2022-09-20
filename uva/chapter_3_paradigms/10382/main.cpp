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


bool compare(pair<double, double>& p1, pair<double, double>& p2){
    if (abs(p1.first - p2.first) > DELTA)
        return p1.first < p2.first;
    return p1.second < p2.second;
}


int main(){
    
    while(true){
        int n,l,w;
        cin >> n >> l >> w;
        if (cin.eof())
            break;

        vector<pair<double, double>> sprinkles;        
        FOR(i,0,n){
            double a,b;
            cin >> a >> b;
            
            if (b >= ((double(w)/double(2))+DELTA))
                sprinkles.push_back({a - pow((b*b - pow(double(w)/2.0, 2)), 0.5), a + pow((b*b - pow(double(w)/2.0, 2)), 0.5)});
            
        }
        
        sort(sprinkles.begin(), sprinkles.end(), compare);
        FOR(j,0,sprinkles.size())
            PAIR(sprinkles[j]);

        int result = 0;
        double pos = 0.0;
        int i = 0;
        bool finish = false;
        
        if (l == 0){
            cout << 0 << endl;
            finish = true;
        }
        while(!finish){
            int best = -1;
            FOR(j,i,sprinkles.size()){
                if (sprinkles[j].first >= pos+DELTA){
                    break;
                }
                i++;
                if (sprinkles[j].second >= pos+DELTA){
                    if(best == -1)
                        best = j;
                    else if(sprinkles[best].second < sprinkles[j].second)
                        best = j;
                }
            }
            if (best == -1){
                finish = true;
                cout << -1 << endl;
            } 
            else if (sprinkles[best].second <= l - DELTA){
                result++;
                pos = sprinkles[best].second;
            }
            else{
                cout << result + 1 << endl;
                finish = true;
            }
        }


    }
    
    return 0;
}