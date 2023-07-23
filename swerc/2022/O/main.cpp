#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

//#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << endl; cout << endl
#define VECTWalls(x) for (int u = 0; u<x.size(); u++) cout << x[u].r1 << "\t" << x[u].r2 << "\t" << x[u].a << endl; cout << endl
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#define VECTWalls(x)
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

struct Circ{
    int a1, a2, r;
};

struct Vert{
    int r1, r2, a;
};

bool compare_vert_walls(Vert v1, Vert v2){
    assert (v1.a!=v2.a);
    return v1.a < v2.a;
}

int main(){
    int T;
    cin >> T;
    FOR(t, 0, T){
        vector<Circ> circ;
        vector<Vert> vert;
        int W;
        cin >> W;
        bool no = false;
        FOR(w,0,W){
            char t;
            int a,b,c;
            cin >> t >> a >> b >> c;
            if (t == 'C'){
                Circ ci;
                ci.r = a;
                ci.a1 = b;
                ci.a2 = c;
                circ.push_back(ci);
            }
            else{
                Vert ve;
                ve.r1 = a;
                ve.r2 = b;
                ve.a = c;
                int below = -1;
                int above = -1;
                FOR(j,0,vert.size()){
                    if (vert[j].a == ve.a){
                        if (vert[j].r1 == ve.r2){
                            above = j;
                        }
                        if (vert[j].r2 == ve.r1){
                            below = j;
                        }
                    }
                }
                if (above != -1 && below != -1){
                    vert[above].r1 = vert[below].r1;
                    swap(vert[below], vert[vert.size()-1]);
                    vert.resize(vert.size()-1);
                    // VECTWalls(vert);
                    // COUT("Something went wrong");
                    // exit(0);
                }
                else if (above != -1){
                    vert[above].r1 = ve.r1;
                }
                else if (below != -1){
                    vert[below].r2 = ve.r2;
                }
                else{
                    vert.push_back(ve);
                }
            }
        }
        
        vector<vector<bool>> grid(21, vector<bool>(360, false));
        for(int i = 0; i < circ.size(); i++){
            int j = circ[i].a1;
            while(j != circ[i].a2){
                grid[circ[i].r][j] = true;
                j+=1;
                j=(j==360?0:j);
            }
        }

        for(int i = 0; i < 20; i++){
            vector<Vert> walls;
            FOR(j,0,vert.size()){
                if (vert[j].r1<=i && vert[j].r2 >= i+1){
                    Vert tmp;
                    tmp.a = vert[j].a; tmp.r1 = vert[j].r1; tmp.r2=vert[j].r2;
                    walls.push_back(tmp);
                }
            }
            if (walls.size() <= 1){

            }
            else{
                sort(walls.begin(), walls.end(), compare_vert_walls);
                
                vector<bool> reachable(360, false);
                FOR(j,0,walls.size()){
                    int l = walls[j].a;
                    bool reach = false;
                    int next=j+1==walls.size()?0:j+1;
                    while(l!=walls[next].a){
                        if (!grid[i][l])
                            reach = true;
                        l++;
                        l = (l==360?0:l);
                    }
                    if(reach){
                        int l = walls[j].a;
                        while(l!=walls[next].a){
                            reachable[l] = true;
                            l++;
                            l = (l==360?0:l);
                        }
                    }
                }
                FOR(k,0,360){
                    if (!reachable[k])
                        grid[i+1][k] = true;
                }
            }
            bool continued = false;
            FOR(k,0,360){
                if (!grid[i+1][k])
                    continued = true;
            }
            if (!continued){
                cout << "NO" << endl;
                VALUE(i);
                no = true;
                break;
            }
        }
        if (!no)
            cout << "YES" << endl;
    }
    return 0;
}