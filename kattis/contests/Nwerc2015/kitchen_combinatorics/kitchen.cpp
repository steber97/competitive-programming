
#include <bits/stdc++.h>
#include <climits>

using namespace std;

//#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)

#define MODULUS 100
#define MAX_VAL 1000000000000000000LL
int r,s,m,d,n;

vll brands;
vector<unordered_set<int>> start, mains, dessert;
vii incomp;
unordered_set<int> inc_set;

int map_pair_to_index(ii t){
    int res = 0;
    if (t.first <= s)
        res += t.first;
    if (t.second <= s)
        res += t.second;
    if (t.first > s and t.first <= s+m)
        res += (t.first - s) * MODULUS;
    if (t.second > s and t.second <= s+m)
        res += (t.second - s) * MODULUS;

    if (t.first > s+m and t.first <= s+m+d)
        res += (t.first-s-m) * MODULUS * MODULUS;

    if (t.second > s+m and t.second <= s+m+d)
        res += (t.second - s -m) * MODULUS * MODULUS;

    return res;
}


int main(){

    cin >> r >> s >> m >> d >> n;

    VALUE(s);
    VALUE(m);
    VALUE(d);

    brands.resize(r);
    start.resize(s, unordered_set<int>());
    mains.resize(m, unordered_set<int>());
    dessert.resize(d, unordered_set<int>());
    incomp.resize(n);

    FOR(i,0,r)
        cin >> brands[i];
    
    FOR(i, 0, s){
        int temp;
        cin >> temp;
        FOR(j,0,temp){
            int t;
            cin >> t;
            start[i].insert(t);
        }
    }

    FOR(i, 0, m){
        int temp;
        cin >> temp;
        FOR(j,0,temp){
            int t;
            cin >> t;
            mains[i].insert(t);
        }
    }

    FOR(i, 0, d){
        int temp;
        cin >> temp;
        FOR(j,0,temp){
            int t;
            cin >> t;
            dessert[i].insert(t);
        }
    }

    FOR(i,0,n){
        ii t;
        cin >> t.first >> t.second;
        if (t.first > t.second){
            // swap
            int t2 = t.first;
            t.first = t.second;
            t.second = t2;
        }
        incomp[i] = t;
        inc_set.insert(map_pair_to_index(t));       // Ad incompatible pair to unordered set.
    }

    for(auto el: inc_set){
        VALUE(el);
    }

    // INPUT TAKEN, now go on!
    ll res = 0LL;
    bool finish = false;
    FOR(i,1,s+1){
        if (finish)
            break;
        FOR(j,1,m+1){
            if (finish)
                break;
            FOR(k,1,d+1){
                ii p1,p2,p3;
                p1 = {i, j+s};
                p2 = {i, k+m+s};
                p3 = {j+s, k+m+s};

                if (inc_set.find(map_pair_to_index(p1))!=inc_set.end() or inc_set.find(map_pair_to_index(p2))!=inc_set.end() or inc_set.find(map_pair_to_index(p3))!=inc_set.end() ){
                   
                    continue;      // Found taboo matching
                }

                ll res1=1LL, res2=1LL, res3 = 1LL;

                for (auto i1: start[i-1]){
                    long double t = (long double)(MAX_VAL) / (long double)(res1);
                    res1 *= brands[i1-1];
                    if (res1 > MAX_VAL or res2 > MAX_VAL or res3 > MAX_VAL or double (brands[i1-1]) > t+1.0){
                        finish = true;
                        break;
                    }
                }
                for (auto i2: mains[j-1]){
                    long double t = (long double)(MAX_VAL) / (long double)(res2);
                    res2 *= ( start[i-1].find(i2) == start[i-1].end() ? brands[i2-1] : 1LL);
                    if (res1 > MAX_VAL or res2 > MAX_VAL or res3 > MAX_VAL  or double (brands[i2-1]) > t+1.0){
                        finish = true;
                        break;
                    }
                }
                for (auto i3: dessert[k-1]){
                    long double t = (long double)(MAX_VAL) / (long double)(res3);
                    res3 *= ( start[i-1].find(i3) == start[i-1].end() and mains[j-1].find(i3) == mains[j-1].end() ? brands[i3-1] : 1LL);
                    if (res1 > MAX_VAL or res2 > MAX_VAL or res3 > MAX_VAL  or double (brands[i3-1]) > t+1.0){
                        finish = true;
                        break;
                    }
                }

                ll m1, m2;
                ll temp2 = 1LL;
                
                m1 = MAX_VAL / res1;

                if (res2 > m1 + 1LL){
                    finish = true;
                    break;
                }
                else{
                    temp2 = res1 * res2;
                }

                m1 = MAX_VAL / temp2;

                if (res3 > m1 + 1LL){
                    
                    finish = true;
                    break;
                }
                else{
                    temp2 *= res3;
                }
                

                res += temp2;
                if (res > MAX_VAL){
                    finish = true;
                    break;
                }
                
                
            }
        }
    }

    if (finish){
        cout << "too many" << endl;
    }
    else{
        cout << res << endl; 
    }

    return 0;
}