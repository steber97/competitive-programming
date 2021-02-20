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


int main(){

    int n;
    cin >> n;
    vector<long long> v(n);
    for (int i = 0; i<n; i++){
        cin>>v[i];
    }

    int left = 1;
    int right = 1;
    bool taken = false;
    bool second = false;
    int start  = 1;
    while(true){
        
        VALUE(start);
        for (int i = start ; i<n; i++){
            // cout << "\t" <<v[i] << endl;
            if (v[i] >= v[i-1]){
                ;
            }
            else{
                if (taken == true){
                    cout << "impossible" << endl;
                    return 0;
                }
                taken = true;
                left = i;
                break;
            }
        }
        if(second){
            cout << left+1 << " " << right+1 << endl;
            return 0; 
        }
        if (!taken){
            cout << 1 << " " << 1 << endl;
            return 0;
        }
        else{
            VALUE(left);
            // Look for when we stop decreasing.
            right = left;
            for (int j = left+1; j<n; j++){
                if (v[j] <= v[j-1]){
                    right ++;
                }
                else{
                    break;
                }
            }
            for (int j = left; j>=1; j--){
                if (v[j-1] >= v[j] ){
                    left --;
                }
                else{
                    break;
                }
            }
            VALUE(left);
            VALUE(right);
            if ((left > 0)
            && (right < n-1) && 
            (v[left]<=v[right+1]) && 
            (v[right]>=v[left-1])){
                // cout << left+1 <<  " "<< right+1 << endl;
                start = right+1;
            }
            else if ((left == 0) && (right == n-1)){
                // cout << left+1 <<  " "<< right+1 << endl;
                start = right+1;

            } 
            else if ((left == 0) &&(v[left]<=v[right+1])){
                // cout << left+1 <<  " "<< right+1 << endl;
                start = right+1;
            }
            else if ((right==n-1) && (v[right]>= v[left-1])){
                // cout << left+1 <<  " "<< right+1 << endl;
                start = right+1;
            }
            else{
                cout << "impossible" << endl;
                return 0;
            }
        }
        second = true;
    }
    
    return 0;
}