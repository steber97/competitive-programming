#include <bits/stdc++.h>
#include <climits>

using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)


ll n,r,p;
vll DP;


long long recursive(long long num){
    //cout << num << endl;
    if (DP[num] != LONG_LONG_MAX){
        //cout << "ciao" << endl;
        return DP[num];
    }
    else if(num == 1){
        //cout << "ciao2" << endl;
        return 0;
    }
    else{
        FOR(i, 2, num+1){
            long long temp = recursive((num % i == 0 ? num/i : (num/i)+1));
            DP[num] = min(DP[num], temp + (i-1)*p + r );
        }
        return DP[num];
    }
}


int main(){

    cin >> n >> r >> p;

    DP.resize(n+1, LONG_LONG_MAX);
    long long res = recursive(n);

    cout << res << endl;

    return 0;
}