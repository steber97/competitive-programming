//#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <utility>
#include <iostream>
#include <stdexcept>

#import <random>
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


#define WORMHOLE -100000


class Azione {
public:
    int r = -1;
    int c = -1;
    bool iswormhole = false;

    string gotonext(Azione & neigh) {
        std::string rs = "";
        if (neigh.c == -1 && neigh.r == -1)
            return "";
        if (iswormhole)
            rs += std::to_string(c) + " " + std::to_string(r) + " ";

        if (neigh.r == r) {
            if (neigh.c == c - 1)
                return rs + "L";
            else if (neigh.c == c + 1)
                return rs + "R";
        }
        if (neigh.c == c) {
            if (neigh.r == r - 1)
                return rs + "U";
            else if (neigh.r == r + 1)
                return rs + "D";
        }
        return "ERROR";
    }

    Azione(int r, int c, bool iswormhole): r(r), c(c), iswormhole(iswormhole){

    }
    Azione(){}
};

class Snake {
public:
    int id;
    pair<int, int> head = make_pair<>(-1, -1);
    int lunghezza;
    vector<Azione> azioni;
    Snake(int id, int lunghezza) : id(id), lunghezza(lunghezza) {

    }
    Snake() {}


};

class Griglia {
public:
    vector<vector<ll>> grid;
    int R, C;
    Griglia(int R, int C) : R(R), C(C) {
        grid = vector<vector<ll>>(R, vector<ll>(C));
    }
};

class coord{
    public: 
    int x, y;
    ll val;
    coord(int y, int x, ll val): x(x), y(y),val(val) {

    }
    coord(){}
};


vector<Azione> place_snake(Snake& s, coord p1, coord p2, Griglia& g) {
    coord best_start = p1;
    ll bestval = - INT64_MAX;
    // cout << p1.y << " " << p1.x << "; " << p2.y << " " << p2.x << endl;
    // cout << s.lunghezza << endl;
    int remaining = (p2.y-p1.y+1) * (p2.x-p1.x+1);
    for(int i = p1.y; i <= p2.y; i++){
        for(int j = p1.x; j <= p2.x; j++) {
            if (remaining >= s.lunghezza){
                ll totsum = 0;
                coord it = coord(i, j, 0);
                for(int k = 0; k < s.lunghezza; k++) {
                    totsum += g.grid[it.y][it.x] != WORMHOLE ? g.grid[it.y][it.x] : 0;

                    // cout << it.y << " " << it.x << endl;
                    if ((k+j+1) % (p2.x - p1.x + 1) == 0){
                        it.y++;
                    }
                    else if ((it.y - i) % 2 == 0) {
                        it.x++;
                    }
                    else{
                        it.x--;
                    }
                }
                if (bestval < totsum) {
                    bestval = totsum;
                    best_start = coord(i, j, g.grid[i][j]);
                }
            }
            remaining--;
        }
    }

    // cout << "best "  << best_start.y << " " << best_start.x << endl;
    
    vector<Azione> soluz;
    coord it = coord(best_start.y, best_start.x, g.grid[best_start.y][best_start.x]);
    for(int k = 0; k < s.lunghezza; k++) {
        soluz.push_back(Azione(it.y, it.x, g.grid[it.y][it.x]==WORMHOLE));
        // cout << it.y << " " << it.x << endl;
        if ((k+best_start.x+1) % (p2.x - p1.x + 1) == 0){
            it.y++;
        }
        else if ((it.y - best_start.y) % 2 == 0) {
            it.x++;
        }
        else{
            it.x--;
        }
    }
    return soluz;
}

void read_input(int & C, int & R, int & S, vector<Snake>&snakes, Griglia & g) {

    cin >> C >> R >> S;
    snakes.resize(S);
    for (int i = 0; i < S; i++) {
        int len; cin >> len;
        snakes[i] = Snake(i, len);
    }

    g = Griglia(R, C);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            string s; cin >> s;
            if (s == "*") {
                g.grid[i][j] = WORMHOLE;
            }
            else {
                g.grid[i][j] = stoi(s);
            }
        }
    }
}

