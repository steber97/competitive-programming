#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
    
    class State {
        public:
            int boxy, boxx, persy, persx, n, m;
            State(int boxy, int boxx, int persy, int persx, int n, int m){
                this->boxy = boxy;
                this->boxx = boxx;
                this->persy = persy;
                this->persx = persx;
                this->n = n;
                this->m = m;
            }

            int getHash(){
                return (persy * n + persx) * n * m + (boxy * n + boxx);
            }
        
    };
    public:
        vector<int> distances;
        vector<queue<State>> queues_at_dist;
        int n, m;

        pair<int, int> getPosTarget(vector<vector<char>>& grid, char target){
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    if (grid[i][j] == target)
                        return {i, j};
                }
            }
        }

        

        int minPushBox(vector<vector<char>>& grid) {
            this->n = grid.size();
            this->m = grid[0].size();
            distances.resize(n * n * m * m, -1);
            queues_at_dist.resize(n * m);
            pair<int, int> posPers = this->getPosTarget(grid, 'S');
            pair<int, int> posBox = this->getPosTarget(grid, 'B');
            pair<int, int> posTarget = this->getPosTarget(grid, 'T');

            State initial(posBox.first, posBox.second, posPers.first, posPers.second, n, m);

            queues_at_dist[0].push(initial);
            int current_dist = 0;
            distances[initial.getHash()] = 0;

            while(current_dist < n * m){
                if (queues_at_dist[current_dist].empty())
                    current_dist++;
                else{
                    State current = queues_at_dist[current_dist].front();
                    queues_at_dist[current_dist].pop();

                    if (current.boxy == posTarget.first && current.boxx == posTarget.second){
                        return current_dist;
                    }

                    for (int i = -1; i < 2; i++){
                        for (int j = -1; j < 2; j++){
                            if ((i != 0 || j != 0) && (i == 0 || j == 0))
                            if (current.persy + i >= 0 && current.persy + i < n){
                                if (current.persx + j >= 0 && current.persx + j < m){
                                    if (grid[i + current.persy][j + current.persx] != '#' && (current.boxy != i + current.persy || current.boxx != j + current.persx)){
                                        // standard move
                                        State next(current.boxy, current.boxx, current.persy + i, current.persx + j, n, m);
                                        if (distances[next.getHash()] == -1 || distances[next.getHash()] > current_dist){
                                            distances[next.getHash()] = current_dist;
                                            queues_at_dist[current_dist].push(next);
                                        }
                                    }
                                    else if (i + current.persy == current.boxy && j + current.persx == current.boxx){
                                        // Move box;
                                        if (current.persy + 2*i >= 0 && current.persy + 2*i < n) {
                                            if (current.persx + 2*j >= 0 && current.persx + 2*j < m){
                                                if (grid[current.persy + 2*i][current.persx + 2*j] != '#'){
                                                    State next(current.persy + 2*i, current.persx + 2*j, current.persy + i, current.persx + 2*j, n, m);
                                                    if (distances[next.getHash()] == -1 || distances[next.getHash()] > current_dist + 1){
                                                        distances[next.getHash()] = current_dist + 1;
                                                        queues_at_dist[current_dist + 1].push(next);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            return -1;
        }
};

int main() {

    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> grid[i][j];
        }
    }

    Solution sol;
    int moves = sol.minPushBox(grid);
    cout << moves << endl;
    return 0;

}