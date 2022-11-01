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


int move_pawn(vector<string>& board, int i, int j){
    int dy, res;
    char target;
    if (board[i][j] == 'p'){  // black
        dy = 1;
        target = 'K';
        res = 2;
    }
    else {
        dy = -1;
        target = 'k';
        res = 1;
    }

    if (i + dy < 8 && i + dy >= 0 && j + 1 < 8){
        if (board[i+dy][j+1] == target)
            return res;
    }
    if (i + dy < 8 && i + dy >= 0 && j - 1 >= 0){
        if (board[i+dy][j-1] == target)
            return res;
    }
    return 0;
}

int move_knight(vector<string>& board, int i, int j){
    vector<int> dx = {-2, -1, 1, 2, 2, 1, -1, -2};
    vector<int> dy = {-1, -2, -2, -1, 1, 2, 2, 1};
    char target;
    int res;
    if (board[i][j] == 'n'){
        target = 'K';
        res = 2;
    }
    else{
        target = 'k';
        res = 1; 
    }
    FOR(k,0,8){
        if (((i + dy[k]) >= 0) && ((i + dy[k]) < 8) && ((j + dx[k]) >= 0) && ((dx[k] + j) < 8)){
            if (board[i+dy[k]][j+dx[k]] == target)
                return res;
        }
    }
    return 0;
}

int move_bishop(vector<string>& board, int i, int j){
    vector<int> dy = {-1, -1, 1, 1};
    vector<int> dx = {-1, 1, 1, -1};
    char target;
    int res;
    if(board[i][j] == 'b'){
        target = 'K';
        res = 2;
    }
    else{
        target = 'k';
        res = 1;
    }
    FOR(k,0,4){
        FOR(d,1,8){
            if (((i + d*dy[k]) >= 0) && ((i + d*dy[k]) < 8) && 
                    ((j + d*dx[k]) >= 0) && ((j + d*dx[k]) < 8)){
                if (board[i + (d*dy[k])][j + (d*dx[k])] != '.'){
                    if (board[i + (d*dy[k])][j + (d*dx[k])] == target){
                        return res;
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                break;
            }
        }
    }
    return 0;
}

int move_rook(vector<string>& board, int i, int j){
    vector<int> dy = {-1, 0, 1, 0};
    vector<int> dx = {0, 1, 0, -1};
    char target;
    int res;
    if(board[i][j] == 'r'){
        target = 'K';
        res = 2;
    }
    else{
        target = 'k';
        res = 1;
    }
    FOR(k,0,4){
        FOR(d,1,8){
            if (((i + d*dy[k]) >= 0) && ((i + d*dy[k] < 8)) && 
                    ((j + d*dx[k]) >= 0) && ((j + d*dx[k] < 8))){
                if (board[i + (d*dy[k])][j + (d*dx[k])] != '.'){
                    if (board[i + (d*dy[k])][j + (d*dx[k])] == target){
                        return res;
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                break;
            }
        }
    }
    return 0;
}

int move_queen(vector<string>& board, int i, int j){
    vector<int> dy = {-1, -1, 1, 1, -1, 0, 1, 0};
    vector<int> dx = {-1, 1, 1, -1, 0, 1, 0, -1};
    char target;
    int res;
    if(board[i][j] == 'q'){
        target = 'K';
        res = 2;
    }
    else{
        target = 'k';
        res = 1;
    }
    FOR(k,0,8){
        FOR(d,1,8){
            if (((i + d*dy[k]) >= 0) && ((i + d*dy[k] < 8)) && 
                    ((j + d*dx[k]) >= 0) && ((j + d*dx[k] < 8))){
                if (board[i + (d*dy[k])][j + (d*dx[k])] != '.'){
                    if (board[i + (d*dy[k])][j + (d*dx[k])] == target){
                        return res;
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                break;
            }
        }
    }
    return 0;
}


int main(){
    vector<string> board(8, "");
    bool finish = false;
    int t = 1;
    while(!finish) {
        finish = true;
        FOR(i,0,8){
            string s;
            getline(cin, board[i]);
            FOR(j,0,8)
                if (board[i][j] != '.')
                    finish = false;
        }
        FOR(i,0,8){
            COUT(board[i]);
            COUT(endl);
        }
        if (!finish){
            int win = 0;
            FOR(i,0,8){
                FOR(j,0,8){
                    if (board[i][j]=='p' || board[i][j]=='P'){
                        win = move_pawn(board, i, j);
                    }
                    else if (board[i][j]=='n' || board[i][j]=='N'){
                        win = move_knight(board, i, j);
                    }
                    else if (board[i][j]=='b' || board[i][j]=='B'){
                        COUT("Move bishop "); COUT(i); COUT(" "); COUT(j); COUT(endl);
                        win = move_bishop(board, i, j);
                        COUT(win); COUT(endl);
                    }
                    else if (board[i][j]=='r' || board[i][j]=='R'){
                        win = move_rook(board, i, j);
                    }
                    else if (board[i][j]=='q' || board[i][j]=='Q'){
                        win = move_queen(board, i, j);
                    }

                    if (win != 0){
                        break;
                    }
                }
                if (win != 0)
                    break;
            }
            if (win == 0){
                cout << "Game #" << t << ": no king is in check." << endl;
            }
            else if(win == 1){
                cout << "Game #" << t << ": black king is in check." << endl;
            }
            else if (win == 2){
                cout << "Game #" << t << ": white king is in check." << endl;

            }
        }
        t++;
        string s;
        getline(cin, s);  // empty string;
        // cout << s << endl;
    }
    return 0;    
}