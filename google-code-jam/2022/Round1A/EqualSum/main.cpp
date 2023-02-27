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


int main(){
    int T; cin >> T;
    FOR(t,1,T+1){
        int N; cin >> N;
        vll myints;
        FOR(i,0,30){
            myints.push_back(pow(2, i));
        }
        myints.push_back(3);
        FOR(i,0,69){
            myints.push_back(1000000 + i*2);
        }
        
        FOR(i,0,N)
            cout << myints[i] << " ";
        cout << endl << flush;

        vll otherints(N);
        FOR(i,0,N)
            cin >> otherints[i];

        otherints.insert(otherints.end(), myints.begin()+31, myints.end());
        vll p1, p2;
        ll sum1 = 0, sum2 = 0;
        
        FOR(i,0,otherints.size()){
            if(sum1<=sum2){
                p1.push_back(otherints[i]);
                sum1+=otherints[i];
            }
            else{
                p2.push_back(otherints[i]);
                sum2+=otherints[i];
            }
        }

        // cerr << sum1 <<  " " << sum2 << endl;
        int i = 0;
        while ((sum1==sum2) && (i<min(p1.size(),p2.size()))){
            sum1-=p1[i];
            sum1+=p2[i];
            sum2+=p1[i];
            sum2-=p2[i];
            swap(p1[i], p2[i]);
            i++;
        }

        assert((sum1 != sum2));
        if (sum1 < sum2){
            swap(p1,p2);
            swap(sum1, sum2);
        }
        assert(((sum1-sum2) % 2) == 0);

        if ((sum1-sum2) % 4 == 2){
            sum1+=4;
            p1.push_back(1);
            p1.push_back(3);
        }
        else{
            sum1 += 3;
            sum2 += 1;
            p1.push_back(3);
            p2.push_back(1);
        }

        assert (((sum1 - sum2) % 4) == 2);

        ll diff = sum1 - sum2 - 2;
        assert((diff % 4) == 0);
        p2.push_back(pow(2, 29));
        sum2 += pow(2,29);

        ll diffhalf = diff / 2;
        assert ((diffhalf % 2) == 0);

        for (int i = 28; i >= 1; i--) {
            ll pow2i = pow(2,i);
            if (pow2i <= diffhalf) {
                diffhalf -= pow2i;
                p2.push_back(pow2i);
                sum2 += pow2i;
            }
            else{
                p1.push_back(pow2i);
                sum1 += pow2i;
            }
        }

        assert (diffhalf == 0);
        assert(sum1 == sum2);
        assert((p1.size() + p2.size()) == (2*N));

        for(auto i: p1){
            cout << i << " ";
        }
        cout << endl << flush;
    }
    
    return 0;
}