void soluzione(Griglia & griglia, vector<Snake> & snakes) {
    int sr = griglia.grid.size() / sqrt(snakes.size());
    int sc = griglia.grid[0].size() / sqrt(snakes.size());

    int subgridSize = sr * sc;
    int iSnake = 0;
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(snakes), std::end(snakes), rng);
    for (int row = 0; row < griglia.grid.size(); row += sr) {
        for (int col = 0; col < griglia.grid[0].size(); col += sc) {
            
            if (row + sr > griglia.grid.size() || col + sc > griglia.grid[0].size()) {
                continue;
            }

            if (snakes[iSnake].lunghezza <= subgridSize) {
                vector<Azione> soluz = place_snake(snakes[iSnake], coord(row, col,0), coord(row+sr-1, col+sc-1,0), griglia);
                
                snakes[iSnake].azioni = vector<Azione>(soluz.begin()+1, soluz.end());
                snakes[iSnake].head = {soluz[0].r, soluz[0].c};

                // int foundWormhole = 0;
                // for (int subrow = row; subrow < row + sr && snakes[iSnake].azioni.size() < snakes[iSnake].lunghezza - 1 - foundWormhole; subrow++) {
                //     for (int subcol = col; subcol < col + sc && snakes[iSnake].azioni.size() < snakes[iSnake].lunghezza - 1 - foundWormhole; subcol++) {
                //         int corrSubcol = (((subrow - row) % 2) == 0) ? subcol : (2 * col + sc - subcol - 1);
                //         ll val = griglia.grid[subrow][corrSubcol];
                //         bool isWormhole = (val == WORMHOLE);
                //         if (snakes[iSnake].head.first == -1) {
                //             if (!isWormhole)
                //                 snakes[iSnake].head = std::make_pair<>(subrow, corrSubcol);
                //             else
                //                 continue;
                //         }
                //         else {
                //             ll val = griglia.grid[subrow][corrSubcol];
                //             Azione a;
                //             a.iswormhole = isWormhole;
                //             a.r = subrow;
                //             a.c = corrSubcol;
                //             snakes[iSnake].azioni.push_back(a);
                //             if (isWormhole)
                //                 foundWormhole++;
                //         }                                                   
                //     }
                // }
                if ((snakes[iSnake].azioni.size() > 0 &&
                    snakes[iSnake].azioni[snakes[iSnake].azioni.size() - 1].iswormhole)) {
                    snakes[iSnake].head = make_pair<>(-1, -1);
                }
            }
            iSnake++;
            if (iSnake >= snakes.size())
                return;
        }
    }
}

int main() {
    Griglia g(0, 0);
    vector<Snake> snakes;
    int C, R, S;

    read_input(C, R, S, snakes, g);

    soluzione(g, snakes);

    for (int i = 0; i < snakes.size(); i++) {
        Snake s = snakes[i];
        if (s.head.first == -1) {
            cout << endl;
            continue;
        }
        /*
        bool invalid = false;
        for (Azione & a : s.azioni) {
            if (a.iswormhole) {
                invalid = true;
                break;
            }
        }
        if (invalid) {
            cout << endl;
            continue;
        }*/

        if (s.azioni.size() != 0) {
            cout << s.head.second << " " << s.head.first;
        }
        Azione prev;
        prev.r = s.head.first;
        prev.c = s.head.second;
        int k = 0;
        for (Azione & a : s.azioni) {
            if (k>=s.lunghezza)
                break;
            cout << " " << prev.gotonext(a);
            prev = a;
            k++;
            if (a.iswormhole)
                k++;
        }
        if (i < snakes.size() - 1)
            cout << endl;
    }

    return 0;
}