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

int n, u, r, d, l;
vi blacks(4);
// 0->top, 1->right, 2->bottom, 3->left
bool fatina (int pos, vb corner){
    if (pos == 0){
        if (u == n){
            vb corner = {true, true, false, false};
            return fatina(pos+1, corner);
        }
        if (blacks[pos] == 0){
            vb corner = {false, false, false, false};
            return fatina(pos+1, corner);
        }
        if (blacks[pos] == n-1){
            vb corner = {false, true, false, false};
            bool res = fatina(pos+1, corner);
            corner = {true, false, false, false};
            res = fatina(pos+1, corner) or res;
            if (n-1 >= 2){
                corner = {true, true, false, false};
                res = fatina(pos+1, corner) or res;
            }
            return res;
        }
        vb corner = {false, false, false, false};
        bool res = fatina(pos+1, corner);
        corner = {true, false, false, false};
        res = fatina(pos+1, corner) or res;
        corner = {false, true, false, false};
        res = fatina(pos+1, corner) or res;
        if (blacks[pos] > 1){
            corner = {true, true, false, false};
            res = fatina(pos+1, corner) or res;
        }
        return res;
    }
    if (pos == 3){
        if ((corner[0]==true) and (corner[3]==true) and (l<2)){
            return false;
        }
        else if ((corner[0]==false) and (corner[3]==false) and (l>n-2)){
            return false;
        }
        else if (((corner[0] == false) and (corner[3]==true)) or ((corner[0] == true) and (corner[3]==false))){
            if (l == n)
                return false;
            if (l==0)
                return false;
        }
        return true;
    }
    if (corner[pos] == true){
        if (blacks[pos] == 0){
            return false;
        }
        if (blacks[pos] == n){
            corner[pos+1] = true;
            return fatina(pos+1, corner);
        }
        if (blacks[pos] == 1){
            corner[pos+1]=false;
            return fatina(pos+1, corner);
        }
        corner[pos+1] = false;
        bool res = fatina(pos+1, corner);
        corner[pos+1] = true;
        res = fatina(pos+1, corner) or res;
        return res;
    }
    else{
        if (blacks[pos] == n){
            return false;
        }
        if (blacks[pos] == n-1){
            corner[pos+1] = true;
            return fatina(pos+1, corner);
        }
        if (blacks[pos] == 0){
            corner[pos+1] = false;
            return fatina(pos+1, corner);
        }
        corner[pos+1] = false;
        bool res = fatina(pos+1, corner);
        corner[pos+1] = true;
        res = fatina(pos+1, corner) or res;
        return res;
    }
}


int main(){

    int T;
    cin >> T;
    FOR(t,0,T) {

        cin >> n >> u >> r >> d >> l;
        blacks[0]=u;
        blacks[1]=r;
        blacks[2]=d;
        blacks[3]=l;
        vb corner(4);
        if (fatina(0, corner)){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }
    return 0;    
}