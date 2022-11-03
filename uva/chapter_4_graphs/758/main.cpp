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
typedef vector<char> vc;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<char>> vvc;
typedef vector<vector<bool>> vvb;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


class CC{
    public:
        vii pos;
        ii head;
        int id;
    friend bool operator<(const CC& l, const CC& r)
    {
        if  (l.pos.size() > r.pos.size())
            return true;
        if (l.pos.size() == r.pos.size())
            if (l.head.second < r.head.second)
                return true;
            else if (l.head.second == r.head.second)
                if (l.head.first < r.head.first)
                    return true;
        return false;
    }
};

CC dfs(int i, int j, vvi& visited, vvc& grid){
    CC res;
    res.head = {i,j};
    res.id = visited[i][j];
    res.pos = vii();
    FOR(k,-1,2){
        FOR(l,-1,2){
            if (k==0 || l==0){
                if(((i+k) >= 0) && ((i+k)<grid.size())){
                    if (((j+l) >= 0) && ((j+l)<grid[0].size())){
                        if(visited[i+k][j+l] == -1){
                            if (grid[i][j] == grid[i+k][j+l]){
                                visited[i+k][j+l] = res.id;
                                CC tmp = dfs(i+k, j+l, visited, grid);
                                res.pos.insert(res.pos.end(), tmp.pos.begin(), tmp.pos.end());
                                if (tmp.head.second < res.head.second)
                                    res.head = tmp.head;
                                else if ((tmp.head.second == res.head.second) && (tmp.head.first<res.head.first))
                                    res.head = tmp.head;
                            }
                        }
                    }
                }
            }
        }
    }
    res.pos.push_back({i,j});
    
    return res;
}

void printgrid(vvc& grid){
    FOR(i,0,10){
        FOR(j,0,15)
            COUT(grid[i][j]);
        COUT(endl);
    }   
    COUT(endl);
}


int main(){  
    int T;
    cin >> T;
    FOR(t,1,T+1){
        cout << "Game " << t << ":" << endl << endl;
        // R, G, B, .->empty
        vvc grid(10, vc(15));
        for(int i = 9; i>=0; i--){
            FOR(j,0,15){
                cin >> grid[i][j];
            }
        }



        bool finish = false;
        int movecount = 1;
        long long totscore = 0;
        while(!finish){
            vector<CC> vcc;
            int id = 0;
            vvi visited(10, vi(15, -1));  // -1 unvisited
            FOR(i,0,10){
                FOR(j,0,15){
                    if ((visited[i][j] == -1) && (grid[i][j] != '.')){
                        visited[i][j] = id++;
                        CC cc = dfs(i,j,visited,grid);
                        vcc.push_back(cc);
                    }
                }
            }
            sort(vcc.begin(), vcc.end());
            if (vcc.size() == 0 || vcc[0].pos.size() == 1){
                finish = true;
            }
            else{
                cout << "Move " << movecount++ << " at (" << 
                    vcc[0].head.first+1 << "," << vcc[0].head.second+1 << 
                    "): removed " << vcc[0].pos.size() << " balls of color " << 
                    grid[vcc[0].head.first][vcc[0].head.second] << ", got " <<
                    pow(vcc[0].pos.size()-2, 2) << " points." << endl;
                totscore += pow(vcc[0].pos.size()-2, 2);
                for(ii p: vcc[0].pos){
                    grid[p.first][p.second] = '.';
                }
                // Compress:
                // first by column
                FOR(i,1,10){
                    FOR(j,0,15){
                        if (grid[i][j] != '.'){
                            char color = grid[i][j];
                            int k = i;
                            while(k>0 && grid[k-1][j] == '.')
                                k--;
                            grid[i][j] = '.';
                            grid[k][j] = color;
                        }
                    }
                }
                // Then horizontally
                vvc grid2(10, vc(15, '.'));
                int shift = 0;
                // printgrid(grid);
                FOR(j,0,15){
                    bool empty = true;
                    FOR(i,0,10){
                        if (grid[i][j]!='.')
                            empty = false;
                    }
                    if (empty){
                        shift++;
                    }
                    else{
                        FOR(i,0,10){
                            grid2[i][j-shift]=grid[i][j];
                        }
                    }
                }

                grid = grid2;
                // printgrid(grid);
            }
        }
        int tot = 0;
        FOR(i,0,10)
            FOR(j,0,15)
                if (grid[i][j] != '.')
                    tot++;
        cout << "Final score: " << totscore + (tot==0?1000:0) << ", with " << tot <<" balls remaining." << endl << (t!=T?"\n":"");

    }
    return 0;    
}